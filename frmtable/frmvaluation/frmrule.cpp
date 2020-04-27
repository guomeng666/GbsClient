#include "frmrule.h"
#include "ui_frmrule.h"
#include "serialize.h"
#include <QDebug>
#include <QBuffer>
#include <QMessageBox>

FrmRule::FrmRule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmRule)
{
    ui->setupUi(this);
}

FrmRule::~FrmRule()
{
    delete ui;
}



void FrmRule::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "收购规则"){
        ui->stackedWidget->setCurrentIndex(1);
    }else if(arg1 == "拒收规则"){
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void FrmRule::on_btnOk_clicked()
{
    if(!checkRules()) return;
    Serialize out(&m_rule);
    if(ui->comboBox->currentText() == "收购规则"){
        out <<"rule"<< ui->cbxGreater->currentText() << ui->editMin->text()\
               << ui->cbxLess->currentText() << ui->editMax->text()\
               << ui->editRatio->text() << ui->editRatio->text();
    }else if(ui->comboBox->currentText() == "拒收规则"){
        out <<"reject"<< ui->editReject->text();
    }
    done(1);
}

bool FrmRule::checkRules()
{
    if(ui->comboBox->currentText().contains("收购")){
        if(ui->editMax->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","收购规则最大值内容不能为空!","确定");
            return false;
        }else if(ui->editMin->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","收购规则最小值内容不能为空!","确定");
            return false;
        }else if(ui->editRatio->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","收购规则扣重比例内容不能为空!","确定");
            return false;
        }
    }else if(ui->comboBox->currentText().contains("拒收")){
        if(ui->editReject->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","拒收规则内容不能为空!","确定");
            return false;
        }
    }
    return true;
}
