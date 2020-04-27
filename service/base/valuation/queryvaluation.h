#ifndef QUERYVALUATION_H
#define QUERYVALUATION_H

#include "serviceinterface.h"

class QueryValuation : public ServiceInterface
{
public:
    QueryValuation();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYDEPARTMENT_H
