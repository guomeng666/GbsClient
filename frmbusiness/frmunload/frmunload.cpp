#include "frmunload.h"
#include "gbstoolfunctions.h"
#include "ui_frmunload.h"
#include <QDebug>
#include <QBuffer>
#include <QPixmap>

FrmUnload::FrmUnload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmUnload)
{
    ui->setupUi(this);
    this->initBtn();
    this->initForm();
//    initStyle();
}

FrmUnload::~FrmUnload()
{
    delete ui;
}

void FrmUnload::initForm()
{

}

void FrmUnload::initStyle()
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

void FrmUnload::initBtn()
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

void FrmUnload::topButtonClick()
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

void FrmUnload::onMenuButtonClick()
{

}


void FrmUnload::editBusinessInformation(QString editStatus)
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


void FrmUnload::submitTakeInfo()
{
    //如果校验数据没有任何问题,向服务器发送扦样完成信息
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditWeigh);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation","add");
    session.addRequestData("Number","");
    session.addRequestData("RegisterID",m_currentRegisterID); // 查询时获得的登记编号


    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        QMessageBox::information(NULL,"系统提示","保存成功","确定");
    }else{
        QMessageBox::information(NULL,"系统提示","保存失败:"+session.getErrMsg(),"确定");
    }
}

void FrmUnload::on_btnSubmit_clicked()
{
    submitTakeInfo();
}

void FrmUnload::on_comboBox_currentIndexChanged(int index)
{
    ui->stackedWidgetTake->setCurrentIndex(index);
}
