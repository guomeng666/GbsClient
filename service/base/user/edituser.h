#ifndef EDITUSER_H
#define EDITUSER_H

#include "serviceinterface.h"

class EditUser : public ServiceInterface
{
public:
    EditUser();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITDEPARMENT_H
