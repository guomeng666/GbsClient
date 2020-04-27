#ifndef QUERYTRANSPORT_H
#define QUERYTRANSPORT_H

#include "serviceinterface.h"

class QueryTransport : public ServiceInterface
{
public:
    QueryTransport();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
