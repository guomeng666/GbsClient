#include "edituser.h"

EditUser::EditUser()
{

}

void EditUser::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Operation",QJsonValue(session.getRequestData("Operation")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
    rootObj.insert("UserName",QJsonValue(session.getRequestData("UserName")));
    rootObj.insert("UserPassword",QJsonValue(session.getRequestData("UserPassword")));
    rootObj.insert("UserIdentityID",QJsonValue(session.getRequestData("UserIdentityID")));
    rootObj.insert("UserAddress",QJsonValue(session.getRequestData("UserAddress")));
    rootObj.insert("UserRoleID",QJsonValue(session.getRequestData("UserRoleID")));
    rootObj.insert("UserDepartmentID",QJsonValue(session.getRequestData("UserDepartmentID")));
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
