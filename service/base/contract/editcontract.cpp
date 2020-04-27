#include "editcontract.h"

EditContract::EditContract()
{

}

void EditContract::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("ContractNum",QJsonValue(session.getRequestData("ContractNum")));
    rootObj.insert("ContractType",QJsonValue(session.getRequestData("ContractType")));
    rootObj.insert("GrainType",QJsonValue(session.getRequestData("GrainType")));
    rootObj.insert("Start",QJsonValue(session.getRequestData("Start")));
    rootObj.insert("End",QJsonValue(session.getRequestData("End")));
    rootObj.insert("OrderID",QJsonValue(session.getRequestData("OrderID")));
    rootObj.insert("Supplier",QJsonValue(session.getRequestData("Supplier")));
    rootObj.insert("TransCompany",QJsonValue(session.getRequestData("TransCompany")));
    rootObj.insert("Source",QJsonValue(session.getRequestData("Source")));
    rootObj.insert("Total",QJsonValue(session.getRequestData("Total")));
    rootObj.insert("Complete",QJsonValue(session.getRequestData("Complete")));
    rootObj.insert("TransportNum",QJsonValue(session.getRequestData("TransportNum")));
    rootObj.insert("WagaonNum",QJsonValue(session.getRequestData("WagaonNum")));
    rootObj.insert("PayType",QJsonValue(session.getRequestData("PayType")));
    rootObj.insert("BankType",QJsonValue(session.getRequestData("BankType")));
    rootObj.insert("BankNum",QJsonValue(session.getRequestData("BankNum")));
    rootObj.insert("Contact",QJsonValue(session.getRequestData("Contact")));
    rootObj.insert("ContactPhone",QJsonValue(session.getRequestData("ContactPhone")));
    rootObj.insert("IsComplete",QJsonValue(session.getRequestData("IsComplete")));
    rootObj.insert("Remark",QJsonValue(session.getRequestData("Remark")));
    rootObj.insert("Valuation",QJsonValue(session.getRequestData("Valuation")));
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
