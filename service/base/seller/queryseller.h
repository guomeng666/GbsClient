#ifndef QUERYSELLER_H
#define QUERYSELLER_H

#include "serviceinterface.h"

class QuerySeller : public ServiceInterface
{
public:
    QuerySeller();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYVEHICLETYPE_H
