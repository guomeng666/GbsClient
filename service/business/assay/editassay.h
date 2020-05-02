#ifndef EDITASSAY_H
#define EDITASSAY_H

#include "serviceinterface.h"

class EditAssay : public ServiceInterface
{
public:
    EditAssay();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITASSAY_H
