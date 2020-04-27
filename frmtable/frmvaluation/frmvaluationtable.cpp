#include "frmvaluationtable.h"
#include "frmvaluationedit.h"
#include "ui_frmvaluationtable.h"

FrmValuationTable::FrmValuationTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmValuationTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmValuationTable::~FrmValuationTable()
{
    delete ui;
}

void FrmValuationTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "计价名字" << "单价" <<"默认计价方式" <<"详细规则" <<"备注" \
           << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmValuationTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmValuationTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmValuationTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmValuationTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmValuationTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmValuationTable::onDeleteRow);
}

void FrmValuationTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmValuationEdit *editFrm = new FrmValuationEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_bankTypeName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_bankTypeName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmValuationTable::queryTableData(qint32 page, qint32 perPage, const QString& bankTypeName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryValuation);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Name",bankTypeName);
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

void FrmValuationTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmValuationTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmValuationTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmValuationTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmValuationTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_bankTypeName = ui->editName->text();
    queryTableData(1, m_perPage,m_bankTypeName,m_startTime,m_endTime);
}

void FrmValuationTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_bankTypeName,m_startTime,m_endTime);
}

void FrmValuationTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmValuationTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_bankTypeName,m_startTime,m_endTime);
}

void FrmValuationTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_bankTypeName,m_startTime,m_endTime);
}

void FrmValuationTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_bankTypeName,m_startTime,m_endTime);
}

void FrmValuationTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_bankTypeName,m_startTime,m_endTime);
}

void FrmValuationTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmValuationTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmValuationTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

