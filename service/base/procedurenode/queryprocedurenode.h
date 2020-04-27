#ifndef QUERYPROCEDURENODE_H
#define QUERYPROCEDURENODE_H

#include "serviceinterface.h"

class QueryProcedureNode : public ServiceInterface
{
public:
    QueryProcedureNode();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
