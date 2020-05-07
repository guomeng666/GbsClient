#ifndef FRMSETTLEMENT_H
#define FRMSETTLEMENT_H

#include <QWidget>

namespace Ui {
class FrmSettlement;
}

class FrmSettlement : public QWidget
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };

public:
    explicit FrmSettlement(QWidget *parent = 0);
    ~FrmSettlement();

private slots:
    void on_lineEdit_returnPressed();
    void onCountDown();

    void on_btnRetrun_clicked();

private:
    void initStyle();
    void initBtn();
    void initForm();
    void querySettlementInfo(QString icNumber);
    Ui::FrmSettlement *ui;
    void clearFrm();
    qint32 m_countDown;
    QString m_procedureNum;
    QTimer *countDownTimer;
};

#endif // FRMSETTLEMENT_H
