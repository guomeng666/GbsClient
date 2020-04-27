#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include <QObject>
#include <QDebug>
#include "gbssession.h"

// 命令基类
class ServiceInterface : public QObject
{

public:
    virtual void Execute(GbsSession& session) = 0;
    virtual ~ServiceInterface() {}

};

#endif // SERVICEINTERFACE_H
