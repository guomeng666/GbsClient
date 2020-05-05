#ifndef ALTERWEIGH_H
#define ALTERWEIGH_H

#include "serviceinterface.h"

class AlterWeigh : public ServiceInterface
{
public:
    AlterWeigh();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // ALTERWEIGH_H
