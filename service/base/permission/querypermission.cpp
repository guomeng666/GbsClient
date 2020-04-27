#include "querypermission.h"

QueryPermission::QueryPermission()
{

}

void QueryPermission::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("PermissionName",QJsonValue(session.getRequestData("PermissionName")));
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
        rowData << QString::number(row.value("ID").toInt())<<row.value("Name").toString()
                <<QString::number(row.value("Quer").toInt())<<QString::number(row.value("Maintain").toInt())
                <<QString::number(row.value("Register").toInt())<<QString::number(row.value("Sampling").toInt())
                <<QString::number(row.value("Assay").toInt())<<QString::number(row.value("Sell").toInt())
                <<QString::number(row.value("Weigh").toInt())<<QString::number(row.value("Unload").toInt())
                <<QString::number(row.value("Settlement").toInt())<<row.value("CreateTime").toString()
                <<row.value("UpdateTime").toString();
        session.appendRow(rowData);
        qDebug()<<session.getRow(i);
    }
}
