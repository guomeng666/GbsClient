#include "querysettlement.h"

QuerySettlement::QuerySettlement()
{

}

void QuerySettlement::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
    rootObj.insert("Number",QJsonValue(session.getRequestData("Number")));
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
    rowData << QString::number(row.value("ProcedureID").toInt())\
            << QString::number(row.value("RegisterID").toInt())\
            << row.value("PurchaseType").toString()\
            << row.value("GrainType").toString()\
            << row.value("PackType").toString()\
            << row.value("License").toString()\
            << row.value("VehicleType").toString()\
            << row.value("Color").toString()\
            << row.value("Frame").toString()\
            << QString::number(row.value("CupageRatio").toDouble())\
            << QString::number(row.value("MoistureRatio").toDouble())\
            << QString::number(row.value("ImpurityRatio").toDouble())\
            << QString::number(row.value("MildewRatio").toDouble())\
            << QString::number(row.value("BrokenRatio").toDouble())\
            << QString::number(row.value("HeatHarmRatio").toDouble())\
            << QString::number(row.value("SidebysideImpurityRatio").toDouble())\
            << QString::number(row.value("TotalRatio").toDouble())\
            << QString::number(row.value("UnloadDeduct").toDouble())\
            << QString::number(row.value("RoughWeight").toDouble())\
            << QString::number(row.value("TareWeight").toDouble())\
            << QString::number(row.value("NetWeight").toDouble())\
            << QString::number(row.value("ValidWeight").toDouble())\
            << row.value("Valuation").toString()\
            << QString::number(row.value("UnitPrice").toDouble())\
            << QString::number(row.value("TotalPrice").toDouble())\
            << row.value("Seller").toString()\
            << row.value("PayType").toString()\
            << row.value("BankType").toString()\
            << row.value("BankNum").toString();
            session.appendRow(rowData);
            qDebug()<<rowData;
}
