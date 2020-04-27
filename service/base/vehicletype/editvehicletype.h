#ifndef EDITVEHICLETYPE_H
#define EDITVEHICLETYPE_H

#include "serviceinterface.h"

class EditVehicleType : public ServiceInterface
{
public:
    EditVehicleType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITVEHICLETYPE_H
