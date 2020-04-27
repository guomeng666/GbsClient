#ifndef QUERYWAREHOUSE_H
#define QUERYWAREHOUSE_H

#include "serviceinterface.h"

class QueryWarehouse : public ServiceInterface
{
public:
    QueryWarehouse();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
