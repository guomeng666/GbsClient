#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "serviceinterface.h"
#include "singleton.h"
#include "gbssession.h"
#include <QMap>


class ServiceManager : public QObject
{
    friend class Singleton<ServiceManager>;
    Q_OBJECT
public:
    bool doAction(GbsSession &session);

signals:

public slots:

private:
    explicit ServiceManager(QObject *parent = nullptr);
    ~ServiceManager();
    QMap<QString, ServiceInterface*> m_servicesMap;
};

#endif // SERVICEMANAGER_H
