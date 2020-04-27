#ifndef EDITROLE_H
#define EDITROLE_H

#include "serviceinterface.h"

class EditRole : public ServiceInterface
{
public:
    EditRole();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITROLE_H
