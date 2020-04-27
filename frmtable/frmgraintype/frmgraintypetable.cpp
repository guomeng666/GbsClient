#include "frmgraintypetable.h"
#include "frmgraintypeedit.h"
#include "ui_FrmGrainTypeTable.h"

FrmGrainTypeTable::FrmGrainTypeTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmGrainTypeTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmGrainTypeTable::~FrmGrainTypeTable()
{
    delete ui;
}

void FrmGrainTypeTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "粮食类型" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmGrainTypeTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmGrainTypeTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmGrainTypeTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmGrainTypeTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmGrainTypeTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmGrainTypeTable::onDeleteRow);
}

void FrmGrainTypeTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmGrainTypeEdit *editFrm = new FrmGrainTypeEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage,m_grainName,m_startTime,m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage,m_grainName,m_startTime,m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmGrainTypeTable::queryTableData(qint32 page, qint32 perPage, const QString& grainName,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryGrainType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("GrainTypeName",grainName);
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

void FrmGrainTypeTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmGrainTypeTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmGrainTypeTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmGrainTypeTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmGrainTypeTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_grainName = ui->editName->text();
    queryTableData(1, m_perPage,m_grainName,m_startTime,m_endTime);
}

void FrmGrainTypeTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_grainName,m_startTime,m_endTime);
}

void FrmGrainTypeTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmGrainTypeTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_grainName,m_startTime,m_endTime);
}

void FrmGrainTypeTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_grainName,m_startTime,m_endTime);
}

void FrmGrainTypeTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_grainName,m_startTime,m_endTime);
}

void FrmGrainTypeTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_grainName,m_startTime,m_endTime);
}

void FrmGrainTypeTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmGrainTypeTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmGrainTypeTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

