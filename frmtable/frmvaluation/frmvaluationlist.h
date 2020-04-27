#ifndef FRMVALUATIONLIST_H
#define FRMVALUATIONLIST_H

#include <QWidget>

namespace Ui {
class FrmValuationList;
}

class QListWidgetItem;

class FrmValuationList : public QWidget
{
    Q_OBJECT

public:
    explicit FrmValuationList(QWidget *parent = 0);
    ~FrmValuationList();

    void setTitleText(const QString &text);
    QString getTitleText();
    qint32 getRuleCount();
    bool isHaveRejectRule();
    QList<QByteArray> getListItemData();
    void setRuleItem(QByteArray &data);

private slots:
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnAddRule_clicked();
    void on_btnDelRule_clicked();

private:
    Ui::FrmValuationList *ui;
};

#endif // FRMVALUATIONLIST_H
