#include "frmassayedit.h"
#include "gbstoolfunctions.h"
#include "ui_frmassayedit.h"

FrmAssayEdit::FrmAssayEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmAssayEdit),
    m_number(0)
{
    ui->setupUi(this);
    initForm();
    m_editStatus = "add";
}

FrmAssayEdit::~FrmAssayEdit()
{
    delete ui;
}

void FrmAssayEdit::initForm()
{
}

void FrmAssayEdit::setEditType(const QString type)
{
    if(type == "alter"){
        ui->labTitle->setText("化验信息");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmAssayEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmAssayEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(12).toInt();
    editRoleData("delete");
}

void FrmAssayEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmAssayEdit::onEventShowDetail);
}

void FrmAssayEdit::onEventShowDetail()
{
    m_number = m_detailData.at(0).toInt();
    ui->labAssayNum->setText(m_detailData.at(0));
    ui->labGrainType->setText(m_detailData.at(1));
    ui->labClass->setText(m_detailData.at(2));
    ui->labSampleBox->setText(m_detailData.at(3));
    ui->labStandard->setText(m_detailData.at(4));
    ui->editBugNUm->setText(m_detailData.at(5));
    ui->editRZ->setText(m_detailData.at(6));
    ui->editSF->setText(m_detailData.at(7));
    ui->editMB->setText(m_detailData.at(8));
    ui->editPS->setText(m_detailData.at(9));
    ui->editRS->setText(m_detailData.at(10));
    ui->editBJZ->setText(m_detailData.at(11));
    ui->editXSZ->setText(m_detailData.at(12));
    ui->editTK->setText(m_detailData.at(13));
    ui->editBX->setText(m_detailData.at(14));
    ui->editYZL->setText(m_detailData.at(15));
    ui->editSPL->setText(m_detailData.at(16));
    ui->cbxSmell->setCurrentText(m_detailData.at(17));
    ui->editMZ->setText(m_detailData.at(18));
    ui->editJZ->setText(m_detailData.at(19));
    ui->editZZ->setText(m_detailData.at(20));
    ui->labComplete->setText(m_detailData.at(21));
    ui->labReject->setText(m_detailData.at(22));
    ui->editReject->setText(m_detailData.at(23));
    ui->editRemark->setText(m_detailData.at(24));
}

void FrmAssayEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){

    }
    GbsSession session;
    session.addRequestData("Cmd",CmdEditAssay);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("UnitWeight",ui->editRZ->text());
    session.addRequestData("Moisture",ui->editSF->text());
    session.addRequestData("Impurity",ui->editZZ->text());
    session.addRequestData("Mildew",ui->editMB->text());
    session.addRequestData("Broken",ui->editPS->text());
    session.addRequestData("HeatHarm",ui->editRS->text());
    session.addRequestData("SideImpurity",ui->editBJZ->text());
    session.addRequestData("Scree",ui->editXSZ->text());
    session.addRequestData("SoilBlock",ui->editTK->text());
    session.addRequestData("RodCore",ui->editBX->text());
    session.addRequestData("DifGrain",ui->editYZL->text());
    session.addRequestData("BlistersGrain",ui->editSPL->text());
    session.addRequestData("PeculiarSmell",QString::number(ui->cbxSmell->currentIndex()));
    session.addRequestData("RoughWeight",ui->editMZ->text());
    session.addRequestData("NetWeight",ui->editJZ->text());
    session.addRequestData("SampleBag",ui->editBugNUm->text());
    session.addRequestData("Remarks",ui->editRemark->text());
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

void FrmAssayEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}

void FrmAssayEdit::on_btnReturn_clicked()
{
    reject();
}
