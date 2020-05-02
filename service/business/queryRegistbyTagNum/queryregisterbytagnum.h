#ifndef QUERYREGISTERBYTAGNUM_H
#define QUERYREGISTERBYTAGNUM_H

#include "serviceinterface.h"

class QueryRegisterByTagNum : public ServiceInterface
{
public:
    QueryRegisterByTagNum();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYREGISTERBYTAGNUM_H
