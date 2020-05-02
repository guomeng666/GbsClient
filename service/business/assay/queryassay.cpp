#include "queryassay.h"

QueryAssay::QueryAssay()
{

}

void QueryAssay::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Field",QJsonValue(session.getRequestData("Field")));
    rootObj.insert("Name",QJsonValue(session.getRequestData("Name")));
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
        QString isStandard = row.value("Standard").toBool() == true ? "是" : "否";
        QString smell = row.value("PeculiarSmell").toBool() == true ? "有" : "无";
        QString isReject = row.value("IsReject").toBool() == true ? "是" : "否";
        QString isComplete = row.value("IsComplete").toBool() == true ? "是" : "否";
        rowData << QString::number(row.value("ID").toInt())
                << row.value("GrainType").toString()\
                << row.value("Class").toString()\
                << row.value("SampleBox").toString()\
                << isStandard\
                << row.value("SampleBag").toString() \
                << QString::number(row.value("UnitWeight").toDouble())\
                << QString::number(row.value("Moisture").toDouble())  \
                << QString::number(row.value("Mildew").toDouble()) \
                << QString::number(row.value("Broken").toDouble())
                << QString::number(row.value("HeatHarm").toDouble()) \
                << QString::number(row.value("SideImpurity").toDouble())
                << QString::number(row.value("Scree").toDouble()) \
                << QString::number(row.value("SoilBlock").toDouble())
                << QString::number(row.value("RodCore").toDouble()) \
                << QString::number(row.value("DifGrain").toDouble())
                << QString::number(row.value("BlistersGrain").toDouble()) \
                << smell\
                << QString::number(row.value("RoughWeight").toDouble()) \
                << QString::number(row.value("NetWeight").toDouble())  \
                << QString::number(row.value("Impurity").toDouble())\
                << isComplete\
                << isReject\
                << row.value("RejectContent").toString()\
                << row.value("Remarks").toString() \
                << row.value("Creater").toString() <<row.value("CreateTime").toString()\
                << row.value("Updater").toString() <<row.value("UpdateTime").toString();
        session.appendRow(rowData);
//        qDebug()<<rowData;
    }
}
