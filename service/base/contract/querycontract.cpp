#include "querycontract.h"

QueryContract::QueryContract()
{

}

void QueryContract::Execute(GbsSession &session)
{
    //封包处理
    session.setRequestUrl(Singleton<SystemConfig>::Instance().getQueryIntefaceUrl());
    QJsonDocument doc;
    QJsonObject rootObj;
    rootObj.insert("Cmd", QJsonValue(session.getRequestData("Cmd")));
    rootObj.insert("Sender",QJsonValue(session.getRequestData("Sender")));
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
        rowData << QString::number(row.value("ID").toInt())<< row.value("ContractNum").toString()\
                << row.value("ContractType").toString() << row.value("GrainType").toString()\
                << row.value("Start").toString() << row.value("End").toString()\
                << row.value("OrderID").toString()<< row.value("Supplier").toString() \
                << row.value("TransCompany").toString()<< row.value("Source").toString() \
                << QString::number(row.value("Total").toInt()) \
                << QString::number(row.value("Complete").toInt()) \
                << QString::number(row.value("IsComplete").toBool())\
                << row.value("TransportNum").toString()\
                << row.value("WagaonNum").toString() << row.value("PayType").toString()\
                << row.value("BankType").toString() << row.value("BankNum").toString()\
                << row.value("Valuation").toString() << row.value("Contact").toString() \
                << row.value("ContactPhone").toString() << row.value("Remark").toString()\
                << row.value("Creater").toString() <<row.value("CreateTime").toString()\
                << row.value("Updater").toString() <<row.value("UpdateTime").toString();
        session.appendRow(rowData);
//        qDebug()<<rowData;
    }
}
