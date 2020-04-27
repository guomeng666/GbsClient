#ifndef QUERYREGISTER_H
#define QUERYREGISTER_H

#include "serviceinterface.h"

class QueryRegister : public ServiceInterface
{
public:
    QueryRegister();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
