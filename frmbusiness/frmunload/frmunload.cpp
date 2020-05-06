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

void FrmUnload::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    GbsToolFunctions::setComboxItem(CmdQueryWarehouse,ui->cbxWareHouse);
}


void FrmUnload::submitTakeInfo()
{
    //如果校验数据没有任何问题,向服务器发送扦样完成信息
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditUnload);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation","add");
    session.addRequestData("RegisterID",m_currentRegisterID); // 查询时获得的登记编号
    session.addRequestData("WareHouseID",ui->cbxWareHouse->currentData().toString()); // 查询时获得的登记编号
    session.addRequestData("TakeCount",QString::number(ui->doubleSpinBoxBag->value() * ui->editBagNum->text().toInt()));
    session.addRequestData("Remarks",ui->editRemarks->text());
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
    //提交卸粮信息
    submitTakeInfo();
}

//获取车牌号码
void FrmUnload::on_editLiscense_returnPressed()
{
    QStringList result;
    if(GbsToolFunctions::getRegisterByLiscense(ui->editLiscense->text(),result)){
        m_currentRegisterID = result.at(0);
        ui->editPurchase->setText(result.at(1));
        ui->editPackType->setText(result.at(2));
        ui->editGrainType->setText(result.at(3));
        ui->editLiscense->setText(result.at(4));
        ui->editVehicleType->setText(result.at(5));
        ui->editColor->setText(result.at(6));
        ui->editFrameNum->setText(result.at(7));
    }else{
        QMessageBox::warning(NULL,"系统提示",result.at(0),"确定");
     }
}


