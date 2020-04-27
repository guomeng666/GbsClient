#include "queryvehicletype.h"

QueryVehicleType::QueryVehicleType()
{

}

void QueryVehicleType::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("VehicleTypeName",QJsonValue(session.getRequestData("VehicleTypeName")));
    rootObj.insert("StartPage",QJsonValue(session.getRequestData("StartPage")));
    rootObj.insert("PerPage",QJsonValue(session.getRequestData("PerPage")));
    rootObj.insert("StartDate",QJsonValue(session.getRequestData("StartDate")));
    rootObj.insert("EndDate",QJsonValue(session.getRequestData("EndDate")));
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
    //数据返回正确,解析数据
    session.setCurPage( doc.object().value("Page").toString().toInt());
    session.setTotalAmount(doc.object().value("TotalData").toInt());

    QJsonArray data = rootObj.value("Data").toArray();
    for(int i = 0; i < data.size(); ++i ) {
        QJsonObject row = data.at(i).toObject();
        QStringList rowData;
        rowData << QString::number(row.value("ID").toInt())<<row.value("Name").toString()\
                   <<QString::number(row.value("EstimateLoad").toInt())<<row.value("Creater").toString()\
                   <<row.value("CreateTime").toString()<<row.value("Updater").toString()\
                  <<row.value("UpdateTime").toString();
        session.appendRow(rowData);
    }
}
