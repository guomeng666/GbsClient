#ifndef QUERYSAMPLECLASS_H
#define QUERYSAMPLECLASS_H

#include "serviceinterface.h"

class QuerySampleClass : public ServiceInterface
{
public:
    QuerySampleClass();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYSAMPLECLASS_H
