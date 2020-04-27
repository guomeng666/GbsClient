#include "frmregister.h"
#include "frmregistertable.h"
#include "gbstoolfunctions.h"
#include "ui_frmregister.h"
#include <QDebug>
#include <QBuffer>
#include <QPixmap>

FrmRegister::FrmRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmRegister)
{
    ui->setupUi(this);
    this->initBtn();
    this->initForm();
//    initStyle();
}

FrmRegister::~FrmRegister()
{
    delete ui;
}

void FrmRegister::initForm()
{
    setVehicleType();
    setGrainType();
    setPackType();
    setPayMentType();
    setBankType();
    ui->labVedio1->setPixmap(QPixmap::fromImage(QImage(":/image/test1")));
    ui->labVedio2->setPixmap(QPixmap::fromImage(QImage(":/image/test2")));
    ui->labVedio3->setPixmap(QPixmap::fromImage(QImage(":/image/test3")));
    ui->labVedio4->setPixmap(QPixmap::fromImage(QImage(":/image/test4")));
}

void FrmRegister::setVehicleType()
{
    GbsToolFunctions::setComboxItem(CmdQueryVehicleType,ui->cbxVehicleType);
}

void FrmRegister::setGrainType()
{
    GbsToolFunctions::setComboxItem(CmdQueryGrainType,ui->cbxGrainType);
}

void FrmRegister::setPackType()
{
    GbsToolFunctions::setComboxItem(CmdQueryPackType,ui->cbxPackType);
}

void FrmRegister::setPayMentType()
{
    GbsToolFunctions::setComboxItem(CmdQueryPaymenttype,ui->cbxPayType);
}

void FrmRegister::setBankType()
{
    GbsToolFunctions::setComboxItem(CmdQueryBankType,ui->cbxBankType);
}

void FrmRegister::on_cbxpurchase_currentIndexChanged(int index)
{
    ui->stkWidgetPurchase->setCurrentIndex(index);
}

void FrmRegister::initStyle()
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

void FrmRegister::initBtn()
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

void FrmRegister::topButtonClick()
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

void FrmRegister::onMenuButtonClick()
{

}

bool FrmRegister::checkFrmEditData(PurchaseType type)
{
    if(ui->editLiscense->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","车牌号码不能为空","确定");
        return false;
    }
    if(ui->editFrameNum->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","车架号码不能为空","确定");
        return false;
    }
    if(ui->editColor->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","车辆颜色不能为空","确定");
        return false;
    }
    if(ui->editTagNum->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","电子标签号码不能为空","确定");
        return false;
    }
    if(ui->editICNum->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","IC卡号码不能为空","确定");
        return false;
    }

    if(type == Contarct){
        if(ui->editContractNum->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","合同号码不能为空","确定");
            return false;
        }
        if(ui->editDriverAddress->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","司机身份证号码不能为空","确定");
            return false;
        }
        if(ui->editDriverName->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","司机姓名不能为空","确定");
            return false;
        }
        if(ui->editDriverNum->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","司机身份证号码不能为空","确定");
            return false;
        }
        if(ui->editDriverPhone->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","司机电话不能为空","确定");
            return false;
        }
    }else if(type == Scattered){
        if(ui->editSellerAddress->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","售粮人身份证地址不能为空","确定");
            return false;
        }
        if(ui->editSellerName->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","售粮人名字不能为空","确定");
            return false;
        }
        if(ui->editSellerNum->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","售粮人身份证号码不能为空","确定");
            return false;
        }
        if(ui->editSellerPhone->text().isEmpty()){
            QMessageBox::warning(NULL,"系统提示","售粮人电话不能为空","确定");
            return false;
        }
    }
    return true;
}

void FrmRegister::editBusinessInformation(QString editStatus)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditRegister);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number","0");
    session.addRequestData("PurchaseType",ui->cbxpurchase->currentText());
    session.addRequestData("ContractNum",ui->editContractNum->text());
    session.addRequestData("VehicleLiscence",ui->editLiscense->text());
    session.addRequestData("VehicleType",ui->cbxVehicleType->currentData().toString());
    session.addRequestData("VehicleColor",ui->editColor->text());
    session.addRequestData("VehicleFrameId",ui->editFrameNum->text());
    session.addRequestData("DriverNum",ui->editDriverNum->text());
    session.addRequestData("DriverName",ui->editDriverName->text());
    session.addRequestData("DriverAddress ",ui->editDriverAddress->text());
    session.addRequestData("DriverPhone",ui->editDriverPhone->text());
    session.addRequestData("SellerNum",ui->editSellerNum->text());
    session.addRequestData("SellerName",ui->editSellerName->text());
    session.addRequestData("SellerAddress",ui->editSellerAddress->text());
    session.addRequestData("SellerPhone",ui->editSellerPhone->text());
    session.addRequestData("PayeeNum",ui->editPayeeNum->text());
    session.addRequestData("PayeeName",ui->editPayeeName->text());
    session.addRequestData("PayeeAddress",ui->editPayeeAddress->text());
    session.addRequestData("PayeePhone",ui->editPayeePhone->text());
    session.addRequestData("PayeeBankType",ui->cbxBankType->currentData().toString());
    session.addRequestData("PayeeBankNum",ui->editBankNum->text());
    session.addRequestData("PayMentType",ui->cbxPayType->currentData().toString());
    session.addRequestData("PackType",ui->cbxPackType->currentData().toString());
    session.addRequestData("GrainType",ui->cbxGrainType->currentData().toString());
    session.addRequestData("TagNum",ui->editTagNum->text());
    session.addRequestData("TagStatus",ui->labTagStatus->text());
    session.addRequestData("ICID",ui->editICNum->text());
    session.addRequestData("Remarks",ui->editRemark->text());
    session.addRequestData("Pircture1",GbsToolFunctions::lablePixmapToString(ui->labVedio1));
    session.addRequestData("Pircture2",GbsToolFunctions::lablePixmapToString(ui->labVedio2));
    session.addRequestData("Pircture3",GbsToolFunctions::lablePixmapToString(ui->labVedio3));
    session.addRequestData("Pircture4",GbsToolFunctions::lablePixmapToString(ui->labVedio4));
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        QMessageBox::information(NULL,"系统提示","提交数据成功","确定");
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmRegister::getPricture()
{
    GbsToolFunctions::lablePixmapToString(ui->labVedio1);
    GbsToolFunctions::lablePixmapToString(ui->labVedio2);
    GbsToolFunctions::lablePixmapToString(ui->labVedio3);
    GbsToolFunctions::lablePixmapToString(ui->labVedio4);
}

void FrmRegister::on_btnSave_clicked()
{
    qDebug()<<"提交信息";
    if(ui->cbxpurchase->currentText() == "散收粮"){
        if(checkFrmEditData(PurchaseType::Scattered)){
            editBusinessInformation("add");
        }
    }else if(ui->cbxpurchase->currentText() == "合同粮"){
        if(checkFrmEditData(PurchaseType::Contarct)){
            if(GbsToolFunctions::contractIsValid(ui->editContractNum->text())){
                editBusinessInformation("add");
            }else{
                QMessageBox::warning(NULL,"系统提示","输入的合同号码不存在","确定");
            }
        }
    }
}

void FrmRegister::on_editSellerNum_returnPressed()
{
    QStringList result;
    if(GbsToolFunctions::getSellerInfoByIdentityID(ui->editSellerNum->text(),result)){
       ui->editSellerName->setText(result.at(1));
       ui->editSellerAddress->setText(result.at(3));
       ui->editSellerPhone->setText(result.at(4));
    }else{
       QMessageBox::warning(NULL,"系统提示",result.at(0),"确定");
    }
}

void FrmRegister::on_editPayeeNum_returnPressed()
{
    QStringList result;
    if(GbsToolFunctions::getSellerInfoByIdentityID(ui->editPayeeNum->text(),result)){
        ui->editPayeeName->setText(result.at(1));
        ui->editPayeeAddress->setText(result.at(3));
        ui->editPayeePhone->setText(result.at(4));
        if(!result.at(5).isEmpty()){
            ui->cbxBankType->setCurrentText(result.at(5));
        }
        if(!result.at(6).isEmpty()){
            ui->editBankNum->setText(result.at(6));
        }
    }else{
       QMessageBox::warning(NULL,"系统提示",result.at(0),"确定");
    }
}

void FrmRegister::on_editLiscense_returnPressed()
{
    QStringList result;
    if(GbsToolFunctions::getVehicleByLiscense(ui->editLiscense->text(),result)){
        ui->cbxVehicleType->setCurrentText(result.at(2));
        ui->editColor->setText(result.at(3));
        ui->editFrameNum->setText(result.at(4));
    }else{
        QMessageBox::warning(NULL,"系统提示",result.at(0),"确定");
     }
}

void FrmRegister::on_btnClear_clicked()
{
    getPricture();
}

void FrmRegister::on_editDriverNum_returnPressed()
{
    QStringList result;
    if(GbsToolFunctions::getSellerInfoByIdentityID(ui->editDriverNum->text(),result)){
        ui->editDriverName->setText(result.at(1));
        ui->editDriverAddress->setText(result.at(3));
        ui->editDriverPhone->setText(result.at(4));
    }else{
       QMessageBox::warning(NULL,"系统提示",result.at(0),"确定");
    }
}
