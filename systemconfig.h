#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <QObject>
#include "singleton.h"

class SystemConfig : public QObject
{
    Q_OBJECT
    friend class Singleton<SystemConfig>;

public:
    QString getQueryIntefaceUrl() { return m_queryUrl; }
    QString getBusinessUrl() { return m_businessUrl; }

signals:

public slots:

private:
    explicit SystemConfig(QObject *parent = nullptr);
    ~SystemConfig();

    QString m_queryUrl;  //请求接口地址
    QString m_businessUrl; //业务接口地址
};

#endif // SYSTEMCONFIG_H
