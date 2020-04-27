#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QObject>
#include <QBuffer>
#include <QDataStream>

class Serialize : public QObject
{
    Q_OBJECT
public:
    explicit Serialize(QObject *parent = nullptr);
    Serialize(QByteArray *array);
    ~Serialize();

    Serialize& operator<<(const QString &);
    Serialize& operator>>(QString &);

    void setByteArray(QByteArray *array);

signals:

public slots:
private:
    void setDataStream();
    QBuffer m_buffer;
    QDataStream m_stream;
    QByteArray *m_array;
};

#endif // SERIALIZE_H
