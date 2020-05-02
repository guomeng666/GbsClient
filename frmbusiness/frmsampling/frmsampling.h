#ifndef FRMSAMPLING_H
#define FRMSAMPLING_H

#include <QWidget>

namespace Ui {
class FrmSampling;
}

class FrmSampling : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmSampling(QWidget *parent = 0);
    ~FrmSampling();

    void editBusinessInformation(QString editStatus);
private slots:
    void topButtonClick();
    void onMenuButtonClick();

    void on_editTagNum_returnPressed();

    void on_pushButton_3_clicked();

private:
    void initStyle();
    void initBtn();
    void initForm();
    Ui::FrmSampling *ui;
    QString m_currentRegisterID; //当前扦样车辆的登记记录数据库ID
    QString m_currentVehicleID; //当前扦样车辆的车辆数据库ID
};

#endif // FrmSampling_H
