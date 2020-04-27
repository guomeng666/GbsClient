#ifndef EDITVEHICLE_H
#define EDITVEHICLE_H

#include "serviceinterface.h"

class EditVehicle : public ServiceInterface
{
public:
    EditVehicle();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITVEHICLETYPE_H
