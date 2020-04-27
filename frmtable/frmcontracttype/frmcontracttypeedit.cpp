#include "frmcontracttypeedit.h"
#include "ui_frmcontracttypeedit.h"

FrmContractTypeEdit::FrmContractTypeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmContractTypeEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmContractTypeEdit::~FrmContractTypeEdit()
{
    delete ui;
}

void FrmContractTypeEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("仓库添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("仓库修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmContractTypeEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmContractTypeEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmContractTypeEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmContractTypeEdit::onEventShowDetail);
}

void FrmContractTypeEdit::onEventShowDetail()
{
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 6);
        m_number = m_detailData.at(0).toInt();
        ui->editName->setText(m_detailData.at(1));
    }
}

bool FrmContractTypeEdit::checkFrmEditData()
{
    if(ui->editName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","银行名字不能为空","确定");
        return false;
    }
    return true;
}

void FrmContractTypeEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditContractType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("ContractTypeName",ui->editName->text());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmContractTypeEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}
