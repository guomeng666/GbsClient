#ifndef QUERYPACKTYPE_H
#define QUERYPACKTYPE_H

#include "serviceinterface.h"

class QueryPackType : public ServiceInterface
{
public:
    QueryPackType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYPACKTYPE_H
