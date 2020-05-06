#include "frmunloadtable.h"
#include "frmunloadedit.h"
#include "ui_frmunloadtable.h"

FrmUnloadTable::FrmUnloadTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmUnloadTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmUnloadTable::~FrmUnloadTable()
{
    delete ui;
}

void FrmUnloadTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "车牌号码" << "仓库" << "扣重总量" << "备注"<< "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmUnloadTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmUnloadTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmUnloadTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmUnloadTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmUnloadTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmUnloadTable::onDeleteRow);
}

void FrmUnloadTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmUnloadEdit *editFrm = new FrmUnloadEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_liscense,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_liscense,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmUnloadTable::queryTableData(qint32 page, qint32 perPage, const QString& name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryUnload);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Name",name);
    session.addRequestData("StartPage",QString::number(page));
    session.addRequestData("PerPage",QString::number(perPage));
    session.addRequestData("StartDate",startTime);
    session.addRequestData("EndDate",endTime);

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        ui->tableWidget->setTableData(session.getTotalAmount(),
                                      session.getCurPage(),
                                      session.getTableData());
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmUnloadTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmUnloadTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmUnloadTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmUnloadTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmUnloadTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_liscense = ui->editName->text();
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmUnloadTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmUnloadTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmUnloadTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmUnloadTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmUnloadTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmUnloadTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmUnloadTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmUnloadTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmUnloadTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

