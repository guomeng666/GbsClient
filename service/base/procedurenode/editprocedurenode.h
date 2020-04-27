#ifndef EDITPROCEDURENODE_H
#define EDITPROCEDURENODE_H

#include "serviceinterface.h"

class EditProcedureNode : public ServiceInterface
{
public:
    EditProcedureNode();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITPROCEDURENODE_H
