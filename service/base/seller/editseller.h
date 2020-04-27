#ifndef EDITSELLER_H
#define EDITSELLER_H

#include "serviceinterface.h"

class EditSeller : public ServiceInterface
{
public:
    EditSeller();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITSELLER_H
