#ifndef QUERYSETTLEMENT_H
#define QUERYSETTLEMENT_H

#include "serviceinterface.h"

class QuerySettlement : public ServiceInterface
{
public:
    QuerySettlement();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYSETTLEMENT_H
