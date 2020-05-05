#ifndef QUERYWEIGH_H
#define QUERYWEIGH_H

#include "serviceinterface.h"

class QueryWeigh : public ServiceInterface
{
public:
    QueryWeigh();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWEIGH_H
