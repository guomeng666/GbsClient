#ifndef QUERYPERMISSION_H
#define QUERYPERMISSION_H

#include "serviceinterface.h"

class QueryPermission : public ServiceInterface
{
public:
    QueryPermission();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYPERMISSION_H
