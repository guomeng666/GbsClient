#include "frmprocedurenodetable.h"
#include "frmprocedurenodeedit.h"
#include "ui_frmprocedurenodetable.h"

FrmProcedureNodeTable::FrmProcedureNodeTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmProcedureNodeTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmProcedureNodeTable::~FrmProcedureNodeTable()
{
    delete ui;
}

void FrmProcedureNodeTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "节点名字" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmProcedureNodeTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmProcedureNodeTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmProcedureNodeTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmProcedureNodeTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmProcedureNodeTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmProcedureNodeTable::onDeleteRow);
}

void FrmProcedureNodeTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmProcedureNodeEdit *editFrm = new FrmProcedureNodeEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_nodeName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_nodeName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmProcedureNodeTable::queryTableData(qint32 page, qint32 perPage, const QString& nodeName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryProcedureNode);
    session.addRequestData("Sender","Admin");
    session.addRequestData("ProcedureNodeName",nodeName);
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

void FrmProcedureNodeTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmProcedureNodeTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmProcedureNodeTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmProcedureNodeTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmProcedureNodeTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_nodeName = ui->editName->text();
    queryTableData(1, m_perPage,m_nodeName,m_startTime,m_endTime);
}

void FrmProcedureNodeTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_nodeName,m_startTime,m_endTime);
}

void FrmProcedureNodeTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmProcedureNodeTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_nodeName,m_startTime,m_endTime);
}

void FrmProcedureNodeTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_nodeName,m_startTime,m_endTime);
}

void FrmProcedureNodeTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_nodeName,m_startTime,m_endTime);
}

void FrmProcedureNodeTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_nodeName,m_startTime,m_endTime);
}

void FrmProcedureNodeTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmProcedureNodeTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmProcedureNodeTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

