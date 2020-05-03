#ifndef QUERYSELL_H
#define QUERYSELL_H

#include "serviceinterface.h"

class QuerySell : public ServiceInterface
{
public:
    QuerySell();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYSELL_H
