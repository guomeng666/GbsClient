#ifndef FRMWEIGH_H
#define FRMWEIGH_H

#include <QWidget>

namespace Ui {
class FrmWeigh;
}

class FrmWeigh : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmWeigh(QWidget *parent = 0);
    ~FrmWeigh();

    void editBusinessInformation(QString editStatus);
private slots:
    void topButtonClick();
    void onMenuButtonClick();
    void on_editTagNum_returnPressed();
    void on_btnSubmit_clicked();

private:
    void initStyle();
    void initBtn();
    void initForm();
    Ui::FrmWeigh *ui;
    QString m_currentRegisterID; //当前扦样车辆的登记记录数据库ID
    QString m_currentVehicleID; //当前扦样车辆的车辆数据库ID
    void submitWeighInfo();
};

#endif // FRMWEIGH_H
