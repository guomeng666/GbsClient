#ifndef FRMVEHICLETYPEEDIT_H
#define FRMVEHICLETYPEEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmVehicleTypeEdit;
}

class FrmVehicleTypeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmVehicleTypeEdit(QWidget *parent = 0);
    ~FrmVehicleTypeEdit();
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
    Ui::FrmVehicleTypeEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMVEHICLETYPEEDIT_H
