#ifndef QUERYGRAINTYPE_H
#define QUERYGRAINTYPE_H

#include "serviceinterface.h"

class QueryGrainType : public ServiceInterface
{
public:
    QueryGrainType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYGRAINTYPE_H
