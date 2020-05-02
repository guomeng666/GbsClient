#include "editsampling.h"

EditSampling::EditSampling()
{

}

void EditSampling::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("RegisterID",QJsonValue(session.getRequestData("RegisterID")));
    rootObj.insert("SampleBoxNum",QJsonValue(session.getRequestData("SampleBoxNum")));
    rootObj.insert("Remarks",QJsonValue(session.getRequestData("Remarks")));
    rootObj.insert("Picture1",QJsonValue(session.getRequestData("Picture1")));
    rootObj.insert("Picture2",QJsonValue(session.getRequestData("Picture2")));
    rootObj.insert("Picture3",QJsonValue(session.getRequestData("Picture3")));
    rootObj.insert("Picture4",QJsonValue(session.getRequestData("Picture4")));
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
