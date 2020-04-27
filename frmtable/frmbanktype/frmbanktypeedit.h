#ifndef FRMBANKTYPEEDIT_H
#define FRMBANKTYPEEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmBankTypeEdit;
}

class FrmBankTypeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmBankTypeEdit(QWidget *parent = 0);
    ~FrmBankTypeEdit();
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
    Ui::FrmBankTypeEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMBANKTYPEEDIT_H
