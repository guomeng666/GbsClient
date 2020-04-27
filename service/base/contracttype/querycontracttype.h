#ifndef QUERYCONTRACTTYPE_H
#define QUERYCONTRACTTYPE_H

#include "serviceinterface.h"

class QueryContractType : public ServiceInterface
{
public:
    QueryContractType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYCONTRACTTYPE_H
