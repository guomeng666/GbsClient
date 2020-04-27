#ifndef FRMREGISTER_H
#define FRMREGISTER_H

#include <QWidget>

namespace Ui {
class FrmRegister;
}

class FrmRegister : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmRegister(QWidget *parent = 0);
    ~FrmRegister();

private slots:
    void on_cbxpurchase_currentIndexChanged(int index);
    void topButtonClick();
    void onMenuButtonClick();
    void on_btnSave_clicked();

    void on_editSellerNum_returnPressed();

    void on_editPayeeNum_returnPressed();

    void on_editLiscense_returnPressed();

    void on_btnClear_clicked();

    void on_editDriverNum_returnPressed();

private:
    void initStyle();
    void initBtn();
    void initForm();
    void setVehicleType();
    void setGrainType();
    void setPackType();
    void setPayMentType();
    void setBankType();
    bool checkFrmEditData(PurchaseType type);
    void editBusinessInformation(QString editStatus);
    Ui::FrmRegister *ui;
    void getPricture();
};

#endif // FRMREGISTER_H
