#ifndef EDITUNLOAD_H
#define EDITUNLOAD_H

#include "serviceinterface.h"

class EditUnload : public ServiceInterface
{
public:
    EditUnload();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITUNLOAD_H
