#include "frmselltable.h"
#include "frmselledit.h"
#include "ui_frmselltable.h"

FrmSellTable::FrmSellTable(QWidget *parent) :
    QWidget(parent),
    FrmTableBase(),
    ui(new Ui::FrmSellTable)
{
    ui->setupUi(this);
    this->initForm();
}

FrmSellTable::~FrmSellTable()
{
    delete ui;
}

void FrmSellTable::initForm()
{
    ui->dateStart->setDateTime(QDateTime::currentDateTime());
    ui->dateEnd->setDateTime(QDateTime::currentDateTime());
    QStringList header;
    header << "编号" << "车牌号码" << "出售状态" << "创建人" << "创建日期" << "更新人" << "更新日期";
    ui->tableWidget->setTableColumnHeader(header);
    connect(ui->tableWidget,&GbsTableWidget::evtFristBtnClicked,this,&FrmSellTable::onFirstBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtNextBtnClicked,this,&FrmSellTable::onNextBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtPreviousClicked,this,&FrmSellTable::onPreviousBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtLastBtnClicked,this,&FrmSellTable::onLastBtnClicked);
    connect(ui->tableWidget,&GbsTableWidget::evtAlterRow,this,&FrmSellTable::onAlterRow);
    connect(ui->tableWidget,&GbsTableWidget::evtDeleteRow,this,&FrmSellTable::onDeleteRow);
}

void FrmSellTable::editData(QString editStatus,const QStringList &rowData)
{
    FrmSellEdit *editFrm = new FrmSellEdit(this);
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
void FrmSellTable::queryTableData(qint32 page, qint32 perPage, const QString& name,\
                                  const QString& startTime, const QString& endTime)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerySell);
    session.addRequestData("Sender","Admin");
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

void FrmSellTable::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->close();
    this->deleteLater();
}

void FrmSellTable::onEventShowTableData()
{
    queryTableData(1, m_perPage,"","","");
}

void FrmSellTable::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_firstShow){
        QTimer::singleShot(10,this,&FrmSellTable::onEventShowTableData);
        m_firstShow = true;
    }
}

void FrmSellTable::on_btnQuery_clicked()
{
    m_startTime = ui->dateStart->date().toString("yyyy-MM-dd");
    m_endTime = ui->dateEnd->date().addDays(1).toString("yyyy-MM-dd");
    m_liscense = ui->editName->text();
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellTable::on_btnRefresh_clicked()
{
    queryTableData(1, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellTable::on_editName_returnPressed()
{
    on_btnQuery_clicked();
}

void FrmSellTable::onFirstBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellTable::onNextBtnClicked(quint32 page)
{
     queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellTable::onPreviousBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellTable::onLastBtnClicked(quint32 page)
{
    queryTableData(page, m_perPage,m_liscense,m_startTime,m_endTime);
}

void FrmSellTable::onAlterRow(const QStringList &row)
{
    editData("alter",row);
}

void FrmSellTable::onDeleteRow(const QStringList &row)
{
    editData("delete",row);
}

void FrmSellTable::on_btnAdd_clicked()
{
    editData("add",QStringList());
}

