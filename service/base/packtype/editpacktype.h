#ifndef EDITPACKTYPE_H
#define EDITPACKTYPE_H

#include "serviceinterface.h"

class EditPackType : public ServiceInterface
{
public:
    EditPackType();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITPACKTYPE_H
