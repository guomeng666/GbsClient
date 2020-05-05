#ifndef EDITWEIGH_H
#define EDITWEIGH_H

#include "serviceinterface.h"

class EditWeigh : public ServiceInterface
{
public:
    EditWeigh();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITWEIGH_H
