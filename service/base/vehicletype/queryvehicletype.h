#ifndef QUERYVEHICLETYPE_H
#define QUERYVEHICLETYPE_H

#include "serviceinterface.h"

class QueryVehicleType : public ServiceInterface
{
public:
    QueryVehicleType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYVEHICLETYPE_H
