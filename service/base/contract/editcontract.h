#ifndef EDITCONTRACT_H
#define EDITCONTRACT_H

#include "serviceinterface.h"

class EditContract : public ServiceInterface
{
public:
    EditContract();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITCONTRACTTYPE_H
