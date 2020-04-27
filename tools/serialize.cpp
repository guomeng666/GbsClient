#include "serialize.h"
#include <QDebug>

Serialize::Serialize(QObject *parent) : QObject(parent)
{

}

Serialize::Serialize(QByteArray *array)
{
    m_array = array;
    setDataStream();
}

Serialize::~Serialize()
{
    m_buffer.close();
}

Serialize &Serialize::operator<<(const QString &str)
{
    m_stream << str;
    return *this;
}

Serialize &Serialize::operator>>(QString &str)
{
    m_stream >> str;
    return *this;
}

void Serialize::setByteArray(QByteArray *array)
{
    m_array = array;
    setDataStream();
}

void Serialize::setDataStream()
{
    if(m_buffer.isOpen())
        m_buffer.close();
    m_buffer.setBuffer(m_array);
    m_buffer.open(QIODevice::ReadWrite);
    m_stream.setDevice(&m_buffer);
}
