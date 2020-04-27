#include "frmselleredit.h"
#include "ui_frmselleredit.h"

FrmSellerEdit::FrmSellerEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSellerEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmSellerEdit::~FrmSellerEdit()
{
    delete ui;
}

void FrmSellerEdit::setEditType(const QString type)
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

void FrmSellerEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmSellerEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmSellerEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmSellerEdit::onEventShowDetail);
}

void FrmSellerEdit::onEventShowDetail()
{
    getBankTypeItem();
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 11);
        m_number = m_detailData.at(0).toInt();
        ui->editName->setText(m_detailData.at(1));
        ui->editIdentityID->setText(m_detailData.at(2));
        ui->editAddress->setText(m_detailData.at(3));
        ui->editPhone->setText(m_detailData.at(4));
        ui->cbxBankType->setCurrentText(m_detailData.at(5));
        ui->editBankID->setText(m_detailData.at(6));
    }
}

bool FrmSellerEdit::checkFrmEditData()
{
    if(ui->editName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","角色名称不能为空","确定");
        return false;
    }
    return true;
}

void FrmSellerEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditSeller);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("SellerName",ui->editName->text());
    session.addRequestData("IdentityID",ui->editIdentityID->text());
    session.addRequestData("SellerAddress",ui->editAddress->text());
    session.addRequestData("SellerPhone",ui->editPhone->text());
    session.addRequestData("BankType",ui->cbxBankType->currentData().toString());
    session.addRequestData("BankId",ui->editBankID->text());

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmSellerEdit::getBankTypeItem()
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryBankType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("VehicleTypeName","");
    session.addRequestData("StartPage",QString::number(1));
    session.addRequestData("PerPage",QString::number(100));
    session.addRequestData("StartDate","");
    session.addRequestData("EndDate","");

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        for(quint32 i = 0; i < session.getRowSize(); ++i){
            QStringList row = session.getRow(i);
            ui->cbxBankType->addItem(row.at(1),row.at(0));
            qDebug()<<row.at(1)<<row.at(0);
        }
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmSellerEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}
