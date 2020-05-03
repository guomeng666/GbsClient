#include "queryassaytosell.h"

QueryAssayToSell::QueryAssayToSell()
{

}

void QueryAssayToSell::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
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
    QString errMsg = rootObj.value("ErrMsg").toString();
    if(errNo != 0){
        session.setErrNo(errNo);
        session.setErrMsg(errMsg);
        return;
    }
    //数据返回正确,解析数据
    QJsonObject data = rootObj.value("Data").toObject();
    QStringList rowData;
    QString smell = data.value("PeculiarSmell").toBool() == true ? "有" : "无";
    QString isReject = data.value("IsReject").toBool() == true ? "是" : "否";
    rowData << data.value("PurchaseType").toString()\
            << data.value("GrainType").toString()\
            << data.value("PackType").toString()\
            << data.value("License").toString()\
            << data.value("VehicleType").toString()\
            << data.value("Color").toString()\
            << QString::number(data.value("UnitWeight").toDouble())\
            << QString::number(data.value("Moisture").toDouble())\
            << QString::number(data.value("Impurity").toDouble())\
            << QString::number(data.value("Mildew").toDouble())\
            << QString::number(data.value("Broken").toDouble())\
            << QString::number(data.value("HeatHarm").toDouble())\
            << QString::number(data.value("SideImpurity").toDouble())\
            << QString::number(data.value("Scree").toDouble())\
            << QString::number(data.value("SoilBlock").toDouble())\
            << QString::number(data.value("RodCore").toDouble())\
            << QString::number(data.value("DifGrain").toDouble())\
            << QString::number(data.value("BlistersGrain").toDouble())\
            << smell\
            << isReject\
            << QString::number(data.value("ProcedureNum").toInt());
    qDebug()<<rowData;
    session.appendRow(rowData);
}
