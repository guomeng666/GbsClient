#ifndef EDITWAREHOUSE_H
#define EDITWAREHOUSE_H

#include "serviceinterface.h"

class EditWarehouse : public ServiceInterface
{
public:
    EditWarehouse();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITUSER_H
