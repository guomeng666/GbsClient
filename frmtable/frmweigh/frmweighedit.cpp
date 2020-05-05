#include "frmweighedit.h"
#include "gbstoolfunctions.h"
#include "ui_frmweighedit.h"

FrmWeighEdit::FrmWeighEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmWeighEdit),
    m_number(0)
{
    ui->setupUi(this);
    initForm();
    m_editStatus = "add";
}

FrmWeighEdit::~FrmWeighEdit()
{
    delete ui;
}

void FrmWeighEdit::initForm()
{
}

void FrmWeighEdit::setEditType(const QString type)
{
    if(type == "alter"){
        ui->labTitle->setText("扦样信息");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmWeighEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmWeighEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(12).toInt();
    editRoleData("delete");
}

void FrmWeighEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmWeighEdit::onEventShowDetail);
}

void FrmWeighEdit::onEventShowDetail()
{
    m_number = m_detailData.at(0).toInt();
    ui->labWeighNum->setText(m_detailData.at(0));
    ui->labRegisterNum->setText(m_detailData.at(1));
    ui->editLiscense->setText(m_detailData.at(2));
    ui->editRouthWeight->setText(m_detailData.at(3));
    ui->editRoughDate->setText(m_detailData.at(4));
    ui->editRoughtOperator->setText(m_detailData.at(5));
    ui->editRoughRemarks->setText(m_detailData.at(6));
    ui->editTraeWeight->setText(m_detailData.at(7));
    ui->editTraeDate->setText(m_detailData.at(8));
    ui->editTraeOperator->setText(m_detailData.at(9));
    ui->editTraeRemarks->setText(m_detailData.at(10));
    ui->editNetWeight->setText(m_detailData.at(11));
    m_pictureID = m_detailData.at(12).toInt();
    if(m_pictureID != 0){
        m_listImage = GbsToolFunctions::getImageFromService("Weigh",QString::number(m_pictureID));
        ui->imageWeight->setImages(m_listImage);
    }
}

void FrmWeighEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){

    }
    GbsSession session;
    session.addRequestData("Cmd",CmdAlterWeigh);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("RoughtWeight",ui->editRouthWeight->text());
    session.addRequestData("RoughtRemarks",ui->editRoughRemarks->text());
    session.addRequestData("TraeWeight",ui->editTraeWeight->text());
    session.addRequestData("TraeRemarks",ui->editTraeRemarks->text());
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

void FrmWeighEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}

void FrmWeighEdit::on_btnReturn_clicked()
{
    reject();
}
