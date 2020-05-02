#ifndef QUERYASSAY_H
#define QUERYASSAY_H

#include "serviceinterface.h"

class QueryAssay : public ServiceInterface
{
public:
    QueryAssay();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYASSAY_H
