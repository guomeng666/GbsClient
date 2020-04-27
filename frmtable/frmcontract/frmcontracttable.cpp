#include "frmcontracttable.h"
#include "frmcontractedit.h"
#include "ui_frmcontracttable.h"

FrmContractTable::FrmContractTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmContractTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmContractTable::~FrmContractTable()
{
    delete ui;
}

void FrmContractTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "合同号码" << "合同类型" << "粮食类型"\
           << "开始日期" << "结束日期" << "订单编号" << "供应商"\
           << "运输公司" << "原发地" << "采购总量" <<"已完成" \
           << "是否完成" << "车船号码" << "车皮号码"<<"支付方式" \
           <<"银行类型" << "银行卡号" << "计价方式" <<"联系人" \
           <<"联系人电话" <<"备注" << "创建人" << "创建日期"\
           << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmContractTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmContractTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmContractTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmContractTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmContractTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmContractTable::onDeleteRow);
}

void FrmContractTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmContractEdit *editFrm = new FrmContractEdit(this);
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
void FrmContractTable::queryTableData(qint32 page, qint32 perPage, const QString& contractName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryContract);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Name",contractName);
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

void FrmContractTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmContractTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmContractTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmContractTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmContractTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_contractName = ui->editName->text();
    queryTableData(1, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmContractTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_contractName,m_startTime,m_endTime);
}

void FrmContractTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmContractTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmContractTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

