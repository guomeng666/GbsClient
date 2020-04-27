#ifndef FRMSUPPLIEREDIT_H
#define FRMSUPPLIEREDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmSupplierEdit;
}

class FrmSupplierEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSupplierEdit(QWidget *parent = 0);
    ~FrmSupplierEdit();
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
    Ui::FrmSupplierEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FrmSupplierEdit_H
