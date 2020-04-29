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

private:
    void initStyle();
    void initBtn();
    void initForm();
    Ui::FrmSampling *ui;
};

#endif // FrmSampling_H
