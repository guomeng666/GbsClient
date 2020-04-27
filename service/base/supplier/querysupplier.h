#ifndef QUERYSUPPLIER_H
#define QUERYSUPPLIER_H

#include "serviceinterface.h"

class QuerySupplier : public ServiceInterface
{
public:
    QuerySupplier();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
