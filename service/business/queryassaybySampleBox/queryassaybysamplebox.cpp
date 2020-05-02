#include "queryassaybysamplebox.h"

QueryAssaySampleBox::QueryAssaySampleBox()
{

}

void QueryAssaySampleBox::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Name",QJsonValue(session.getRequestData("Name")));
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
    QJsonObject data = rootObj.value("Data").toObject();
    QStringList rowData;
    rowData << QString::number(data.value("ID").toInt())\
            << data.value("GrainType").toString();
    qDebug()<<rowData;
    session.appendRow(rowData);
}
