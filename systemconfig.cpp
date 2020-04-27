#include "systemconfig.h"

SystemConfig::SystemConfig(QObject *parent) : QObject(parent)
{
    m_queryUrl    = "http://127.0.0.1:5000/services/query";
    m_businessUrl = "http://127.0.0.1:5000/services/business";
}

SystemConfig::~SystemConfig()
{

}
