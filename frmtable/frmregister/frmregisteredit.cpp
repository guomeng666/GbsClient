#include "frmregisteredit.h"
#include "gbstoolfunctions.h"
#include "ui_frmregisteredit.h"

FrmRegisterEdit::FrmRegisterEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmRegisterEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmRegisterEdit::~FrmRegisterEdit()
{
    delete ui;
}

void FrmRegisterEdit::setEditType(const QString type)
{
    if(type == "alter"){
        ui->labTitle->setText("登记信息");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmRegisterEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmRegisterEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmRegisterEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmRegisterEdit::onEventShowDetail);
}

void FrmRegisterEdit::onEventShowDetail()
{
    //setPurchaseType();
    setVehicleType();
    setGrainType();
    setPackType();
    setPayMentType();
    setBankType();
    m_number = m_detailData.at(0).toInt();
    ui->labMainNum->setText(QString::number(m_number));
    ui->cbxPurchaseType->setCurrentText(m_detailData.at(1));
    ui->editContractNum->setText(m_detailData.at(2));
    ui->cbxGrainType->setCurrentText(m_detailData.at(3));
    ui->cbxPackType->setCurrentText(m_detailData.at(4));
    ui->cbxPayType->setCurrentText(m_detailData.at(5));
    ui->editTagNum->setText(m_detailData.at(6));
    ui->editICNum->setText(m_detailData.at(7));
    ui->editLiscense->setText(m_detailData.at(8));
    ui->cbxVehicleType->setCurrentText(m_detailData.at(9));
    ui->editColor->setText(m_detailData.at(10));
    ui->editFrameNum->setText(m_detailData.at(11));
    ui->editSellerName->setText(m_detailData.at(12));
    ui->editSellerNum->setText(m_detailData.at(13));
    ui->editSellerAddress->setText(m_detailData.at(14));
    ui->editSellerPhone->setText(m_detailData.at(15));
    ui->editPayeeName->setText(m_detailData.at(16));
    ui->editPayeeNum->setText(m_detailData.at(17));
    ui->editPayeeAddress->setText(m_detailData.at(18));
    ui->editPayeePhone->setText(m_detailData.at(19));
    ui->cbxBankType->setCurrentText(m_detailData.at(20));
    ui->editBankNum->setText(m_detailData.at(21));
    ui->editDriverName->setText(m_detailData.at(22));
    ui->editDriverNum->setText(m_detailData.at(23));
    ui->editDriverAddress->setText(m_detailData.at(24));
    ui->editDriverPhone->setText(m_detailData.at(25));
    ui->editRemarks->setText(m_detailData.at(26));
    m_pictureID = m_detailData.at(27).toInt();
    if(m_pictureID != 0){
        m_listImage = GbsToolFunctions::getImageFromService("Register",QString::number(m_pictureID));
        ui->imageWidget->setImages(m_listImage);
    }
}

void FrmRegisterEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(ui->cbxPurchaseType->currentText() == "散收粮"){
            if(!checkFrmEditData(PurchaseType::Scattered)){
                return;
            }
        }else{
            if(!checkFrmEditData(PurchaseType::Contarct)){
                return;
            }
        }
    }
    if(!GbsToolFunctions::contractIsValid(ui->editContractNum->text())){
        QMessageBox::warning(NULL,"系统提示","修改的合同号码不存在","确定");
        return;
    }
    GbsSession session;
    session.addRequestData("Cmd",CmdEditRegister);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("PurchaseType",ui->cbxPurchaseType->currentText());
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
    session.addRequestData("ICID",ui->editICNum->text());
    session.addRequestData("Remarks",ui->editRemarks->text());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        QMessageBox::information(NULL,"系统提示","数据修改成功","确定");
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmRegisterEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}

void FrmRegisterEdit::setPurchaseType()
{
    GbsToolFunctions::setComboxItem(CmdQueryPurchase,ui->cbxPurchaseType);
}

void FrmRegisterEdit::setVehicleType()
{
    GbsToolFunctions::setComboxItem(CmdQueryVehicleType,ui->cbxVehicleType);
}

void FrmRegisterEdit::setGrainType()
{
    GbsToolFunctions::setComboxItem(CmdQueryGrainType,ui->cbxGrainType);
}

void FrmRegisterEdit::setPackType()
{
    GbsToolFunctions::setComboxItem(CmdQueryPackType,ui->cbxPackType);
}

void FrmRegisterEdit::setPayMentType()
{
    GbsToolFunctions::setComboxItem(CmdQueryPaymenttype,ui->cbxPayType);
}

void FrmRegisterEdit::setBankType()
{
    GbsToolFunctions::setComboxItem(CmdQueryBankType,ui->cbxBankType);
}

bool FrmRegisterEdit::checkFrmEditData(PurchaseType type)
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
