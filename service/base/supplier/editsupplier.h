#ifndef EDITSUPPLIER_H
#define EDITSUPPLIER_H

#include "serviceinterface.h"

class EditSupplier : public ServiceInterface
{
public:
    EditSupplier();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITUSER_H
