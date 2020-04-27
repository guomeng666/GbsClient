#ifndef EDITCONTRACTTYPE_H
#define EDITCONTRACTTYPE_H

#include "serviceinterface.h"

class EditContractType : public ServiceInterface
{
public:
    EditContractType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITCONTRACTTYPE_H
