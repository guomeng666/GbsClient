#ifndef QUERYVEHICLE_H
#define QUERYVEHICLE_H

#include "serviceinterface.h"

class QueryVehicle : public ServiceInterface
{
public:
    QueryVehicle();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYVEHICLETYPE_H
