#include "frmvehicletypetable.h"
#include "frmvehicletypeedit.h"
#include "ui_frmvehicletypetable.h"

FrmVehicleTypeTable::FrmVehicleTypeTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmVehicleTypeTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmVehicleTypeTable::~FrmVehicleTypeTable()
{
    delete ui;
}

void FrmVehicleTypeTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "车辆类型名字" << "预估载重量" <<"创建人" <<"创建日期" <<"更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmVehicleTypeTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmVehicleTypeTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmVehicleTypeTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmVehicleTypeTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmVehicleTypeTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmVehicleTypeTable::onDeleteRow);
}

void FrmVehicleTypeTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmVehicleTypeEdit *editFrm = new FrmVehicleTypeEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmVehicleTypeTable::queryTableData(qint32 page, qint32 perPage, const QString& vehicleTypeName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryVehicleType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("VehicleTypeName",vehicleTypeName);
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

void FrmVehicleTypeTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmVehicleTypeTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmVehicleTypeTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmVehicleTypeTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmVehicleTypeTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_vehicleTypeName = ui->editName->text();
    queryTableData(1, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
}

void FrmVehicleTypeTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
}

void FrmVehicleTypeTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmVehicleTypeTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
}

void FrmVehicleTypeTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
}

void FrmVehicleTypeTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
}

void FrmVehicleTypeTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_vehicleTypeName,m_startTime,m_endTime);
}

void FrmVehicleTypeTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmVehicleTypeTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmVehicleTypeTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

