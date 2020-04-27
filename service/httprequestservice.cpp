#include "httprequestservice.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

HttpRequestService::HttpRequestService(QObject *parent) :
    QObject(parent),
    m_timeout(2000)
{
    m_Manager = new QNetworkAccessManager(this);
}

QByteArray HttpRequestService::sendJsonData(const QByteArray jsonData,QString &errString)
{
    QTimer timer;
    timer.setInterval(m_timeout);  // 设置超时时间 30 秒
    timer.setSingleShot(true);  // 单次触发
    qDebug()<<"url:"<<m_url;
    QNetworkRequest request;
    request.setUrl(m_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *pReply = m_Manager->post(request, jsonData);

    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();  // 启动事件循环
    loop.exec();

    // 处理响应
    if (timer.isActive())
    {
        timer.stop();
        if (pReply->error() != QNetworkReply::NoError)
        {
            //返回错误信息
            errString = pReply->errorString();
        }
        else
        {
            QVariant variant = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            int nStatusCode = variant.toInt();
            QByteArray bytes = pReply->readAll();
            qDebug() << "Status Code : " << nStatusCode<<"Data:"<<bytes;
            return bytes;
        }
    }
    else
    {
        // 处理超时
        disconnect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        pReply->abort();
        pReply->deleteLater();
        errString = "Send TimeOut";
    }
    return QByteArray();
}
