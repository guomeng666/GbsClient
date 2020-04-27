#include "editregister.h"

EditRegister::EditRegister()
{

}

void EditRegister::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("PurchaseType",QJsonValue(session.getRequestData("PurchaseType")));
    rootObj.insert("ContractNum",QJsonValue(session.getRequestData("ContractNum")));
    rootObj.insert("VehicleLiscence",QJsonValue(session.getRequestData("VehicleLiscence")));
    rootObj.insert("VehicleType",QJsonValue(session.getRequestData("VehicleType")));
    rootObj.insert("VehicleColor",QJsonValue(session.getRequestData("VehicleColor")));
    rootObj.insert("VehicleFrameId",QJsonValue(session.getRequestData("VehicleFrameId")));
    rootObj.insert("DriverNum",QJsonValue(session.getRequestData("DriverNum")));
    rootObj.insert("DriverName",QJsonValue(session.getRequestData("DriverName")));
    rootObj.insert("DriverAddress",QJsonValue(session.getRequestData("DriverAddress")));
    rootObj.insert("DriverPhone",QJsonValue(session.getRequestData("DriverPhone")));
    rootObj.insert("SellerNum",QJsonValue(session.getRequestData("SellerNum")));
    rootObj.insert("SellerName",QJsonValue(session.getRequestData("SellerName")));
    rootObj.insert("SellerAddress",QJsonValue(session.getRequestData("SellerAddress")));
    rootObj.insert("SellerPhone",QJsonValue(session.getRequestData("SellerPhone")));
    rootObj.insert("PayeeNum",QJsonValue(session.getRequestData("PayeeNum")));
    rootObj.insert("PayeeName",QJsonValue(session.getRequestData("PayeeName")));
    rootObj.insert("PayeeAddress",QJsonValue(session.getRequestData("PayeeAddress")));
    rootObj.insert("PayeePhone",QJsonValue(session.getRequestData("PayeePhone")));
    rootObj.insert("PayeeBankType",QJsonValue(session.getRequestData("PayeeBankType")));
    rootObj.insert("PayeeBankNum",QJsonValue(session.getRequestData("PayeeBankNum")));
    rootObj.insert("PayMentType",QJsonValue(session.getRequestData("PayMentType")));
    rootObj.insert("PackType",QJsonValue(session.getRequestData("PackType")));
    rootObj.insert("GrainType",QJsonValue(session.getRequestData("PackType")));
    rootObj.insert("TagNum",QJsonValue(session.getRequestData("TagNum")));
    rootObj.insert("TagStatus",QJsonValue(session.getRequestData("TagStatus")));
    rootObj.insert("ICID",QJsonValue(session.getRequestData("ICID")));
    rootObj.insert("Remarks",QJsonValue(session.getRequestData("Remarks")));
    rootObj.insert("Pircture1",QJsonValue(session.getRequestData("Pircture1")));
    rootObj.insert("Pircture2",QJsonValue(session.getRequestData("Pircture2")));
    rootObj.insert("Pircture3",QJsonValue(session.getRequestData("Pircture3")));
    rootObj.insert("Pircture4",QJsonValue(session.getRequestData("Pircture4")));
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
