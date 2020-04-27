#ifndef FRMSAMPLECLASSEDIT_H
#define FRMSAMPLECLASSEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmSampleClassEdit;
}

class FrmSampleClassEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSampleClassEdit(QWidget *parent = 0);
    ~FrmSampleClassEdit();
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
    Ui::FrmSampleClassEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMSAMPLECLASSEDIT_H
