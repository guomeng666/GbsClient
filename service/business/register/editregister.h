#ifndef EDITREGISTER_H
#define EDITREGISTER_H

#include "serviceinterface.h"

class EditRegister : public ServiceInterface
{
public:
    EditRegister();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITBANKTYPE_H
