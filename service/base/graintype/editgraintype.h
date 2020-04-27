#ifndef EDITGRAINTYPE_H
#define EDITGRAINTYPE_H

#include "serviceinterface.h"

class EditGrainType : public ServiceInterface
{
public:
    EditGrainType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITGRAINTYPE_H
