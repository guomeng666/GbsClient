#include "frmdepartmenttable.h"
#include "frmdepartmentedit.h"
#include "ui_frmdepartmenttable.h"

FrmDepartmentTable::FrmDepartmentTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmDepartmentTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmDepartmentTable::~FrmDepartmentTable()
{
    delete ui;
}

void FrmDepartmentTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "部门名字" << "创建日期" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmDepartmentTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmDepartmentTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmDepartmentTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmDepartmentTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmDepartmentTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmDepartmentTable::onDeleteRow);
}

void FrmDepartmentTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmDepartmentEdit *editFrm = new FrmDepartmentEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_departmentName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_departmentName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmDepartmentTable::queryTableData(qint32 page, qint32 perPage, const QString& departmentName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryDepartment);
    session.addRequestData("Sender","Admin");
    session.addRequestData("DepartmentName",departmentName);
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

void FrmDepartmentTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmDepartmentTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmDepartmentTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmDepartmentTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmDepartmentTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_departmentName = ui->editName->text();
    queryTableData(1, m_perPage,m_departmentName,m_startTime,m_endTime);
}

void FrmDepartmentTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_departmentName,m_startTime,m_endTime);
}

void FrmDepartmentTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmDepartmentTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_departmentName,m_startTime,m_endTime);
}

void FrmDepartmentTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_departmentName,m_startTime,m_endTime);
}

void FrmDepartmentTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_departmentName,m_startTime,m_endTime);
}

void FrmDepartmentTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_departmentName,m_startTime,m_endTime);
}

void FrmDepartmentTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmDepartmentTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmDepartmentTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

