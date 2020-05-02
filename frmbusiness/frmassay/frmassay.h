#ifndef FRMASSAY_H
#define FRMASSAY_H

#include <QWidget>

namespace Ui {
class FrmAssay;
}

class FrmAssay : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmAssay(QWidget *parent = 0);
    ~FrmAssay();

    void submitAssayData();
private slots:
    void topButtonClick();
    void onMenuButtonClick();\
    void on_editSampleBoxNum_returnPressed();
    void on_btnSubmit_clicked();
    bool checkEditData();

    private:
    void initStyle();
    void initBtn();
    void initForm();
    Ui::FrmAssay *ui;

};

#endif // FRMASSAY_H
