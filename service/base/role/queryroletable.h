#ifndef QUERYROLETABLE_H
#define QUERYROLETABLE_H

#include "serviceinterface.h"

class QueryRoleTable : public ServiceInterface
{
public:
     QueryRoleTable();
     void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYROLETABLE_H
