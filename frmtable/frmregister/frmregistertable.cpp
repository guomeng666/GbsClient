#include "frmregistertable.h"
#include "frmregisteredit.h"
#include "ui_frmregistertable.h"

FrmRegisterTable::FrmRegisterTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmRegisterTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmRegisterTable::~FrmRegisterTable()
{
    delete ui;
}

void FrmRegisterTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "凭证号" << "收购类型" << "合同号" << "粮食类型" << "包装类型" << "支付类型" <<"电子标签号" <<"IC卡号"\
           << "车牌号" << "车辆类型" << "车辆颜色" << "车架号"<< "售粮人" << "身份证号码"\
           << "身份证住址" << "联系电话" << "结算人" << "身份证号码" << "身份证住址"\
           << "联系电话" << "结算银行" << "结算银行卡号码" << "司机姓名" << "身份证号码" << "身份证住址" << "联系电话" \
           << "备注" << "图片索引" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmRegisterTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmRegisterTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmRegisterTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmRegisterTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmRegisterTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmRegisterTable::onDeleteRow);
}

void FrmRegisterTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmRegisterEdit *editFrm = new FrmRegisterEdit(this);
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
void FrmRegisterTable::queryTableData(qint32 page, qint32 perPage, const QString& field, const QString &name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryRegister);
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

void FrmRegisterTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmRegisterTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","","");
}

void FrmRegisterTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmRegisterTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmRegisterTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_fieldName = ui->cbxField->currentText();
    m_fieldContent = ui->editField->text();

    queryTableData(1, m_perPage, m_fieldName, m_fieldContent, m_startTime, m_endTime);
}

void FrmRegisterTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmRegisterTable::on_editField_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmRegisterTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmRegisterTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmRegisterTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmRegisterTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_fieldName,m_fieldContent, m_startTime,m_endTime);
}

void FrmRegisterTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmRegisterTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmRegisterTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

