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
    //使用车牌号码获取车辆信息
    static bool getVehicleByLiscense(QString liscense, QStringList &result);
    //使用电子标签获取车辆信息
    static bool getRegisterInfoByTagNum(QString tagNum, QStringList &result);
    //使用车牌号码获取登记信息
    static bool getRegisterByLiscense(QString liscense, QStringList &result);

    static QString lablePixmapToString(QLabel* lab);
    static bool contractIsValid(const QString &num);
    static QList<QImage> getImageFromService(const QString &nodeName, const QString &number);

signals:

public slots:
};

#endif // GBSTOOLFUNCTIONS_H
