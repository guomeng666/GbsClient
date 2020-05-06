#ifndef QUERYUNLOAD_H
#define QUERYUNLOAD_H

#include "serviceinterface.h"

class QueryUnload : public ServiceInterface
{
public:
    QueryUnload();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYUNLOAD_H
