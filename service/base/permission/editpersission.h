#ifndef EDITPERSISSION_H
#define EDITPERSISSION_H

#include "serviceinterface.h"

class EditPersission : public ServiceInterface
{
public:
    EditPersission();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITPERSISSION_H
