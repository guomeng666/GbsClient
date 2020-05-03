#ifndef SELLGRAIN_H
#define SELLGRAIN_H

#include "serviceinterface.h"

class SellGrain : public ServiceInterface
{
public:
    SellGrain();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // SELLGRAIN_H
