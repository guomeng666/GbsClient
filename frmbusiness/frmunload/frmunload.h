#ifndef FRMUNLOAD_H
#define FRMUNLOAD_H

#include <QWidget>

namespace Ui {
class FrmUnload;
}

class FrmUnload : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmUnload(QWidget *parent = 0);
    ~FrmUnload();
    void showEvent(QShowEvent *event);

private slots:
    void topButtonClick();
    void onMenuButtonClick();
    void on_btnSubmit_clicked();
    void on_editLiscense_returnPressed();

private:
    void initStyle();
    void initBtn();
    void initForm();
    Ui::FrmUnload *ui;
    QString m_currentRegisterID; //当前扦样车辆的登记记录数据库ID
    QString m_currentVehicleID; //当前扦样车辆的车辆数据库ID
    void submitTakeInfo();
};

#endif // FRMUNLOAD_H
