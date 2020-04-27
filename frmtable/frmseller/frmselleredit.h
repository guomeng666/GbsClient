#ifndef FRMSELLER_H
#define FRMSELLER_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmSellerEdit;
}

class FrmSellerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSellerEdit(QWidget *parent = 0);
    ~FrmSellerEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

private:
    bool checkFrmEditData();
    void editRoleData(QString editStatus);
    void getBankTypeItem();
    Ui::FrmSellerEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMSELLER_H
