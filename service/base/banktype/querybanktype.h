#ifndef QUERYBANKTYPE_H
#define QUERYBANKTYPE_H

#include "serviceinterface.h"

class QueryBankType : public ServiceInterface
{
public:
    QueryBankType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
