#include "frmpaymenttypetable.h"
#include "frmpaymenttypeedit.h"
#include "ui_frmpaymenttypetable.h"

FrmPaymenttypeTable::FrmPaymenttypeTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmPaymenttypeTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmPaymenttypeTable::~FrmPaymenttypeTable()
{
    delete ui;
}

void FrmPaymenttypeTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "支付类型" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmPaymenttypeTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmPaymenttypeTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmPaymenttypeTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmPaymenttypeTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmPaymenttypeTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmPaymenttypeTable::onDeleteRow);
}

void FrmPaymenttypeTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmPaymenttypeEdit *editFrm = new FrmPaymenttypeEdit(this);
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
void FrmPaymenttypeTable::queryTableData(qint32 page, qint32 perPage, const QString& supplierName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryPaymenttype);
    session.addRequestData("Sender","Admin");
    session.addRequestData("PaymentTypeName",supplierName);
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

void FrmPaymenttypeTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmPaymenttypeTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmPaymenttypeTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmPaymenttypeTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmPaymenttypeTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_warehouseName = ui->editName->text();
    queryTableData(1, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmPaymenttypeTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmPaymenttypeTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmPaymenttypeTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmPaymenttypeTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmPaymenttypeTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmPaymenttypeTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_warehouseName,m_startTime,m_endTime);
}

void FrmPaymenttypeTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmPaymenttypeTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmPaymenttypeTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

