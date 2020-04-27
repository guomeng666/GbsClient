#include "editvehicletype.h"

EditVehicleType::EditVehicleType()
{

}

void EditVehicleType::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("VehicleTypeName",QJsonValue(session.getRequestData("VehicleTypeName")));
    rootObj.insert("EstimateLoad",QJsonValue(session.getRequestData("EstimateLoad")));
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
