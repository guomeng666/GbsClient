#ifndef EDITTRANSPORT_H
#define EDITTRANSPORT_H

#include "serviceinterface.h"

class EditTransport : public ServiceInterface
{
public:
    EditTransport();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITUSER_H
