#ifndef QUERYSAMPLING_H
#define QUERYSAMPLING_H

#include "serviceinterface.h"

class QuerySampling : public ServiceInterface
{
public:
    QuerySampling();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYSAMPLING_H
