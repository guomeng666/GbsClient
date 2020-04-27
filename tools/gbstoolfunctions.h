#ifndef GBSTOOLFUNCTIONS_H
#define GBSTOOLFUNCTIONS_H

#include <QObject>

class QComboBox;
class QLabel;

class GbsToolFunctions : public QObject
{
    Q_OBJECT

public:
    explicit GbsToolFunctions(QObject *parent = nullptr);
    static void setComboxItem(const QString cmd, QComboBox *bx);
    //使用身份证号码获取售粮户信息
    static bool getSellerInfoByIdentityID(QString identity, QStringList &result);
    static bool getVehicleByLiscense(QString liscense, QStringList &result);
    static QString lablePixmapToString(QLabel* lab);
    static bool contractIsValid(const QString &num);

    static QList<QImage> getImageFromService(const QString &nodeName, const QString &number);
signals:

public slots:
};

#endif // GBSTOOLFUNCTIONS_H
