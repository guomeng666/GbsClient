#ifndef HTTPREQUESTSERVICE_H
#define HTTPREQUESTSERVICE_H

#include <QObject>
#include <QNetworkReply>
#include <QTimer>
/**
  *使用Http协议的POST请求向服务器请求数据或者发送数据
  *同步发送,默认超时时间5秒
*/


class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;


class HttpRequestService : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequestService(QObject *parent = nullptr);

    //使用Http的Post方法发送Json数据
    QByteArray sendJsonData(const QByteArray jsonData, QString &errString);
    //设置发送超时时间
    void setRecvTimeOut(int time) { m_timeout = time; }
    //设置主机URL地址
    void setHostUrl(const QString url) { m_url.setUrl(url); }

signals:

public slots:

private:
    int m_timeout;
    QUrl m_url;
    QNetworkAccessManager *m_Manager;
};

#endif // HTTPREQUESTSERVICE_H
