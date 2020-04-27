#include "frmpacktypetable.h"
#include "frmpacktypeedit.h"
#include "ui_FrmPackTypeTable.h"

FrmPackTypeTable::FrmPackTypeTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmPackTypeTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmPackTypeTable::~FrmPackTypeTable()
{
    delete ui;
}

void FrmPackTypeTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "支付类型" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmPackTypeTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmPackTypeTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmPackTypeTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmPackTypeTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmPackTypeTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmPackTypeTable::onDeleteRow);
}

void FrmPackTypeTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmPackTypeEdit *editFrm = new FrmPackTypeEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_packName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_packName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmPackTypeTable::queryTableData(qint32 page, qint32 perPage, const QString& packName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryPackType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("PackTypeName",packName);
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

void FrmPackTypeTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmPackTypeTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmPackTypeTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmPackTypeTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmPackTypeTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_packName = ui->editName->text();
    queryTableData(1, m_perPage,m_packName,m_startTime,m_endTime);
}

void FrmPackTypeTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_packName,m_startTime,m_endTime);
}

void FrmPackTypeTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmPackTypeTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_packName,m_startTime,m_endTime);
}

void FrmPackTypeTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_packName,m_startTime,m_endTime);
}

void FrmPackTypeTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_packName,m_startTime,m_endTime);
}

void FrmPackTypeTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_packName,m_startTime,m_endTime);
}

void FrmPackTypeTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmPackTypeTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmPackTypeTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

