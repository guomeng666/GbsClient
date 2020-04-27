#ifndef EDITDEPARTMENT_H
#define EDITDEPARTMENT_H

#include "serviceinterface.h"

class EditDeparment : public ServiceInterface
{
public:
    EditDeparment();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITUSER_H
