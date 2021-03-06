#include "frmvehicletable.h"
#include "frmvehicleedit.h"
#include "ui_frmvehicletable.h"

FrmVehicleTable::FrmVehicleTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmVehicleTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmVehicleTable::~FrmVehicleTable()
{
    delete ui;
}

void FrmVehicleTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "车牌号码" << "类型" << "颜色" << "车架号码" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmVehicleTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmVehicleTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmVehicleTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmVehicleTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmVehicleTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmVehicleTable::onDeleteRow);
}

void FrmVehicleTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmVehicleEdit *editFrm = new FrmVehicleEdit(this);
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
void FrmVehicleTable::queryTableData(qint32 page, qint32 perPage, const QString& liscense,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryVehicle);
    session.addRequestData("Sender","Admin");
    session.addRequestData("VehicleLiscence",liscense);
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

void FrmVehicleTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmVehicleTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmVehicleTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmVehicleTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmVehicleTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_liscense = ui->editName->text();
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmVehicleTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmVehicleTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmVehicleTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmVehicleTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmVehicleTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmVehicleTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmVehicleTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmVehicleTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmVehicleTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

