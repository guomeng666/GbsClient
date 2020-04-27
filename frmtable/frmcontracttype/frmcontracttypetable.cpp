#include "frmcontracttypetable.h"
#include "frmcontracttypeedit.h"
#include "ui_frmcontracttypetable.h"

FrmContractTypeTable::FrmContractTypeTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmContractTypeTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmContractTypeTable::~FrmContractTypeTable()
{
    delete ui;
}

void FrmContractTypeTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "合同类型" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmContractTypeTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmContractTypeTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmContractTypeTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmContractTypeTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmContractTypeTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmContractTypeTable::onDeleteRow);
}

void FrmContractTypeTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmContractTypeEdit *editFrm = new FrmContractTypeEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_contractName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_contractName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmContractTypeTable::queryTableData(qint32 page, qint32 perPage, const QString& contractName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryContractType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("ContractTypeName",contractName);
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

void FrmContractTypeTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmContractTypeTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmContractTypeTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmContractTypeTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmContractTypeTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_contractName = ui->editName->text();
    queryTableData(1, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTypeTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTypeTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmContractTypeTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTypeTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTypeTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTypeTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTypeTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmContractTypeTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmContractTypeTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

