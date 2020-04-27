#ifndef QUERYCONTRACT_H
#define QUERYCONTRACT_H

#include "serviceinterface.h"

class QueryContract : public ServiceInterface
{
public:
    QueryContract();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYCONTRACTTYPE_H
