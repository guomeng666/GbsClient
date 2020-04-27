#ifndef FRMPURCHASEEDIT_H
#define FRMPURCHASEEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmPurchaseEdit;
}

class FrmPurchaseEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPurchaseEdit(QWidget *parent = 0);
    ~FrmPurchaseEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

    void on_btnRight_clicked();

    void on_btnLeft_clicked();

private:
    void getNodeList();
    bool checkFrmEditData();
    void editData(QString editStatus, qint32 number);
    Ui::FrmPurchaseEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号

};

#endif // FRMROLEALTER_H
