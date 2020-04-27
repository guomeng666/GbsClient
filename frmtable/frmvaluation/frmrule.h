#ifndef FRMRULE_H
#define FRMRULE_H

#include <QDialog>

namespace Ui {
class FrmRule;
}

class FrmRule : public QDialog
{
    Q_OBJECT

public:
    explicit FrmRule(QWidget *parent = 0);
    ~FrmRule();
    QByteArray getRule() { return m_rule; }

private slots:
    void on_comboBox_activated(const QString &arg1);
    void on_btnOk_clicked();

private:
    bool checkRules();
    Ui::FrmRule *ui;
    QByteArray m_rule;
};

#endif // FRMRULE_H
