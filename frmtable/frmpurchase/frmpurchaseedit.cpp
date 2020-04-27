#include "frmpurchaseedit.h"
#include "ui_frmpurchaseedit.h"
#include <QListWidgetItem>

FrmPurchaseEdit::FrmPurchaseEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmPurchaseEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmPurchaseEdit::~FrmPurchaseEdit()
{
    delete ui;
}

void FrmPurchaseEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("流程添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("流程修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmPurchaseEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmPurchaseEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editData("delete",m_number);
}

void FrmPurchaseEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmPurchaseEdit::onEventShowDetail);
}

void FrmPurchaseEdit::onEventShowDetail()
{
    getNodeList();
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 7);
        m_number = m_detailData.at(0).toInt();
        ui->editName->setText(m_detailData.at(1));
        QStringList roleList = m_detailData.at(2).split(',');
        qDebug()<<roleList<<"count:"<<ui->listNodes->count();

        for(int i = 0; i < roleList.count(); ++i){
            for(int j = 0; j < ui->listNodes->count();++j){
                if(ui->listNodes->item(j)->text() == roleList.at(i)){
                    QListWidgetItem *selectItem = ui->listNodes->item(j);
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

void FrmPurchaseEdit::getNodeList()
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryProcedureNode);
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
            ui->listNodes->addItem(item);
        }
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

bool FrmPurchaseEdit::checkFrmEditData()
{
    if(ui->editName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","用户名字不能为空","确定");
        return false;
    }else if(ui->listSelected->count() == 0){
        QMessageBox::warning(NULL,"系统提示","必须要选定一个角色","确定");
        return false;
    }
    return true;
}

void FrmPurchaseEdit::editData(QString editStatus, qint32 number)
{
    Q_UNUSED(number)
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditPurchase);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("PurchaseName",ui->editName->text());
    QStringList roles;
    for(int i = 0 ; i < ui->listSelected->count(); ++i){
         roles << ui->listSelected->item(i)->text();
    }
    session.addRequestData("Sequence",roles.join(','));
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmPurchaseEdit::on_btnEdit_clicked()
{
    editData(m_editStatus, m_number);
}

void FrmPurchaseEdit::on_btnRight_clicked()
{
    QListWidgetItem *selectItem = ui->listNodes->currentItem();
    if(selectItem != nullptr){
        QListWidgetItem *newItem=selectItem->clone();
        ui->listSelected->addItem(newItem);
        ui->listSelected->setCurrentItem(newItem);
        delete selectItem;
    }
}

void FrmPurchaseEdit::on_btnLeft_clicked()
{
    QListWidgetItem *selectItem = ui->listSelected->currentItem();
    if(selectItem != nullptr){
        QListWidgetItem *newItem=selectItem->clone();
        ui->listNodes->addItem(newItem);
        ui->listNodes->setCurrentItem(newItem);
        delete selectItem;
    }
}
