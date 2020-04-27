#include "frmvaluationlist.h"
#include "frmrule.h"
#include "ui_frmvaluationlist.h"
#include "serialize.h"
#include <QDebug>
#include <QBuffer>
#include <QDataStream>

FrmValuationList::FrmValuationList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmValuationList)
{
    ui->setupUi(this);
}

FrmValuationList::~FrmValuationList()
{
    delete ui;
}

void FrmValuationList::setTitleText(const QString &text)
{
    ui->groupBox->setTitle(text);
}

QString FrmValuationList::getTitleText()
{
    return ui->groupBox->title();
}

qint32 FrmValuationList::getRuleCount()
{
    return ui->listWidget->count();
}

bool FrmValuationList::isHaveRejectRule()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        if(ui->listWidget->item(i)->text().contains("拒收"))
            return true;
    }
    return false;
}

QList<QByteArray> FrmValuationList::getListItemData()
{
    QList<QByteArray> listArray;
    for(int i = 0; i < ui->listWidget->count(); ++i){
        listArray << ui->listWidget->item(i)->data(Qt::UserRole).toByteArray();
    }
    return listArray;
}

void FrmValuationList::setRuleItem(QByteArray &data)
{
    QByteArray serialData = data;
    Serialize in(&serialData);
    QString ruleType;
    in >> ruleType;
    if(ruleType == "rule"){
        QString symbolGreate, max, symbolLess, min, rejectRation;
        in >> symbolGreate >> min >> symbolLess >> max >> rejectRation;
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(Qt::UserRole,serialData);
        item->setText("收购: "+ symbolGreate + max + "% " + symbolLess + min + "%  扣重比:" + rejectRation +"%");
        ui->listWidget->addItem(item);
    }else if(ruleType == "reject"){
        QString rejectValue;
        in >> rejectValue;
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(Qt::UserRole,serialData);
        item->setText("拒收:"+ rejectValue + "%");
        ui->listWidget->addItem(item);
    }
}

void FrmValuationList::on_btnUp_clicked()
{
    QListWidgetItem *selectItem = ui->listWidget->currentItem();
    qint32 row = ui->listWidget->currentRow();
    if(selectItem != nullptr && row > 0){
        QListWidgetItem *newItem=selectItem->clone();
        delete selectItem;
        ui->listWidget->insertItem(row - 1, newItem);
        ui->listWidget->setCurrentItem(newItem);
    }
}

void FrmValuationList::on_btnDown_clicked()
{
    QListWidgetItem *selectItem = ui->listWidget->currentItem();
    qint32 row = ui->listWidget->currentRow();
    if(selectItem != nullptr && row < ui->listWidget->count()-1){
        QListWidgetItem *newItem=selectItem->clone();
        delete selectItem;
        ui->listWidget->insertItem(row+1, newItem);
        ui->listWidget->setCurrentItem(newItem);
    }
}

void FrmValuationList::on_btnAddRule_clicked()
{
    FrmRule ruleDialog;
    int res = ruleDialog.exec();
    if(res == 1){
        QByteArray serialData = ruleDialog.getRule();
        setRuleItem(serialData);
    }
}

void FrmValuationList::on_btnDelRule_clicked()
{
    QListWidgetItem *selectItem = ui->listWidget->currentItem();
    delete selectItem;
}
