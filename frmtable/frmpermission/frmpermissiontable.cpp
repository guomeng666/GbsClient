#include "frmpermissiontable.h"
#include "frmpermissionedit.h"
#include "ui_frmpermissiontable.h"

FrmPermissionTable::FrmPermissionTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmPermissionTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmPermissionTable::~FrmPermissionTable()
{
    delete ui;
}

void FrmPermissionTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header<<"编号"<<"权限名称"<<"查询权限"<<"管理权限"<<"登记修改权限"
          <<"扦样修改权限"<<"化验修改权限"<<"售粮修改权限"<<"检斤修改权限"
          <<"卸粮修改权限"<<"结算修改权限"<<"创建日期"<<"更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmPermissionTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmPermissionTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmPermissionTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmPermissionTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmPermissionTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmPermissionTable::onDeleteRow);
}

void FrmPermissionTable::editData(QString editStatus,const QStringList &row)
{
    FrmpermissionEdit *editFrm = new FrmpermissionEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter")
        editFrm->setDetailData(row);
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(row);
        queryTableData(m_curPage, m_perPage,m_permissionName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_permissionName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmPermissionTable::queryTableData(qint32 page, qint32 perPage, const QString& postName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerPermission);
    session.addRequestData("Sender","Admin");
    session.addRequestData("PermissionName",postName);
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

void FrmPermissionTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmPermissionTable::onEventShowTableData()
{
    qDebug()<<"RoleShowEvent";
    queryTableData(m_curPage, m_perPage,"","","");
}

void FrmPermissionTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmPermissionTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmPermissionTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_permissionName = ui->editName->text();
    queryTableData(1, m_perPage,m_permissionName,m_startTime,m_endTime);
}

void FrmPermissionTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_permissionName,m_startTime,m_endTime);
}

void FrmPermissionTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmPermissionTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_permissionName,m_startTime,m_endTime);
}

void FrmPermissionTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_permissionName,m_startTime,m_endTime);
}

void FrmPermissionTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_permissionName,m_startTime,m_endTime);
}

void FrmPermissionTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_permissionName,m_startTime,m_endTime);
}

void FrmPermissionTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmPermissionTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmPermissionTable::on_btnAdd_clicked()
{
    editData("add", QStringList());
}

