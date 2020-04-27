#include "frmusertable.h"
#include "frmuseredit.h"
#include "ui_frmusertable.h"

FrmUserTable::FrmUserTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmUserTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmUserTable::~FrmUserTable()
{
    delete ui;
}

void FrmUserTable::initForm()
{
    QStringList header;
    header << "编号" << "用户名字" << "用户密码" << "身份证号码" << "身份证住址" << "隶属部门" << "角色名字"\
           << "最后登录时间" << "创建日期" << "更新日期" ;
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmUserTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmUserTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmUserTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmUserTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmUserTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmUserTable::onDeleteRow);

    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
}

void FrmUserTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmUserEdit *editFrm = new FrmUserEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter")
        editFrm->setDetailData(rowData);
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_postName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_postName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmUserTable::queryTableData(qint32 page, qint32 perPage, const QString& Name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryUser);
    session.addRequestData("Sender","Admin");
    session.addRequestData("UserName",Name);
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

void FrmUserTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmUserTable::onEventShowTableData()
{
    qDebug()<<"RoleShowEvent";
    queryTableData(m_curPage, m_perPage,"","","");
}

void FrmUserTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmUserTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmUserTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_postName = ui->editName->text();
    queryTableData(1, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmUserTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmUserTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmUserTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmUserTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmUserTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmUserTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmUserTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmUserTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmUserTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}
