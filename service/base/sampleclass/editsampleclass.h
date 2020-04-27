#ifndef EDITSAMPLECLASS_H
#define EDITSAMPLECLASS_H

#include "serviceinterface.h"

class EditSampleClass : public ServiceInterface
{
public:
    EditSampleClass();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // EDITSAMPLECLASS_H
