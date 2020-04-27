#include "gbstablewidget.h"
#include "ui_gbstablewidget.h"
#include <QDebug>

GbsTableWidget::GbsTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GbsTableWidget),
    m_total(0),
    m_curPage(0),
    m_perPage(20),
    m_totalPage(0)
{
    ui->setupUi(this);
    initWidget();
    initMenu();
}

GbsTableWidget::~GbsTableWidget()
{
    delete ui;
}

void GbsTableWidget::initWidget()
{
    ui->tableWidget->setRowCount(m_perPage);
    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏行标
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择模式，选择单行
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->setAlternatingRowColors(true);
    connect(ui->tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(onRecordSortbyClounm(int)));
}

void GbsTableWidget::initMenu()
{
    QList<QAction*> actionList;
    m_tableMenu = new QMenu(ui->tableWidget);
    actionList << new QAction("修改",m_tableMenu);
    actionList << new QAction("删除",m_tableMenu);
    m_tableMenu->addActions(actionList);
    foreach (QAction* action, actionList) {
        connect(action,&QAction::triggered,this,&GbsTableWidget::onEvtTableMenuAction);
    }
}

void GbsTableWidget::setTableColumnHeader(QStringList &header)
{
    ui->tableWidget->setColumnCount(header.size()); //设置列数
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(int i = 0; i< header.count(); ++i) {
        if(header.at(i).contains("日期")){
            ui->tableWidget->setColumnWidth(i, 200);
        }else if(header.at(i).contains("身份证")){
            ui->tableWidget->setColumnWidth(i, 250);
        }else if(header.at(i).contains("号码")){
            ui->tableWidget->setColumnWidth(i, 250);
        }else if(header.at(i).contains("流程顺序")){
            ui->tableWidget->setColumnWidth(i, 400);
        }else if(header.at(i).contains("详细规则")){
            m_hideCloumn = i;
        }
    }
    if(m_hideCloumn != 0)
        ui->tableWidget->hideColumn(m_hideCloumn);
}

void GbsTableWidget::setTableData(quint32 total, quint32 curPage,
                                  QList<QStringList> tableData)
{
    m_tableData = tableData;
    m_total = total;
    m_curPage = curPage;
    showTableData();
}


void GbsTableWidget::showTableData()
{
    ui->tableWidget->clearContents();
    m_totalPage = m_total/m_perPage;
    if(m_total%m_perPage != 0){
        m_totalPage++;
    }
    //行遍历
    for(qint32 i = 0; i < m_tableData.size(); ++i ) {
        QStringList row = m_tableData.at(i);
        //列遍历
        for(qint32 j = 0; j <row.size(); ++j){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(row.at(j)));
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(row.at(j)));
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(row.at(j)));
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(row.at(j)));
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(row.at(j)));
        }
    }
    ui->labTotal->setText(QString::number(m_total));
    ui->labPage->setText(QString::number(m_curPage)+"/"+QString::number(m_totalPage));
    setPageBtnStatus();
}

void GbsTableWidget::setPageBtnStatus()
{
    if(m_totalPage - m_curPage != 0){ //总页数 - 当前页数 不等于0 说明还有页
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
    }else{
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
    if(m_curPage > 1)
    {
        ui->btnFirst->setEnabled(true);
        ui->btnPrevious->setEnabled(true);
    }else{
        ui->btnFirst->setEnabled(false);
        ui->btnPrevious->setEnabled(false);
    }
}

QStringList GbsTableWidget::getSelectedRowData()
{
    QStringList listContent;
    int row = ui->tableWidget->currentRow();
    int columnCnt = ui->tableWidget->columnCount();
    for(int i = 0; i < columnCnt; ++i){
        QTableWidgetItem *item = ui->tableWidget->item(row,i);
        if(item == nullptr)
            break;
        QString content = item->text(); //获取内容
        listContent << content;
    }
    return listContent;
}

void GbsTableWidget::on_btnFirst_clicked()
{
    emit evtFristBtnClicked(1);
}

void GbsTableWidget::on_btnPrevious_clicked()
{
    emit evtPreviousClicked(--m_curPage);
}

void GbsTableWidget::on_btnNext_clicked()
{
    emit evtNextBtnClicked(++m_curPage);
}

void GbsTableWidget::on_btnLast_clicked()
{
    emit evtLastBtnClicked(m_totalPage);
}

void GbsTableWidget::onEvtTableMenuAction()
{
    QAction* pAction = (QAction*)sender();
    QString actionText = pAction->text();
    if(actionText == "修改"){
        emit evtAlterRow(getSelectedRowData());
    }else if(actionText == "删除"){
        emit evtDeleteRow(getSelectedRowData());
    }
}

void GbsTableWidget::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QStringList rowDetail = getSelectedRowData();
    if(rowDetail.isEmpty()){

    }else{
        emit evtAlterRow(rowDetail);
    }
}

void GbsTableWidget::onRecordSortbyClounm(int column)
{
    static bool desc = false;
    if(desc){
        ui->tableWidget->sortItems(column,Qt::DescendingOrder);
        desc = false;
    }else{
        ui->tableWidget->sortItems(column,Qt::AscendingOrder);
        desc = true;
    }
}

void GbsTableWidget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    m_tableMenu->exec(QCursor::pos());
}


