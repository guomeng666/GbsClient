#include "frmweightable.h"
#include "frmweighedit.h"
#include "ui_frmweightable.h"

FrmWeighTable::FrmWeighTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmWeighTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmWeighTable::~FrmWeighTable()
{
    delete ui;
}

void FrmWeighTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "检斤编号" << "凭证号" << "车牌号" << "重检重量" << "重检时间" << "重检人" << "重检备注"\
           << "空检重量" << "空检时间" << "空检人" << "空检备注" << "净重量" << "图片索引" << "创建人" \
           << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmWeighTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmWeighTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmWeighTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmWeighTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmWeighTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmWeighTable::onDeleteRow);
}

void FrmWeighTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmWeighEdit *editFrm = new FrmWeighEdit(this);
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
void FrmWeighTable::queryTableData(qint32 page, qint32 perPage, const QString& field, const QString &name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryWeigh);
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

void FrmWeighTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmWeighTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","","");
}

void FrmWeighTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmWeighTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmWeighTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_fieldName = ui->cbxField->currentText();
    m_fieldContent = ui->editField->text();
    queryTableData(1, m_perPage, m_fieldName, m_fieldContent, m_startTime, m_endTime);
}

void FrmWeighTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmWeighTable::on_editField_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmWeighTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmWeighTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmWeighTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmWeighTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmWeighTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmWeighTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

