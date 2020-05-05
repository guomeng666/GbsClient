#include "queryweigh.h"

QueryWeigh::QueryWeigh()
{

}

void QueryWeigh::Execute(GbsSession &session)
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
        QString pictureNum = "";
        if(row.value("PrictureID").toInt() != 0)
            pictureNum = QString::number(row.value("PrictureID").toInt());

        rowData << QString::number(row.value("ID").toInt())\
                << QString::number(row.value("RegisterID").toInt())\
                << row.value("License").toString()\
                << QString::number(row.value("RoughWeight").toInt())\
                << row.value("RoughDate").toString() \
                << row.value("RoughOperator").toString()\
                << row.value("RoughRemarks").toString() \
                << QString::number(row.value("TareWeight").toInt())\
                << row.value("TareDate").toString() \
                << row.value("TareOperator").toString()\
                << row.value("TareRemarks").toString() \
                << QString::number(row.value("NetWeight").toInt()) \
                << pictureNum\
                << row.value("Creater").toString() <<row.value("CreateTime").toString()\
                << row.value("Updater").toString() <<row.value("UpdateTime").toString();
        session.appendRow(rowData);
//        qDebug()<<rowData;
    }
}
