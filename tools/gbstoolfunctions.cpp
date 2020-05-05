#include "gbstoolfunctions.h"
#include "gbssession.h"
#include "servicemanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QBuffer>
#include <QComboBox>
#include <QPixmap>
#include <QLabel>
#include <QCompleter>

GbsToolFunctions::GbsToolFunctions(QObject *parent) : QObject(parent)
{

}

void GbsToolFunctions::setComboxItem(const QString cmd, QComboBox *bx)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",cmd);
    session.addRequestData("Sender","Admin");
    session.addRequestData("PermissionName","");
    session.addRequestData("StartPage",QString::number(1));
    session.addRequestData("PerPage",QString::number(100));
    session.addRequestData("StartDate","");
    session.addRequestData("EndDate","");

    QStringList list;
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        for(quint32 i = 0; i < session.getRowSize(); ++i){
            QStringList row = session.getRow(i);
            list<<row.at(1);
            bx->addItem(row.at(1),row.at(0));
            bx->setEditable(true);
        }
        QCompleter *completer = new QCompleter(list,bx);
        bx->setCompleter(completer);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

/**
  功能:通过身份证号码查询售粮户信息
  参数: tagNum = 电子标签号码, result = 查询的数据
  成功返回result格式: "ID","Name","IdentityID","Address","Phone","BankType","BankID","Creater","Updater","CreateTime","UpdateTime"
  错误返回result格式: "具体失败的内容"
  返回: 存在:true , 不存在:false
*/
bool GbsToolFunctions::getSellerInfoByIdentityID(QString identity, QStringList &result)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQuerySellerByIdentityID);
    session.addRequestData("Sender","Admin");
    session.addRequestData("IdentityID",identity);

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
       result = session.getRow(0);
       return true;
    }else{
        result = QStringList()<<session.getLastErrString();
        return false;
    }
}

/**
  功能:通过车牌号码查询车辆信息
  参数: tagNum = 电子标签号码, result = 查询的数据
  成功返回result格式: "ID","Name","VehicleType","color","FrameID","Creater","Updater","CreateTime","UpdateTime"
  错误返回result格式: "具体失败的内容"
  返回: 存在:true , 不存在:false
*/
bool GbsToolFunctions::getVehicleByLiscense(QString liscense, QStringList &result)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryVehicle);
    session.addRequestData("Sender","Admin");
    session.addRequestData("VehicleLiscence",liscense);
    session.addRequestData("StartPage","1");
    session.addRequestData("PerPage","20");
    session.addRequestData("StartDate","0");
    session.addRequestData("EndDate","0");

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
       result =  session.getRow(0);
       return true;
    }else{
        result = QStringList()<<session.getLastErrString();
        return false;
    }
}

/**
  功能:通过电子标签号码获取登记信息
  参数: tagNum = 电子标签号码, result = 查询的数据
  成功返回result格式: "ID","PurchaseType","PackType","GrainType","License","VehicleType","VehicleColor","VehicleFrame"
  错误返回result格式: "具体失败的内容"
  返回: 存在:true , 不存在:false
*/
bool GbsToolFunctions::getRegisterInfoByTagNum(QString tagNum, QStringList &result)
{
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryRegisterByTagNum);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Name",tagNum);
    session.addRequestData("StartPage","1");
    session.addRequestData("PerPage","20");
    session.addRequestData("StartDate","0");
    session.addRequestData("EndDate","0");

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
       result =  session.getRow(0);
       return true;
    }else{
        result = QStringList()<<session.getLastErrString();
        return false;
    }
}

//将QLabel上显示的图片转换成字符串
QString GbsToolFunctions::lablePixmapToString(QLabel *lab)
{
    const QPixmap* pixmap = lab->pixmap();
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    pixmap->save(&buffer,"jpg");
    quint32 pix_len = (quint32)buffer.data().size();
    qDebug()<<"image size:"<<pix_len;
    QByteArray dataArray;
    dataArray.append(buffer.data());
    return QString(dataArray.toHex());
}

/**
  功能:判断一个合同号码是否有效
  参数: number = 合同号码
  返回: 存在:true , 不存在:false
*/
bool GbsToolFunctions::contractIsValid(const QString &num)
{
    GbsSession session;
    session.addRequestData("Cmd",CmdQueryContract);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Name",num);
    session.addRequestData("StartPage","1");
    session.addRequestData("PerPage","100");
    session.addRequestData("StartDate","");
    session.addRequestData("EndDate","");

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        return true;
    }else{
        return false;
    }
}

/**
  功能:从服务接口获取指定节点的图片
  参数:nodeNmae = 获取那个节点的图片,取值= ["Register", "Sampling", "Assay", "Sell", "Weigh", "Unload", "Settlement"]
       number = 数据库索引编号
  返回:获取的image图片列表
*/
QList<QImage> GbsToolFunctions::getImageFromService(const QString &nodeName, const QString &number)
{
    QList<QImage> list;
    //创建回话
    GbsSession session;
    if(nodeName == "Weigh"){
        session.addRequestData("Cmd",CmdQueryWeighPicture);
    }
    else{
        session.addRequestData("Cmd",CmdQueryPicture);
        session.addRequestData("Node",nodeName);
    }
    session.addRequestData("Sender","Admin");
    session.addRequestData("Number",number);

    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
       QStringList pictures =  session.getRow(0);
       foreach (QString picture, pictures) {
           QByteArray hex =  QByteArray::fromHex(picture.toLatin1());
           QImage img;
           img.loadFromData(hex);
           list << img;
       }
    }
    return list;
}


