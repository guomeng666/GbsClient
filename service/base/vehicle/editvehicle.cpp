#include "editvehicle.h"

EditVehicle::EditVehicle()
{

}

void EditVehicle::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("VehicleLiscence",QJsonValue(session.getRequestData("VehicleLiscence")));
    rootObj.insert("VehicleType",QJsonValue(session.getRequestData("VehicleType")));
    rootObj.insert("VehicleColor",QJsonValue(session.getRequestData("VehicleColor")));
    rootObj.insert("VehicleFrameId",QJsonValue(session.getRequestData("VehicleFrameId")));
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
