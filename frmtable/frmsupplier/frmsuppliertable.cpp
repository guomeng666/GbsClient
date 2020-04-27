#include "frmsuppliertable.h"
#include "frmsupplieredit.h"
#include "ui_frmsuppliertable.h"

FrmSupplierTable::FrmSupplierTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmSupplierTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmSupplierTable::~FrmSupplierTable()
{
    delete ui;
}

void FrmSupplierTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "供应商名字" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmSupplierTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmSupplierTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmSupplierTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmSupplierTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmSupplierTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmSupplierTable::onDeleteRow);
}

void FrmSupplierTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmSupplierEdit *editFrm = new FrmSupplierEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_warehouseName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_warehouseName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmSupplierTable::queryTableData(qint32 page, qint32 perPage, const QString& supplierName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerySupplier);
    session.addRequestData("Sender","Admin");
    session.addRequestData("WarehouseName",supplierName);
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

void FrmSupplierTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmSupplierTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmSupplierTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmSupplierTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmSupplierTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_warehouseName = ui->editName->text();
    queryTableData(1, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmSupplierTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmSupplierTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmSupplierTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmSupplierTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmSupplierTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmSupplierTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmSupplierTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmSupplierTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmSupplierTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

