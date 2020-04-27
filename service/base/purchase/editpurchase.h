#ifndef EDITPURCHASE_H
#define EDITPURCHASE_H

#include "serviceinterface.h"

class EditPurchase : public ServiceInterface
{
public:
    EditPurchase();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITPURCHASE_H
