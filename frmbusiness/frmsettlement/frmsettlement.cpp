#include "frmsettlement.h"
#include "gbstoolfunctions.h"
#include "gbssession.h"
#include "servicemanager.h"
#include "ui_frmsettlement.h"
#include "quiwidget.h"
#include <QDebug>

FrmSettlement::FrmSettlement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmSettlement),
    m_countDown(60)
{
    ui->setupUi(this);
    this->initBtn();
    this->initForm();
//    initStyle();
    countDownTimer = new QTimer(this);
    connect(countDownTimer,SIGNAL(timeout()),this, SLOT(onCountDown()));
}

FrmSettlement::~FrmSettlement()
{
    delete ui;
}

void FrmSettlement::initForm()
{

}

void FrmSettlement::initStyle()
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

void FrmSettlement::initBtn()
{

}

void FrmSettlement::querySettlementInfo(QString icNumber)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerySettlement);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Number",icNumber);
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        QStringList res = session.getRow(0);
        ui->labPurchase->setText(res.at(2));
        ui->labGrainType->setText(res.at(3));
        ui->labPack->setText(res.at(4));
        ui->labLicense->setText(res.at(5));
        ui->labVehicleType->setText(res.at(6));
        ui->labColor->setText(res.at(7));
        ui->labRZRatio->setText(res.at(9) + "%");
        ui->labSFRatio->setText(res.at(10) + "%");
        ui->labZZRatio->setText(res.at(11) + "%");
        ui->labMBRatio->setText(res.at(12) + "%");
        ui->labPSRatio->setText(res.at(13) + "%");
        ui->labRSRatio->setText(res.at(14) + "%");
        ui->labBJZRatio->setText(res.at(15) + "%");
        ui->labTotalRatio->setText(res.at(16) + "%");
        ui->labUnloadDeduct->setText(res.at(17) + "KG");
        ui->labRoughtWeight->setText(res.at(18) + "KG");
        ui->labTareWeight->setText(res.at(19) + "KG");
        ui->labNetWeight->setText(res.at(20) + "KG");
        ui->labValidWeight->setText(res.at(21) + "KG");
        ui->labValuation->setText(res.at(22));
        ui->labPrice->setText(res.at(23) + "元");
        ui->labTotalPrice->setText(res.at(24) + "元");
        ui->labSeller->setText(res.at(25));
        ui->labPayType->setText(res.at(26));
        ui->labBankType->setText(res.at(27));
        ui->labBankNum->setText(res.at(28));
        m_countDown = 60;
        ui->lcdNumber->display(m_countDown);
        countDownTimer->start(1000);
        ui->stackedWidget->setCurrentIndex(1);
    }else{
       QUIHelper::showMessageBoxError(session.getErrMsg(), 3, true);
    }
}

void FrmSettlement::clearFrm()
{
}


//输入IC卡号,用于测试用
void FrmSettlement::on_lineEdit_returnPressed()
{
    querySettlementInfo(ui->lineEdit->text());
}

void FrmSettlement::onCountDown()
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

void FrmSettlement::on_btnRetrun_clicked()
{
    countDownTimer->stop();
    ui->stackedWidget->setCurrentIndex(0);
}
