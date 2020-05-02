#ifndef QUERYASSAYSAMPLEBOX_H
#define QUERYASSAYSAMPLEBOX_H

#include "serviceinterface.h"

class QueryAssaySampleBox : public ServiceInterface
{
public:
    QueryAssaySampleBox();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYASSAYSAMPLEBOX_H
