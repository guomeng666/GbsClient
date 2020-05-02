#include "queryregisterbytagnum.h"

QueryRegisterByTagNum::QueryRegisterByTagNum()
{

}

void QueryRegisterByTagNum::Execute(GbsSession &session)
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
    session.setCurPage( doc.object().value("Page").toString().toInt());
    session.setTotalAmount(doc.object().value("TotalData").toInt());

    QJsonArray data = rootObj.value("Data").toArray();
    for(int i = 0; i < data.size(); ++i ) {
        QJsonObject row = data.at(i).toObject();
        QStringList rowData;
        rowData << QString::number(row.value("ID").toInt())<<row.value("PurchaseType").toString()\
                   <<row.value("PackType").toString()<<row.value("GrainType").toString()\
                   <<row.value("License").toString()<<row.value("VehicleType").toString()\
                   <<row.value("VehicleColor").toString()<<row.value("VehicleFrame").toString()\
                   <<QString::number(row.value("VehicleID").toInt());
        qDebug()<<rowData;
        session.appendRow(rowData);
    }
}
