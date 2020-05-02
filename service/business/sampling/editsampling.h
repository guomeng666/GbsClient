#ifndef EDITSAMPLING_H
#define EDITSAMPLING_H

#include "serviceinterface.h"

class EditSampling : public ServiceInterface
{
public:
    EditSampling();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITSAMPLING_H
