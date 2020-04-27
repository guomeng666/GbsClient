#ifndef QUERYPAYMENTTYPE_H
#define QUERYPAYMENTTYPE_H

#include "serviceinterface.h"

class QueryPaymenttype : public ServiceInterface
{
public:
    QueryPaymenttype();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
