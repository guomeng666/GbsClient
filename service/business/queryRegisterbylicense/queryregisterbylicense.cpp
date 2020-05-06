#include "queryregisterbylicense.h"

QueryRegisterByLicense::QueryRegisterByLicense()
{

}

void QueryRegisterByLicense::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("License",QJsonValue(session.getRequestData("License")));
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

    QJsonObject row = rootObj.value("Data").toObject();
    QStringList rowData;
    rowData << QString::number(row.value("RegisterID").toInt())
            <<row.value("PurchaseType").toString()\
            <<row.value("PackType").toString()
            <<row.value("GrainType").toString()\
            <<row.value("License").toString()
            <<row.value("VehicleType").toString()\
            <<row.value("VehicleColor").toString()
            <<row.value("VehicleFrame").toString();
    qDebug()<<rowData;
    session.appendRow(rowData);
}
