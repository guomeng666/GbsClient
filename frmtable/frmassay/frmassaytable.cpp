#include "frmassaytable.h"
#include "frmassayedit.h"
#include "ui_frmassaytable.h"

FrmAssayTable::FrmAssayTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmAssayTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmAssayTable::~FrmAssayTable()
{
    delete ui;
}

void FrmAssayTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "化验编号"\
           << "粮食类型"\
           << "样品级别"\
           << "样品盒号码"\
           << "标准样"\
           << "留样号码"\
           << "容重"\
           << "水分"\
           << "霉变"\
           << "破损"\
           << "热损"\
           << "并间杂"\
           << "小石子"\
           << "土块"\
           << "棒芯"\
           << "异种粮"\
           << "水泡粒"\
           << "异味"\
           << "样品毛重"\
           << "样品净重"\
           << "杂质"\
           << "化验完毕"\
           << "是否拒收"\
           << "拒收原因"\
           << "备注信息"\
           << "化验员" << "化验日期" << "修改人" << "修改日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmAssayTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmAssayTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmAssayTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmAssayTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmAssayTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmAssayTable::onDeleteRow);
}

void FrmAssayTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmAssayEdit *editFrm = new FrmAssayEdit(this);
    editFrm->setEditType(editStatus);
    if(editStatus == "alter"){
        editFrm->setDetailData(rowData);
    }
    else if(editStatus == "delete")
    {
        //删除数据不需要显示
        editFrm->deleteRowData(rowData);
        queryTableData(m_curPage, m_perPage, m_fieldName, m_fieldContent, m_startTime, m_endTime);
        return;
    }
    int status = editFrm->exec();
    if(status == 0){
        //正常返回
        queryTableData(m_curPage, m_perPage, m_fieldName, m_fieldContent, m_startTime, m_endTime);
    }
    editFrm->deleteLater();
}

//查询表格数据
void FrmAssayTable::queryTableData(qint32 page, qint32 perPage, const QString& field, const QString &name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryAssay);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Field",field);
    session.addRequestData("Name",name);
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

void FrmAssayTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmAssayTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","","");
}

void FrmAssayTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmAssayTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmAssayTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_fieldName = ui->cbxField->currentText();
    m_fieldContent = ui->editField->text();
    queryTableData(1, m_perPage, m_fieldName, m_fieldContent, m_startTime, m_endTime);
}

void FrmAssayTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmAssayTable::on_editField_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmAssayTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmAssayTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmAssayTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmAssayTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmAssayTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmAssayTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

