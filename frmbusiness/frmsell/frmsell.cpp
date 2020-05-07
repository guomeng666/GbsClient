#include "frmsell.h"
#include "gbstoolfunctions.h"
#include "gbssession.h"
#include "servicemanager.h"
#include "ui_frmsell.h"
#include "quiwidget.h"
#include <QDebug>

FrmSell::FrmSell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmSell),
    m_countDown(60)
{
    ui->setupUi(this);
    this->initBtn();
    this->initForm();
//    initStyle();
    countDownTimer = new QTimer(this);
    connect(countDownTimer,SIGNAL(timeout()),this, SLOT(onCountDown()));
}

FrmSell::~FrmSell()
{
    delete ui;
}

void FrmSell::initForm()
{

}

void FrmSell::initStyle()
{
     QStringList qss;
     //主界面顶部栏
     qss.append("QWidget#widgetTitle{background:qlineargradient"
                "(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #0973AB,stop:1 #098DCE);}"
                "QToolButton::menu-indicator{image:None;}");
     //主界面顶部右上角
     qss.append("QWidget#widgetMenu  QAbstractButton {"
                "border:0px solid #FF0000;}");
     qss.append("QWidget#widgetMenu  QAbstractButton:hover,"
                "QWidget#widgetMenu QAbstractButton:pressed{"
                "background:#067DB8;}");

     qss.append("QWidget#widgetTop  QAbstractButton {"
                "border:0px solid #FF0000;}");
     qss.append("QWidget#widgetTop  QAbstractButton:hover,"
                "QWidget#widgetTop QAbstractButton:pressed{"
                "background:#067DB8;}");
     qApp->setStyleSheet(qss.join(""));
}

void FrmSell::initBtn()
{

}

void FrmSell::queryAssayInfo(QString icNumber)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryAssayToSell);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Number",icNumber);
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
       QStringList res = session.getRow(0);
       ui->labPurchase->setText(res.at(0));
       ui->labGrainType->setText(res.at(1));
       ui->labPack->setText(res.at(2));
       ui->labLicense->setText(res.at(3) );
       ui->labVehicleType->setText(res.at(4));
       ui->labColor->setText(res.at(5));
       ui->labRZ->setText(res.at(6) + "%");
       ui->labSF->setText(res.at(7) + "%");
       ui->labZZ->setText(res.at(8) + "%");
       ui->labMB->setText(res.at(9) + "%");
       ui->labPS->setText(res.at(10) + "%");
       ui->labRS->setText(res.at(11) + "%");
       ui->labBJZ->setText(res.at(12) + "%");
       ui->labXSZ->setText(res.at(13) + "%");
       ui->labTK->setText(res.at(14) + "%");
       ui->labBX->setText(res.at(15) + "%");
       ui->labYZL->setText(res.at(16) + "%");
       ui->labSPL->setText(res.at(17) + "%");
       ui->labYW->setText(res.at(18));
       if(res.at(19) == "是"){
            ui->labStatus->setText("拒收");
            ui->btnConcession->setEnabled(true);
            ui->btnSell->setEnabled(false);
            ui->btnRejectSell->setEnabled(false);
       }
       else{
            ui->labStatus->setText("正常");
            ui->btnSell->setEnabled(true);
            ui->btnRejectSell->setEnabled(true);
            ui->btnConcession->setEnabled(false);
       }
       m_procedureNum = res.at(20);
       ui->stackedWidget->setCurrentIndex(1);
       m_countDown = 60;
       ui->lcdNumber->display(m_countDown);
       countDownTimer->start(1000);
    }else{
       QUIHelper::showMessageBoxError(session.getErrMsg(), 3, true);
    }
}

void FrmSell::clearFrm()
{
    ui->labPurchase->clear();
    ui->labGrainType->clear();
    ui->labPack->clear();
    ui->labLicense->clear();
    ui->labVehicleType->clear();
    ui->labColor->clear();
    ui->labRZ->clear();
    ui->labSF->clear();
    ui->labZZ->clear();
    ui->labMB->clear();
    ui->labPS->clear();
    ui->labRS->clear();
    ui->labBJZ->clear();
    ui->labXSZ->clear();
    ui->labTK->clear();
    ui->labBX->clear();
    ui->labYZL->clear();
    ui->labSPL->clear();
    ui->labYW->clear();
    ui->labStatus->clear();
}

//isSell = 是否出售
void FrmSell::sellGrain(bool isSell)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdSellGrain);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation","add");
    session.addRequestData("Number","");
    session.addRequestData("ProcedureNum",m_procedureNum);
    session.addRequestData("Sell",QString::number(isSell));
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        if(isSell){
            QUIHelper::showMessageBoxInfo("出售成功!", 3, true);
        }
        else{
            QUIHelper::showMessageBoxInfo("拒售成功!", 3, true);
        }
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        if(isSell)
            QUIHelper::showMessageBoxError("出售失败,请重新尝试出售.", 3, true);
        else
            QUIHelper::showMessageBoxError("拒售失败,请重新尝试出售.", 3, true);
    }
}

//输入IC卡号,用于测试用
void FrmSell::on_lineEdit_returnPressed()
{
    queryAssayInfo(ui->lineEdit->text());
}

void FrmSell::onCountDown()
{
    m_countDown--;
    if(m_countDown == 0){
        clearFrm();
        ui->stackedWidget->setCurrentIndex(0);
        countDownTimer->stop();
    }else
    {
        ui->lcdNumber->display(m_countDown);
    }
}

void FrmSell::on_btnRetrun_clicked()
{
    countDownTimer->stop();
    ui->stackedWidget->setCurrentIndex(0);
}

//出售
void FrmSell::on_btnSell_clicked()
{
    sellGrain(true);
}

//拒售
void FrmSell::on_btnRejectSell_clicked()
{
    sellGrain(false);
}
