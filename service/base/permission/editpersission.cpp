#include "editpersission.h"

EditPersission::EditPersission()
{

}

void EditPersission::Execute(GbsSession &session)
{
    qDebug()<<"处理数据";
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("PermissionName",QJsonValue(session.getRequestData("PermissionName")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("QueryPri",QJsonValue(session.getRequestData("QueryPri")));
    rootObj.insert("MaintainPri",QJsonValue(session.getRequestData("MaintainPri")));
    rootObj.insert("AlterRegisterPri",QJsonValue(session.getRequestData("AlterRegisterPri")));
    rootObj.insert("AlterSamplingPri",QJsonValue(session.getRequestData("AlterSamplingPri")));
    rootObj.insert("AlterAssayPri",QJsonValue(session.getRequestData("AlterAssayPri")));
    rootObj.insert("AlterSellPri",QJsonValue(session.getRequestData("AlterSellPri")));
    rootObj.insert("AlterWeighPri",QJsonValue(session.getRequestData("AlterWeighPri")));
    rootObj.insert("AlterUnloadPri",QJsonValue(session.getRequestData("AlterUnloadPri")));
    rootObj.insert("AlterSettlementPri",QJsonValue(session.getRequestData("AlterSettlementPri")));
    doc.setObject(rootObj);
    QByteArray send = doc.toJson(QJsonDocument::Compact);
    bool res = session.sendDataToServer(send);
    if(res == false){
        session.setErrNo(errNetWork);
        return;
    }
    doc = QJsonDocument::fromJson(session.getResultRawData());
    rootObj = doc.object();
    quint32 errNo = rootObj.value("Errno").toInt();
    if(errNo != 0){
        session.setErrNo(errNo);
        return;
    }
}
