#ifndef QUERYPURCHASE_H
#define QUERYPURCHASE_H

#include "serviceinterface.h"

class QueryPurchase : public ServiceInterface
{
public:
    QueryPurchase();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYDEPARTMENT_H
