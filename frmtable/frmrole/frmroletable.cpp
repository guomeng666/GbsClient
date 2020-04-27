#include "frmroletable.h"
#include "frmroleedit.h"
#include "ui_frmroletable.h"

FrmRoleTable::FrmRoleTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::TableRole)
{
    ui->setupUi(this);
    this->initForm();
}

FrmRoleTable::~FrmRoleTable()
{
    delete ui;
}

void FrmRoleTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "角色名字" << "权限名字" << "创建日期" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmRoleTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmRoleTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmRoleTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmRoleTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmRoleTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmRoleTable::onDeleteRow);
}

void FrmRoleTable::editData(QString editStatus,const QStringList &row)
{
    FrmRoleEdit *editFrm = new FrmRoleEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter")
        editFrm->setDetailData(row);
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(row);
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
void FrmRoleTable::queryTableData(qint32 page, qint32 perPage, const QString& postName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryRoel);
    session.addRequestData("Sender","Admin");
    session.addRequestData("RoleName",postName);
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

void FrmRoleTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmRoleTable::onEventShowTableData()
{
    qDebug()<<"RoleShowEvent";
    queryTableData(m_curPage, m_perPage,"","","");
}

void FrmRoleTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmRoleTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmRoleTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_postName = ui->editName->text();
    queryTableData(1, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmRoleTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmRoleTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmRoleTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmRoleTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmRoleTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmRoleTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_postName,m_startTime,m_endTime);
}

void FrmRoleTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmRoleTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmRoleTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

