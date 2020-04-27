#ifndef EDITVALUATION_H
#define EDITVALUATION_H

#include "serviceinterface.h"

class EditValuation : public ServiceInterface
{
public:
    EditValuation();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITDEPARMENT_H
