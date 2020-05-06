#ifndef QUERYREGISTERBYLICENSE_H
#define QUERYREGISTERBYLICENSE_H

#include "serviceinterface.h"

class QueryRegisterByLicense : public ServiceInterface
{
public:
    QueryRegisterByLicense();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYREGISTERBYLICENSE_H
