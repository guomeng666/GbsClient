#include "frmsamplingedit.h"
#include "gbstoolfunctions.h"
#include "ui_frmsamplingedit.h"

FrmSamplingEdit::FrmSamplingEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSamplingEdit),
    m_number(0)
{
    ui->setupUi(this);
    initForm();
    m_editStatus = "add";
}

FrmSamplingEdit::~FrmSamplingEdit()
{
    delete ui;
}

void FrmSamplingEdit::initForm()
{
    ui->editColor->setEnabled(false);
    ui->editFrameNum->setEnabled(false);
    ui->editLiscense->setEnabled(false);
    ui->editOperator->setEnabled(false);
    ui->editTagNum->setEnabled(false);
    ui->cbxVehicleType->setEnabled(false);
}

void FrmSamplingEdit::setEditType(const QString type)
{
    if(type == "alter"){
        ui->labTitle->setText("扦样信息");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmSamplingEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmSamplingEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(12).toInt();
    editRoleData("delete");
}

void FrmSamplingEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmSamplingEdit::onEventShowDetail);
}

void FrmSamplingEdit::onEventShowDetail()
{
    setVehicleType();
    m_number = m_detailData.at(0).toInt();
    ui->labMainNum->setText(m_detailData.at(1));
    ui->editLiscense->setText(m_detailData.at(2));
    ui->cbxVehicleType->setCurrentText(m_detailData.at(3));
    ui->editFrameNum->setText(m_detailData.at(4));
    ui->editColor->setText(m_detailData.at(5));
    ui->editTagNum->setText(m_detailData.at(6));
    ui->editRemarks->setText(m_detailData.at(7));
    m_pictureID = m_detailData.at(8).toInt();
    ui->editOperator->setText(m_detailData.at(9));
    if(m_pictureID != 0){
        m_listImage = GbsToolFunctions::getImageFromService("Sampling",QString::number(m_pictureID));
        ui->imageWidget->setImages(m_listImage);
    }
}

void FrmSamplingEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){

    }
    GbsSession session;
    session.addRequestData("Cmd",CmdEditSamling);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("VehicleLiscence",ui->editLiscense->text());
    session.addRequestData("VehicleType",ui->cbxVehicleType->currentData().toString());
    session.addRequestData("VehicleColor",ui->editColor->text());
    session.addRequestData("VehicleFrameId",ui->editFrameNum->text());
    session.addRequestData("TagNum",ui->editTagNum->text());
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

void FrmSamplingEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}


void FrmSamplingEdit::setVehicleType()
{
    GbsToolFunctions::setComboxItem(CmdQueryVehicleType,ui->cbxVehicleType);
}

void FrmSamplingEdit::on_btnReturn_clicked()
{
    reject();
}
