#ifndef EDITPAYMENTTYPE_H
#define EDITPAYMENTTYPE_H

#include "serviceinterface.h"

class EditPaymenttype : public ServiceInterface
{
public:
    EditPaymenttype();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITUSER_H
