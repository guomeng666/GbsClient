#ifndef GBSSESSION_H
#define GBSSESSION_H
#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMap>
#include "httprequestservice.h"
#include "singleton.h"
#include "systemconfig.h"

#define CmdEditRegister "1"
#define CmdQueryRegister "2"

#define CmdQueryPicture "40"

#define CmdQuerySellerByIdentityID "7"

#define CmdEditVehicle "256"
#define CmdQueryVehicle "257"

#define CmdEditVehicleType "258"
#define CmdQueryVehicleType "259"

#define CmdEditGrainType "260"
#define CmdQueryGrainType "261"

#define CmdEditPackType "262"
#define CmdQueryPackType "263"

#define CmdEditPaymenttype "264"
#define CmdQueryPaymenttype "265"

#define CmdEditSampleClass "266"
#define CmdQuerySampleClass "267"

#define CmdEditBankType "268"
#define CmdQueryBankType "269"

#define CmdEditWarehouse "270"
#define CmdQueryWarehouse "271"

#define CmdEditTransport "272"
#define CmdQueryTransport "273"

#define CmdEditSupplier "274"
#define CmdQuerySupplier "275"

#define CmdEditContractType "276"
#define CmdQueryContractType "277"

#define CmdEditPurchase "278"
#define CmdQueryPurchase "279"

#define CmdEditProcedureNode "280"
#define CmdQueryProcedureNode "281"

#define CmdEditSeller "282"
#define CmdQuerySeller "283"

#define CmdEditContract "284"
#define CmdQueryContract "285"

#define CmdEditValuation "290"
#define CmdQueryValuation "291"

#define CmdEditDepartment "501"
#define CmdQueryDepartment "502"

#define CmdEditRole "503"
#define CmdQueryRoel "504"

#define CmdEditUser "505"
#define CmdQueryUser "506"

#define CmdEditPermission "507"
#define CmdQuerPermission "508"

#define errNetWork     255
#define errDataExist   3  //添加的数据已经存在
#define errDataNoExist 4 //修改的数据不存在
#define errSelectItem  5  //修改数据的选择项已经删除

#define errNoExist  8  //修改数据的选择项已经删除

class GbsSession : public QObject
{
    Q_OBJECT
public:

    explicit GbsSession(QObject *parent = nullptr);
    //用于添加向服务器请求的数据
    void addRequestData(QString key, QString value);
    //封包发送数据
    bool sendDataToServer(QByteArray &data);
    //接收服务器返回的数据
    QString getCmd();
    //设置请求地址
    void setRequestUrl(const QString &url){ httpService.setHostUrl(url);}

    const QString getRequestData(const QString& k) const;

    quint32 getErrNo() { return m_errno ;}

    void setErrNo(int errNo) { m_errno = errNo; }

    const QString getErrString(int errNo);
    //获取未经解析的服务器返回数据
    QByteArray getResultRawData(){ return m_rawData; }
    //获取应答数据的行数
    quint32 getRowSize() { return m_row.size(); }
    //获取应数据的列数
    quint32 getCloumSize();
    //设置数据总量
    void setTotalAmount(qint32 total){ m_total = total; }
    //获取数据总量
    qint32 getTotalAmount() { return m_total; }
    //设置当前请求页
    void setCurPage(qint32 page) { m_curPage = page; }
    //获取当前请求页
    qint32 getCurPage() { return m_curPage; }
    //添加一行数据
    void appendRow(QStringList &row){ m_row<<row; }
    //获取一行数据
    QStringList getRow(quint32 rowNum) { return m_row.at(rowNum); }
    //获取最后的错误值
    QString getLastErrString();
    //获取组装好的表格数据
    QList<QStringList> getTableData() {return m_row; }

signals:

public slots:

private:
    HttpRequestService httpService;
    quint32 m_errno;     //错误编码
    QMap<QString,QString> m_dataMap;
    QMap<int, QString> m_errMap;
    QList<QStringList> m_row; //行数据
    quint32 m_total; //数据总量
    quint32 m_curPage; //当前请求的页号
    QString m_errStr;//错误说明
    QByteArray m_rawData; //未解析的数据
};

#endif // GBSSESSION_H
