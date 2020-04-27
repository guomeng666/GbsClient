#ifndef QUERYPICTURE_H
#define QUERYPICTURE_H

#include "serviceinterface.h"

class QueryPicture : public ServiceInterface
{
public:
    QueryPicture();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYPICTURE_H
