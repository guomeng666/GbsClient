#include "frmsampling.h"
#include "gbstoolfunctions.h"
#include "ui_frmsampling.h"
#include <QDebug>
#include <QBuffer>
#include <QPixmap>

FrmSampling::FrmSampling(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmSampling)
{
    ui->setupUi(this);
    this->initBtn();
    this->initForm();
//    initStyle();
}

FrmSampling::~FrmSampling()
{
    delete ui;
}

void FrmSampling::initForm()
{
//    ui->labVedio1->setPixmap(QPixmap::fromImage(QImage(":/image/test1")));
//    ui->labVedio2->setPixmap(QPixmap::fromImage(QImage(":/image/test2")));
//    ui->labVedio3->setPixmap(QPixmap::fromImage(QImage(":/image/test3")));
//    ui->labVedio4->setPixmap(QPixmap::fromImage(QImage(":/image/test4")));
}

void FrmSampling::initStyle()
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

void FrmSampling::initBtn()
{
    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
       btn->setProperty("navBtn","true");
       btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
       btn->setCheckable(true);
       connect(btn, SIGNAL(clicked()), this, SLOT(topButtonClick()));
    }

    tbtns.clear();
    //初始化窗口动作按钮
    tbtns = ui->widgetMenu->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
       btn->setProperty("menuBtn","true");
       connect(btn, SIGNAL(clicked()), this, SLOT(onMenuButtonClick()));
    }
    ui->btnWork->setChecked(true);
}

void FrmSampling::topButtonClick()
{
    QToolButton* b = (QToolButton*)sender();
    QString name = b->text();
    if (name == "工作界面") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (name == "查询报表") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (name == "硬件配置") {
        ui->stackedWidget->setCurrentIndex(2);
    } else if (name == "锁定窗口") {

    }
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
       if(btn->text() != name)
       btn->setChecked(false);
    }
}

void FrmSampling::onMenuButtonClick()
{

}


void FrmSampling::editBusinessInformation(QString editStatus)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditRegister);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number","0");
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        QMessageBox::information(NULL,"系统提示","提交数据成功","确定");
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}


