#include "querypicture.h"

QueryPicture::QueryPicture()
{

}

void QueryPicture::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("Node",QJsonValue(session.getRequestData("Node")));
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

    QJsonObject data = rootObj.value("Data").toObject();
    QStringList rowData;

    rowData << data.value("Picture1").toString() << data.value("Picture2").toString()\
            << data.value("Picture3").toString() << data.value("Picture4").toString();
    session.appendRow(rowData);

}
