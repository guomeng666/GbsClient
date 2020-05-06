#include "frmmanager.h"
#include "frmroletable.h"
#include "frmpermissiontable.h"
#include "frmdepartmenttable.h"
#include "frmusertable.h"
#include "frmvehicletypetable.h"
#include "frmvehicletable.h"
#include "frmwarehousetable.h"
#include "frmbanktypetable.h"
#include "frmsellertable.h"
#include "frmsuppliertable.h"
#include "frmtransporttable.h"
#include "frmpaymenttypetable.h"
#include "frmpacktypetable.h"
#include "frmgraintypetable.h"
#include "frmsampleclasstable.h"
#include "frmcontracttypetable.h"
#include "frmprocedurenodetable.h"
#include "frmpurchasetable.h"
#include "frmvaluationtable.h"
#include "frmcontracttable.h"
#include "frmregistertable.h"
#include "frmregister.h"
#include "frmsampling.h"
#include "frmassay.h"
#include "frmassaytable.h"
#include "frmsell.h"
#include "frmselltable.h"
#include "frmweigh.h"
#include "frmunload.h"
#include "ui_frmmanager.h"
#include <QDebug>
#include <QToolBar>
#include <assert.h>

QWidget* Frmmanager::frmFactory(const QString &name)
{
    if(name == "角色管理"){
        return new FrmRoleTable(this);
    }else if(name == "权限管理"){
        return new FrmPermissionTable(this);
    }else if(name == "部门管理"){
        return new FrmDepartmentTable(this);
    }else if(name == "用户管理"){
        return new FrmUserTable(this);
    }else if(name == "车辆类型管理"){
        return new FrmVehicleTypeTable(this);
    }else if(name == "车辆管理"){
        return new FrmVehicleTable(this);
    }else if(name == "仓库管理"){
        return new FrmWareHouseTable(this);
    }else if(name == "银行卡管理"){
        return new FrmBankTypeTable(this);
    }else if(name == "售粮户管理"){
        return new FrmSellerTable(this);
    }else if(name == "供应商管理"){
        return new FrmSupplierTable(this);
    }else if(name == "运输公司管理"){
        return new FrmTransportTable(this);
    }else if(name == "支付方式管理"){
        return new FrmPaymenttypeTable(this);
    }else if(name == "粮食包装管理"){
        return new FrmPackTypeTable(this);
    }else if(name == "粮食类型管理"){
        return new FrmGrainTypeTable(this);
    }else if(name == "样品级别管理"){
        return new FrmSampleClassTable(this);
    }else if(name == "合同类型管理"){
        return new FrmContractTypeTable(this);
    }else if(name == "流程节点管理"){
        return new FrmProcedureNodeTable(this);
    }else if(name == "收购流程管理"){
        return new FrmPurchaseTable(this);
    }else if(name == "计价方式管理"){
        return new FrmValuationTable(this);
    }else if(name == "合同管理"){
        return new FrmContractTable(this);
    }else if(name == "登记业务"){
        return new FrmRegister(this);
    }else if(name == "登记查询"){
        return new FrmRegisterTable(this);
    }else if(name == "扦样业务"){
        return new FrmSampling(this);
    }else if(name == "化验业务"){
        return new FrmAssay(this);
    }else if(name == "化验查询"){
        return new FrmAssayTable(this);
    }else if(name == "售粮业务"){
        return new FrmSell(this);
    }else if(name == "售粮查询"){
        return new FrmSellTable(this);
    }else if(name == "检斤业务"){
        return new FrmWeigh(this);
    }else if(name == "卸粮业务"){
        return new FrmUnload(this);
    }
    return nullptr;
}

Frmmanager::Frmmanager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Frmmanager)
{
    ui->setupUi(this);
    this->initForm();
    this->initToolBar();
}

Frmmanager::~Frmmanager()
{
    delete ui;
}


void Frmmanager::initForm()
{
    systemMenuInit();
    dayMenuInit();
    businessOperationMenuInit();
    businessQueryMenuInit();
    baseMenuInit();
    this->setWindowTitle("原粮收购管理系统");
}

void Frmmanager::initToolBar()
{
    QToolBar* toolBar = this->addToolBar("ToolBar");
    toolBar->addAction(QIcon(":/image/解锁.png"), "未锁定", this, SLOT(onLockAction()));
    toolBar->addAction(QIcon(":/image/进度查询.png"), "进度查询", this, SLOT(onPurchaseQueryAction()));
}

void Frmmanager::systemMenuInit()
{
    QList<QAction*> actionList;
    QMenu *systemMenu = new QMenu("系统管理",this);
    actionList << new QAction("用户管理",systemMenu);
    actionList << new QAction("角色管理",systemMenu);
    actionList << new QAction("部门管理",systemMenu);
    actionList << new QAction("权限管理",systemMenu);
    systemMenu->addActions(actionList);
    this->menuBar()->addMenu(systemMenu);
    foreach (QAction* action, actionList) {
        connect(action,&QAction::triggered,this,&Frmmanager::onMenuAction);
    }
}

void Frmmanager::dayMenuInit()
{
    QList<QAction*> actionList;
    QMenu *dayMenu = new QMenu("日常操作",this);
    QMenu *blackMenu = new QMenu("黑名单管理",dayMenu);
    actionList << new QAction("审批管理",dayMenu);
    actionList << new QAction("合同管理",dayMenu);
    actionList << new QAction("计价方式管理",dayMenu);
    actionList << new QAction("流程状态查询",dayMenu);
    QAction *vehicleBlackAction = new QAction("车辆黑名单",blackMenu);
    QAction *sellerBlackAction = new QAction("售粮户黑名单",blackMenu);

    connect(vehicleBlackAction,&QAction::triggered,this,&Frmmanager::onMenuAction);
    connect(sellerBlackAction,&QAction::triggered,this,&Frmmanager::onMenuAction);

    blackMenu->addAction(vehicleBlackAction);
    blackMenu->addAction(sellerBlackAction);

    dayMenu->addActions(actionList);
    dayMenu->addMenu(blackMenu);
    this->menuBar()->addMenu(dayMenu);
    foreach (QAction* action, actionList) {
        connect(action,&QAction::triggered,this,&Frmmanager::onMenuAction);
    }
}

void Frmmanager::businessQueryMenuInit()
{
    QList<QAction*> actionList;
    QMenu *businessMenu = new QMenu("业务查询",this);
    actionList << new QAction("登记查询",businessMenu);
    actionList << new QAction("扦样查询",businessMenu);
    actionList << new QAction("化验查询",businessMenu);
    actionList << new QAction("售粮查询",businessMenu);
    actionList << new QAction("检斤查询",businessMenu);
    actionList << new QAction("卸粮查询",businessMenu);
    actionList << new QAction("结算查询",businessMenu);
    businessMenu->addActions(actionList);
    this->menuBar()->addMenu(businessMenu);
    foreach (QAction* action, actionList) {
        connect(action,&QAction::triggered,this,&Frmmanager::onMenuAction);
    }
}

void Frmmanager::businessOperationMenuInit()
{
    QList<QAction*> actionList;
    QMenu *businessMenu = new QMenu("业务操作",this);
    actionList << new QAction("登记业务",businessMenu);
    actionList << new QAction("扦样业务",businessMenu);
    actionList << new QAction("化验业务",businessMenu);
    actionList << new QAction("售粮业务",businessMenu);
    actionList << new QAction("检斤业务",businessMenu);
    actionList << new QAction("卸粮业务",businessMenu);
    actionList << new QAction("结算业务",businessMenu);
    businessMenu->addActions(actionList);
    this->menuBar()->addMenu(businessMenu);
    foreach (QAction* action, actionList) {
        connect(action,&QAction::triggered,this,&Frmmanager::onMenuAction);
    }
}

void Frmmanager::baseMenuInit()
{
    QList<QAction*> actionList;
    QMenu *baseMenu = new QMenu("基础信息",this);
    actionList << new QAction("车辆管理",baseMenu);
    actionList << new QAction("车辆类型管理",baseMenu);
    actionList << new QAction("仓库管理",baseMenu);
    actionList << new QAction("售粮户管理",baseMenu);
    actionList << new QAction("银行卡管理",baseMenu);
    actionList << new QAction("供应商管理",baseMenu);
    actionList << new QAction("运输公司管理",baseMenu);
    actionList << new QAction("支付方式管理",baseMenu);
    actionList << new QAction("粮食包装管理",baseMenu);
    actionList << new QAction("粮食类型管理",baseMenu);
    actionList << new QAction("样品级别管理",baseMenu);
    actionList << new QAction("合同类型管理",baseMenu);
    actionList << new QAction("流程节点管理",baseMenu);
    actionList << new QAction("收购流程管理",baseMenu);
    baseMenu->addActions(actionList);
    this->menuBar()->addMenu(baseMenu);
    foreach (QAction* action, actionList) {
        connect(action,&QAction::triggered,this,&Frmmanager::onMenuAction);
    }
}

void Frmmanager::onMenuAction()
{
    QAction* pAction = (QAction*)sender();
    QString actionText = pAction->text();
    if(m_frmMap.value(actionText) == nullptr){
        QWidget *frmTable = frmFactory(actionText);
        if(frmTable == nullptr){
            QMessageBox::warning(NULL,"系统提示","对不起,该功能还没有实现","确定");
            return;
        }
        m_frmMap[actionText] = frmTable;
        ui->tabWidget->addTab(frmTable,actionText);
        ui->tabWidget->setCurrentWidget(frmTable);
    }
}

void Frmmanager::onLockAction()
{
    static bool isLock = true;
    QAction *pAction = (QAction*)sender();
    if(isLock){
        pAction->setIcon(QIcon(":/image/锁定.png"));
        pAction->setText("已锁定");
        isLock = false;
    }else{
        pAction->setIcon(QIcon(":/image/解锁.png"));
        pAction->setText("未锁定");
        isLock = true;
    }
}

void Frmmanager::onPurchaseQueryAction()
{
    qDebug()<<"进度查询";
}


void Frmmanager::on_tabWidget_tabCloseRequested(int index)
{
    QString tabText = ui->tabWidget->tabText(index);
    Q_ASSERT(m_frmMap.find(tabText) != m_frmMap.end());
    ui->tabWidget->widget(index)->close();
    ui->tabWidget->removeTab(index);
    m_frmMap.remove(tabText);
}
