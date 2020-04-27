#include "frmpurchasetable.h"
#include "frmpurchaseedit.h"
#include "ui_frmpurchasetable.h"

FrmPurchaseTable::FrmPurchaseTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmPurchaseTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmPurchaseTable::~FrmPurchaseTable()
{
    delete ui;
}

void FrmPurchaseTable::initForm()
{
    QStringList header;
    header << "编号" << "流程名字" << "流程顺序" << "创建人"\
           << "创建时间" << "更新人" << "更新日期" ;
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmPurchaseTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmPurchaseTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmPurchaseTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmPurchaseTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmPurchaseTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmPurchaseTable::onDeleteRow);

    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
}

void FrmPurchaseTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmPurchaseEdit *editFrm = new FrmPurchaseEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter")
        editFrm->setDetailData(rowData);
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_purchaseName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_purchaseName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmPurchaseTable::queryTableData(qint32 page, qint32 perPage, const QString& Name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryPurchase);
    session.addRequestData("Sender","Admin");
    session.addRequestData("PurchaseName",Name);
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

void FrmPurchaseTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmPurchaseTable::onEventShowTableData()
{
    qDebug()<<"RoleShowEvent";
    queryTableData(m_curPage, m_perPage,"","","");
}

void FrmPurchaseTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmPurchaseTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmPurchaseTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_purchaseName = ui->editName->text();
    queryTableData(1, m_perPage,m_purchaseName,m_startTime,m_endTime);
}

void FrmPurchaseTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_purchaseName,m_startTime,m_endTime);
}

void FrmPurchaseTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmPurchaseTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_purchaseName,m_startTime,m_endTime);
}

void FrmPurchaseTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_purchaseName,m_startTime,m_endTime);
}

void FrmPurchaseTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_purchaseName,m_startTime,m_endTime);
}

void FrmPurchaseTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_purchaseName,m_startTime,m_endTime);
}

void FrmPurchaseTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmPurchaseTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmPurchaseTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}
