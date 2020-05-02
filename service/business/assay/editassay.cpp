#include "editassay.h"

EditAssay::EditAssay()
{

}

void EditAssay::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("GrainType",QJsonValue(session.getRequestData("GrainType")));
    rootObj.insert("UnitWeight",QJsonValue(session.getRequestData("UnitWeight")));
    rootObj.insert("Moisture",QJsonValue(session.getRequestData("Moisture")));
    rootObj.insert("Impurity",QJsonValue(session.getRequestData("Impurity")));
    rootObj.insert("Mildew",QJsonValue(session.getRequestData("Mildew")));
    rootObj.insert("Broken",QJsonValue(session.getRequestData("Broken")));
    rootObj.insert("HeatHarm",QJsonValue(session.getRequestData("HeatHarm")));
    rootObj.insert("SideImpurity",QJsonValue(session.getRequestData("SideImpurity")));
    rootObj.insert("Scree",QJsonValue(session.getRequestData("Scree")));
    rootObj.insert("SoilBlock",QJsonValue(session.getRequestData("SoilBlock")));
    rootObj.insert("RodCore",QJsonValue(session.getRequestData("RodCore")));
    rootObj.insert("DifGrain",QJsonValue(session.getRequestData("DifGrain")));
    rootObj.insert("BlistersGrain",QJsonValue(session.getRequestData("BlistersGrain")));
    rootObj.insert("PeculiarSmell",QJsonValue(session.getRequestData("PeculiarSmell")));
    rootObj.insert("RoughWeight",QJsonValue(session.getRequestData("RoughWeight")));
    rootObj.insert("NetWeight",QJsonValue(session.getRequestData("NetWeight")));
    rootObj.insert("SampleBag",QJsonValue(session.getRequestData("SampleBag")));
    rootObj.insert("Remarks",QJsonValue(session.getRequestData("Remarks")));
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
