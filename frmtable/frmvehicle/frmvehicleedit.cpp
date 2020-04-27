#include "frmvehicleedit.h"
#include "gbstoolfunctions.h"
#include "ui_frmvehicleedit.h"

FrmVehicleEdit::FrmVehicleEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmVehicleEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmVehicleEdit::~FrmVehicleEdit()
{
    delete ui;
}

void FrmVehicleEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("权限添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("权限修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmVehicleEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmVehicleEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmVehicleEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmVehicleEdit::onEventShowDetail);
}

void FrmVehicleEdit::onEventShowDetail()
{
    getVehicleTypeItem();
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 9);
        m_number = m_detailData.at(0).toInt();
        ui->editName->setText(m_detailData.at(1));
        ui->comboBox->setCurrentText(m_detailData.at(2));
        ui->editColor->setText(m_detailData.at(3));
        ui->editFrameID->setText(m_detailData.at(4));
    }
}

bool FrmVehicleEdit::checkFrmEditData()
{
    if(ui->editName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","角色名称不能为空","确定");
        return false;
    }
    return true;
}

void FrmVehicleEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditVehicle);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("VehicleLiscence",ui->editName->text());
    session.addRequestData("VehicleType",ui->comboBox->currentData().toString());
    session.addRequestData("VehicleColor",ui->editColor->text());
    session.addRequestData("VehicleFrameId",ui->editFrameID->text());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmVehicleEdit::getVehicleTypeItem()
{
    GbsToolFunctions::setComboxItem(CmdQueryVehicleType,ui->comboBox);
}

void FrmVehicleEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}
