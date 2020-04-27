#ifndef FRMROLEALTER_H
#define FRMROLEALTER_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmRoleEdit;
}

class FrmRoleEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmRoleEdit(QWidget *parent = 0);
    ~FrmRoleEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

private:
    void getPermissionSelectItem(); //获取权限选择项
    bool checkFrmEditData();
    void editRoleData(QString editStatus, qint32 number);
    Ui::FrmRoleEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMROLEALTER_H
