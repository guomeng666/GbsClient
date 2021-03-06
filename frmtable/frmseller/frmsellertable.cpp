#include "frmsellertable.h"
#include "frmselleredit.h"
#include "ui_frmsellertable.h"

FrmSellerTable::FrmSellerTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmSellerTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmSellerTable::~FrmSellerTable()
{
    delete ui;
}

void FrmSellerTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "售粮户姓名" << "身份证号码" << "身份证住址" << "电话号码" \
           << "银行名字" << "银行卡号码" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmSellerTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmSellerTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmSellerTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmSellerTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmSellerTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmSellerTable::onDeleteRow);
}

void FrmSellerTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmSellerEdit *editFrm = new FrmSellerEdit(this);
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
void FrmSellerTable::queryTableData(qint32 page, qint32 perPage, const QString& name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerySeller);
    session.addRequestData("Sender","Admin");
    session.addRequestData("SellerName",name);
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

void FrmSellerTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmSellerTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmSellerTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmSellerTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmSellerTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_liscense = ui->editName->text();
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellerTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellerTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmSellerTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellerTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellerTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellerTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellerTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmSellerTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmSellerTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

