#ifndef QUERYDEPARTMENT_H
#define QUERYDEPARTMENT_H

#include "serviceinterface.h"

class QueryUser : public ServiceInterface
{
public:
    QueryUser();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYDEPARTMENT_H
