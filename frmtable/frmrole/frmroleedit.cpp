#include "frmroleedit.h"
#include "ui_frmroleedit.h"

FrmRoleEdit::FrmRoleEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmRoleEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmRoleEdit::~FrmRoleEdit()
{
    delete ui;
}

void FrmRoleEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("角色添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("角色修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmRoleEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmRoleEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete",m_number);
}

void FrmRoleEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmRoleEdit::onEventShowDetail);
}

void FrmRoleEdit::onEventShowDetail()
{
    //获取权限选择项
    getPermissionSelectItem();
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 5);
        m_number = m_detailData.at(0).toInt();
        ui->editRoleName->setText(m_detailData.at(1));
        ui->comboBox->setCurrentText(m_detailData.at(2));
    }
}

void FrmRoleEdit::getPermissionSelectItem()
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerPermission);
    session.addRequestData("Sender","Admin");
    session.addRequestData("PermissionName","");
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
            ui->comboBox->addItem(row.at(1),row.at(0));
            qDebug()<<row.at(1)<<row.at(0);
        }
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

bool FrmRoleEdit::checkFrmEditData()
{
    if(ui->editRoleName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","角色名称不能为空","确定");
        return false;
    }
    return true;
}

void FrmRoleEdit::editRoleData(QString editStatus, qint32 number)
{
    Q_UNUSED(number);
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditRole);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("RoleName",ui->editRoleName->text());
    session.addRequestData("PrimissionID",ui->comboBox->currentData().toString());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmRoleEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus, m_number);
}
