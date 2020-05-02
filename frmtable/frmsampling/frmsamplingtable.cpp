#include "frmsamplingtable.h"
#include "frmsamplingedit.h"
#include "ui_frmsamplingtable.h"

FrmSamplingTable::FrmSamplingTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmSamplingTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmSamplingTable::~FrmSamplingTable()
{
    delete ui;
}

void FrmSamplingTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "扦样编号" << "凭证号" << "车牌号码" << "车辆类型" << "车架号码" << "车辆颜色" << "标签号码"\
           << "备注" << "图片索引" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmSamplingTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmSamplingTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmSamplingTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmSamplingTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmSamplingTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmSamplingTable::onDeleteRow);
}

void FrmSamplingTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmSamplingEdit *editFrm = new FrmSamplingEdit(this);
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
void FrmSamplingTable::queryTableData(qint32 page, qint32 perPage, const QString& field, const QString &name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerySamling);
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

void FrmSamplingTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmSamplingTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","","");
}

void FrmSamplingTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmSamplingTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmSamplingTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_fieldName = ui->cbxField->currentText();
    m_fieldContent = ui->editField->text();
    queryTableData(1, m_perPage, m_fieldName, m_fieldContent, m_startTime, m_endTime);
}

void FrmSamplingTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmSamplingTable::on_editField_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmSamplingTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmSamplingTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmSamplingTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmSamplingTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmSamplingTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmSamplingTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

