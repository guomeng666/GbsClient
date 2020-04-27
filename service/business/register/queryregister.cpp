#include "queryregister.h"

QueryRegister::QueryRegister()
{

}

void QueryRegister::Execute(GbsSession &session)
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
        rowData << QString::number(row.value("ID").toInt()) << row.value("PurchaseType").toString()\
                << row.value("ContractNum").toString()\
                << row.value("GrainType").toString() << row.value("PackType").toString() \
                << row.value("Pay").toString()   << row.value("TagNum").toString()  \
                << row.value("ICNum").toString() << row.value("License").toString() \
                << row.value("VehicleType").toString() << row.value("Color").toString() \
                << row.value("Frame").toString() << row.value("SellerName").toString() \
                << row.value("SellerNum").toString() << row.value("SellerAddress").toString() \
                << row.value("SellerPhone").toString() << row.value("PayeeName").toString() \
                << row.value("PayeeNum").toString() << row.value("PayeeAddress").toString() \
                << row.value("PayeePhone").toString()  \
                << row.value("BankType").toString() << row.value("BankNum").toString() \
                << row.value("DriverName").toString()\
                << row.value("DriverNum").toString() << row.value("DriverAddress").toString() \
                << row.value("DriverPhone").toString() << row.value("Remark").toString() \
                << pictureNum\
                << row.value("Creater").toString() <<row.value("CreateTime").toString()
                << row.value("Updater").toString() <<row.value("UpdateTime").toString();
        session.appendRow(rowData);
//        qDebug()<<rowData;
    }
}
