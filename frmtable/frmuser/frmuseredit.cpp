#include "frmuseredit.h"
#include "gbstoolfunctions.h"
#include "ui_frmuseredit.h"
#include <QListWidgetItem>

FrmUserEdit::FrmUserEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmUserEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmUserEdit::~FrmUserEdit()
{
    delete ui;
}

void FrmUserEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("用户添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("用户修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmUserEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmUserEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete",m_number);
}

void FrmUserEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmUserEdit::onEventShowDetail);
}

void FrmUserEdit::onEventShowDetail()
{
    getDepartmentSelectItem();
    getRoleList();
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 10);
        m_number = m_detailData.at(0).toInt();
        ui->editUserName->setText(m_detailData.at(1));
        ui->editID->setText(m_detailData.at(3));
        ui->editAddress->setText(m_detailData.at(4));
        ui->cbxDepartment->setCurrentText(m_detailData.at(5));
        QStringList roleList = m_detailData.at(6).split(',');
        qDebug()<<roleList<<"count:"<<ui->listRoles->count();

        for(int i = 0; i < roleList.count(); ++i){
            for(int j = 0; j < ui->listRoles->count();++j){
                if(ui->listRoles->item(j)->text() == roleList.at(i)){
                    QListWidgetItem *selectItem = ui->listRoles->item(j);
                    QListWidgetItem *newItem=selectItem->clone();
                    ui->listSelected->addItem(newItem);
                    ui->listSelected->setCurrentItem(newItem);
                    delete selectItem;
                    break;
                }
            }
        }
    }
}

void FrmUserEdit::getDepartmentSelectItem()
{
    GbsToolFunctions::setComboxItem(CmdQueryDepartment,ui->cbxDepartment);
}

void FrmUserEdit::getRoleList()
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryRoel);
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
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(row.at(1));
            item->setData(Qt::UserRole,row.at(0));
            ui->listRoles->addItem(item);
        }
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

bool FrmUserEdit::checkFrmEditData()
{
    if(ui->editUserName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","用户名字不能为空","确定");
        return false;
    }else if(ui->editPassword->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","用户密码不能为空","确定");
        return false;
    }else if(ui->enditConfirm->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","确认密码不能为空","确定");
        return false;
    }else if(ui->editID->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","用户身份证号码不能为空","确定");
        return false;
    }else if(ui->editAddress->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","用户身份证地址不能为空","确定");
        return false;
    }else if(ui->listSelected->count() == 0){
        QMessageBox::warning(NULL,"系统提示","必须要选定一个角色","确定");
        return false;
    }
    if(ui->editPassword->text() != ui->enditConfirm->text()){
        QMessageBox::warning(NULL,"系统提示","两次密码输入不一致!","确定");
        return false;
    }
    return true;
}

void FrmUserEdit::editRoleData(QString editStatus, qint32 number)
{
    Q_UNUSED(number)
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditUser);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("UserName",ui->editUserName->text());
    session.addRequestData("UserPassword",ui->editPassword->text());
    session.addRequestData("UserIdentityID",ui->editID->text());
    session.addRequestData("UserAddress",ui->editAddress->text());
    QStringList roles;
    for(int i = 0 ; i < ui->listSelected->count(); ++i){
         roles << ui->listSelected->item(i)->data(Qt::UserRole).toString();
    }
    session.addRequestData("UserRoleID",roles.join(','));
    session.addRequestData("UserDepartmentID",ui->cbxDepartment->currentData().toString());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmUserEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus, m_number);
}

void FrmUserEdit::on_btnRight_clicked()
{
    QListWidgetItem *selectItem = ui->listRoles->currentItem();
    if(selectItem != nullptr){
        QListWidgetItem *newItem=selectItem->clone();
        ui->listSelected->addItem(newItem);
        ui->listSelected->setCurrentItem(newItem);
        delete selectItem;
    }
}

void FrmUserEdit::on_btnLeft_clicked()
{
    QListWidgetItem *selectItem = ui->listSelected->currentItem();
    if(selectItem != nullptr){
        QListWidgetItem *newItem=selectItem->clone();
        ui->listRoles->addItem(newItem);
        ui->listRoles->setCurrentItem(newItem);
        delete selectItem;
    }
}
