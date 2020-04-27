#include "frmgraintypeedit.h"
#include "ui_frmgraintypeedit.h"

FrmGrainTypeEdit::FrmGrainTypeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmGrainTypeEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmGrainTypeEdit::~FrmGrainTypeEdit()
{
    delete ui;
}

void FrmGrainTypeEdit::setEditType(const QString type)
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

void FrmGrainTypeEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmGrainTypeEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmGrainTypeEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmGrainTypeEdit::onEventShowDetail);
}

void FrmGrainTypeEdit::onEventShowDetail()
{
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 6);
        m_number = m_detailData.at(0).toInt();
        ui->editName->setText(m_detailData.at(1));
    }
}

bool FrmGrainTypeEdit::checkFrmEditData()
{
    if(ui->editName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","仓库名称不能为空","确定");
        return false;
    }
    return true;
}

void FrmGrainTypeEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditGrainType);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("GrainTypeName",ui->editName->text());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmGrainTypeEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}
