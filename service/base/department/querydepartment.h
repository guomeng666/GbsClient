#ifndef QUERYDEAPARTMENT_H
#define QUERYDEAPARTMENT_H

#include "serviceinterface.h"

class QueryDepartment : public ServiceInterface
{
public:
    QueryDepartment();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYDEAPARTMENT_H
