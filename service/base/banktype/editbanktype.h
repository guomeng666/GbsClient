#ifndef EDITBANKTYPE_H
#define EDITBANKTYPE_H

#include "serviceinterface.h"

class EditBankType : public ServiceInterface
{
public:
    EditBankType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITBANKTYPE_H
