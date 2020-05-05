#ifndef QUERYWEIGHPICTURE_H
#define QUERYWEIGHPICTURE_H

#include "serviceinterface.h"

class QueryWeighPicture : public ServiceInterface
{
public:
    QueryWeighPicture();
    void Execute(GbsSession& session) Q_DECL_OVERRIDE;
};

#endif // QUERYWEIGHPICTURE_H
