#ifndef QUERYASSAYTOSELL_H
#define QUERYASSAYTOSELL_H

#include "serviceinterface.h"

class QueryAssayToSell : public ServiceInterface
{
public:
    QueryAssayToSell();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYASSAYTOSELL_H
