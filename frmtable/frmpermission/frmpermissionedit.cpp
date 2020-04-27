#include "frmpermissionedit.h"
#include "ui_frmpermissionedit.h"
#include <QMessageBox>
#include <QDebug>

FrmpermissionEdit::FrmpermissionEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmpermissionEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmpermissionEdit::~FrmpermissionEdit()
{
    delete ui;
}

void FrmpermissionEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("权限添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("权限修改");
        ui->btnEdit->setText("修改");
        m_editStatus ="alter";
    }
}

void FrmpermissionEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmpermissionEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editPermissionData("delete");
}

void FrmpermissionEdit::onEventShowDetail()
{
    m_number = m_detailData.at(0).toInt();
    ui->editPersisionName->setText(m_detailData.at(1));
    setQueryPersissionCheckBox(m_detailData.at(2).toInt());
    setMaintainPersissionCheckBox(m_detailData.at(3).toInt());
    setRegisterPersissionCheckBox(m_detailData.at(4).toInt());
    setSamplingPersissionCheckBox(m_detailData.at(5).toInt());
    setAssayPersissionCheckBox(m_detailData.at(6).toInt());
    setSellPersissionCheckBox(m_detailData.at(7).toInt());
    setWeighPersissionCheckBox(m_detailData.at(8).toInt());
    setUnloadPersissionCheckBox(m_detailData.at(9).toInt());
    setSettlementPersissionCheckBox(m_detailData.at(10).toInt());
}

void FrmpermissionEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(m_editStatus == "alter"){
        Q_ASSERT(m_detailData.size() == 13);
        QTimer::singleShot(10,this,&FrmpermissionEdit::onEventShowDetail);
    }
}

void FrmpermissionEdit::on_btnEdit_clicked()
{
    editPermissionData(m_editStatus);
}

void FrmpermissionEdit::editPermissionData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    qint32 querBits       = generateQueryPerssionBits();
    qint32 maintainBits   = generateMaintainPerssionBits();
    qint32 registerBits   = generateRegisterPerssionBits();
    qint32 samplingBits   = generateSamplingPerssionBits();
    qint32 assayBits      = generateAssayPerssionBits();
    qint32 sellBits       = generateSellPerssionBits();
    qint32 weighBits      = generateWeighPerssionBits();
    qint32 unloadBits     = generateUnloadPerssionBits();
    qint32 settlementBits = generateSettlementPerssionBits();
    qDebug()<<querBits<<maintainBits<<registerBits<<samplingBits<<assayBits<<sellBits<<weighBits<<unloadBits<<settlementBits;
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditPermission);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("PermissionName",ui->editPersisionName->text());
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("QueryPri",QString::number(querBits));
    session.addRequestData("MaintainPri",QString::number(maintainBits));
    session.addRequestData("AlterRegisterPri",QString::number(registerBits));
    session.addRequestData("AlterSamplingPri",QString::number(samplingBits));
    session.addRequestData("AlterAssayPri",QString::number(assayBits));
    session.addRequestData("AlterSellPri",QString::number(sellBits));
    session.addRequestData("AlterWeighPri",QString::number(weighBits));
    session.addRequestData("AlterUnloadPri",QString::number(unloadBits));
    session.addRequestData("AlterSettlementPri",QString::number(settlementBits));

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

bool FrmpermissionEdit::checkFrmEditData()
{
    if(ui->editPersisionName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","权限名称不能为空","确定");
        return false;
    }
    return true;
}

//查询权限配置
qint32 FrmpermissionEdit::generateQueryPerssionBits()
{
    //允许查询日志信息|允许查询结算信息|允许查询卸粮信息|允许查询检斤信息|允许查询售粮信息|允许查询化验信息|允许查询扦样信息|允许查询登记信息
    qint32 bits = ui->chkQueryLog->isChecked()<<7|\
                ui->chkQuerySettlement->isChecked()<<6|\
                ui->chkQueryUnload->isChecked()<<5|\
                ui->chkQueryWeigh->isChecked()<<4|\
                ui->chkQuerySell->isChecked()<<3|\
                ui->chkQueryAssay->isChecked()<<2|\
                ui->chkQuerySampling->isChecked()<<1|\
                ui->chkQueryRegister->isChecked();
    qDebug()<<bits;
    return bits;
}

//管理权限配置
qint32 FrmpermissionEdit::generateMaintainPerssionBits()
{
    //允许管理业务信息|允许管理系统信息
    qint32 bits = ui->chkbusiness->isChecked()<<1|\
                  ui->chkSystem->isChecked();
    qDebug()<<bits;
    return bits;
}

//登记权限配置
qint32 FrmpermissionEdit::generateRegisterPerssionBits()
{
    /**
      允许更改IC卡号码|允许更改电子标签状态|允许更改电子标签号码|允许更改司机|允许更改合同号码|允许更改支付方式|允许更改结算人|允许更改售粮人|
      允许更改粮食类型|允许更改包装类型|允许更改采购流程|允许更改车辆信息
    */
    qint32 bits=ui->chkRegisterICID->isChecked()<<11|\
                ui->chkRegisterTagStatus->isChecked()<<10|\
                ui->chkRegisterTagID->isChecked()<<9|\
                ui->chkRegisterDriver->isChecked()<<8|\
                ui->chkRegisterContract->isChecked()<<7|\
                ui->chkRegisterPayType->isChecked()<<6|\
                ui->chkRegisterReceiver->isChecked()<<5|\
                ui->chkRegisterSeller->isChecked()<<4|\
                ui->chkRegisterGrainType->isChecked()<<3|\
                ui->chkRegisterPackType->isChecked()<<2|\
                ui->chkRegisterPurchase->isChecked()<<1|\
                ui->chkRegisterVehicle->isChecked();
    qDebug()<<bits;
    return bits;
}

//扦样权限配置
qint32 FrmpermissionEdit::generateSamplingPerssionBits()
{
    /**
      允许更改电子标签状态|允许更改电子标签号码|允许更改车辆ID
    */
    qint32 bits=ui->chkSamplingTagStatus->isChecked()<<2|\
                ui->chkSamplingTagID->isChecked()<<1|\
                ui->chkSamplingVehicle->isChecked();
    qDebug()<<bits;
    return bits;
}

//化验权限配置
qint32 FrmpermissionEdit::generateAssayPerssionBits()
{
    /**
      允许更改样品袋|允许更改样品净重|允许更改样品毛重|允许更改异味|允许更改水泡粒|允许更改异种粮|允许更改棒芯|
      允许更改土块|允许更改小石子|允许更改并肩杂|允许更改热损|允许更改破碎|允许更改霉变|允许更改杂质|允许更改水分|
      允许更改容重|允许更改是否是标准样|允许更改样品盒号码||允许更改样品级别|允许更改化验状态|允许更改粮食类型
    */
       qint32 bits=ui->chkAssayYMD->isChecked()<<20|\
                    ui->chkAssayJZ->isChecked()<<19|\
                    ui->chkAssayMZ->isChecked()<<18|\
                    ui->chkAssayYW->isChecked()<<17|\
                    ui->chkAssaySPL->isChecked()<<16|\
                    ui->chkAssayYZL->isChecked()<<15|\
                    ui->chkAssayBX->isChecked()<<14|\
                    ui->chkAssayTK->isChecked()<<13|\
                    ui->chkAssayXSZ->isChecked()<<12|\
                    ui->chkAssayBJZ->isChecked()<<11|\
                    ui->chkAssayRS->isChecked()<<10|\
                    ui->chkAssayPS->isChecked()<<9|\
                    ui->chkAssayMB->isChecked()<<8|\
                    ui->chkAssayZZ->isChecked()<<7|\
                    ui->chkAssayWater->isChecked()<<6|\
                    ui->chkAssayRZ->isChecked()<<5|\
                    ui->chkAssayStandard->isChecked()<<4|\
                    ui->chkAssayBoxID->isChecked()<<3|\
                    ui->chkAssayYPJB->isChecked()<<2|\
                    ui->chkAssayStatus->isChecked()<<1|\
                    ui->chkAssayGrainType->isChecked();
       qDebug()<<bits;
       return bits;
}

//售粮权限
qint32 FrmpermissionEdit::generateSellPerssionBits()
{
    /**
      允许更改售粮状态|允许更改车辆信息
    */
    qint32 bits = ui->chkSellStatus->isChecked()<<1|\
                  ui->chkSellVehicle->isChecked();
    qDebug()<<bits;
    return bits;
}

//检斤权限
qint32 FrmpermissionEdit::generateWeighPerssionBits()
{
    /**
      允许更改皮重|允许更改毛重|允许更改电子标签状态|允许更改电子标签ID|允许更改车辆信息
    */
    qint32 bits =ui->chkWeighTare->isChecked()<<4|\
                 ui->chkWeighRough->isChecked()<<3|\
                 ui->chkWeighTagStatus->isChecked()<<2|\
                 ui->chkWeighTagID->isChecked()<<1|\
                 ui->chkWeighVehicle->isChecked();
    qDebug()<<bits;
    return bits;
}

//卸粮权限
qint32 FrmpermissionEdit::generateUnloadPerssionBits()
{
    /**
      允许更改仓库位|允许更改扣重量|允许更改电子标签状态|允许更改电子标签号码|允许更改车辆信息
    */
    qint32 bits =ui->chkUnloadPos->isChecked()<<4|\
                 ui->chkUnloadTake->isChecked()<<3|\
                 ui->chkUnloadTagStatus->isChecked()<<2|\
                 ui->chkUnloadTagID->isChecked()<<1|\
                 ui->chkUnloadVehicle->isChecked();
    qDebug()<<bits;
    return bits;
}

qint32 FrmpermissionEdit::generateSettlementPerssionBits()
{
    /**
      允许更改计价编号
    */
    qint32 bits = ui->chkSettlementValuation->isChecked();
    qDebug()<<bits;
    return bits;
}

void FrmpermissionEdit::setQueryPersissionCheckBox(quint32 bits)
{
    ui->chkQueryLog->setChecked(bits & 1<<7);
    ui->chkQuerySettlement->setChecked(bits & 1<<6);
    ui->chkQueryUnload->setChecked(bits & 1<<5);
    ui->chkQueryWeigh->setChecked(bits & 1<<4);
    ui->chkQuerySell->setChecked(bits & 1<<3);
    ui->chkQueryAssay->setChecked(bits & 1<<2);
    ui->chkQuerySampling->setChecked(bits & 1<<1);
    ui->chkQueryRegister->setChecked(bits & 1);
}

void FrmpermissionEdit::setMaintainPersissionCheckBox(quint32 bits)
{
    ui->chkbusiness->setChecked(bits & 1<<1);
    ui->chkSystem->setChecked(bits & 1);
}

void FrmpermissionEdit::setRegisterPersissionCheckBox(quint32 bits)
{
    ui->chkRegisterICID->setChecked(bits & 1<<11);
    ui->chkRegisterTagStatus->setChecked(bits & 1<<10);
    ui->chkRegisterTagID->setChecked(bits & 1<<9);
    ui->chkRegisterDriver->setChecked(bits & 1<<8);
    ui->chkRegisterContract->setChecked(bits & 1<<7);
    ui->chkRegisterPayType->setChecked(bits & 1<<6);
    ui->chkRegisterReceiver->setChecked(bits & 1<<5);
    ui->chkRegisterSeller->setChecked(bits & 1<<4);
    ui->chkRegisterGrainType->setChecked(bits & 1<<3);
    ui->chkRegisterPackType->setChecked(bits & 1<<2);
    ui->chkRegisterPurchase->setChecked(bits & 1<<1);
    ui->chkRegisterVehicle->setChecked(bits & 1<<1);
}

void FrmpermissionEdit::setSamplingPersissionCheckBox(quint32 bits)
{
    ui->chkSamplingTagStatus->setChecked(bits & 1<<2);
    ui->chkSamplingTagID->setChecked(bits & 1<<1);
    ui->chkSamplingVehicle->setChecked(bits & 1);
}

void FrmpermissionEdit::setAssayPersissionCheckBox(quint32 bits)
{
    ui->chkAssayYMD->setChecked(bits & 1<<20);
    ui->chkAssayJZ->setChecked(bits & 1<<19);
    ui->chkAssayMZ->setChecked(bits & 1<<18);
    ui->chkAssayYW->setChecked(bits & 1<<17);
    ui->chkAssaySPL->setChecked(bits & 1<<16);
    ui->chkAssayYZL->setChecked(bits & 1<<15);
    ui->chkAssayBX->setChecked(bits & 1<<14);
    ui->chkAssayTK->setChecked(bits & 1<<13);
    ui->chkAssayXSZ->setChecked(bits & 1<<12);
    ui->chkAssayBJZ->setChecked(bits & 1<<11);
    ui->chkAssayRS->setChecked(bits & 1<<10);
    ui->chkAssayPS->setChecked(bits & 1<<9);
    ui->chkAssayMB->setChecked(bits & 1<<8);
    ui->chkAssayZZ->setChecked(bits & 1<<7);
    ui->chkAssayWater->setChecked(bits & 1<<6);
    ui->chkAssayRZ->setChecked(bits & 1<<5);
    ui->chkAssayStandard->setChecked(bits & 1<<4);
    ui->chkAssayBoxID->setChecked(bits & 1<<3);
    ui->chkAssayYPJB->setChecked(bits & 1<<2);
    ui->chkAssayStatus->setChecked(bits & 1<<1);
    ui->chkAssayGrainType->setChecked(bits & 1);
}

void FrmpermissionEdit::setSellPersissionCheckBox(quint32 bits)
{
    ui->chkSellStatus->setChecked(bits & 1<<1);
    ui->chkSellVehicle->setChecked(bits & 1);
}

void FrmpermissionEdit::setWeighPersissionCheckBox(quint32 bits)
{
    ui->chkWeighTare->setChecked(bits & 1<<4);
    ui->chkWeighRough->setChecked(bits & 1<<3);
    ui->chkWeighTagStatus->setChecked(bits & 1<<2);
    ui->chkWeighTagID->setChecked(bits & 1<<1);
    ui->chkWeighVehicle->setChecked(bits & 1);
}

void FrmpermissionEdit::setUnloadPersissionCheckBox(quint32 bits)
{
    ui->chkUnloadPos->setChecked(bits & 1<<4);
    ui->chkUnloadTake->setChecked(bits & 1<<3);
    ui->chkUnloadTagStatus->setChecked(bits & 1<<2);
    ui->chkUnloadTagID->setChecked(bits & 1<<1);
    ui->chkUnloadVehicle->setChecked(bits & 1);
}

void FrmpermissionEdit::setSettlementPersissionCheckBox(quint32 bits)
{
    ui->chkSettlementValuation->setChecked(bits & 1);
}

