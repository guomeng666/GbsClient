#ifndef FRMSELL_H
#define FRMSELL_H

#include <QWidget>

namespace Ui {
class FrmSell;
}

class FrmSell : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmSell(QWidget *parent = 0);
    ~FrmSell();

private slots:
    void on_lineEdit_returnPressed();
    void onCountDown();

    void on_btnRetrun_clicked();

    void on_btnSell_clicked();

    void on_btnRejectSell_clicked();

private:
    void initStyle();
    void initBtn();
    void initForm();
    Ui::FrmSell *ui;
    void queryAssayInfo(QString icNumber);
    void clearFrm();
    void sellGrain(bool isSell);
    qint32 m_countDown;
    QString m_procedureNum;
    QTimer *countDownTimer;
};

#endif // FRMSELL_H
