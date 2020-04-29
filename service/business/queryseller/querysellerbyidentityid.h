#ifndef QUERYSELLERBYIDENTITYID_H
#define QUERYSELLERBYIDENTITYID_H

#include "serviceinterface.h"

class QuerySellerByIdentityID : public ServiceInterface
{
public:
    QuerySellerByIdentityID();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWAREHOUSE_H
