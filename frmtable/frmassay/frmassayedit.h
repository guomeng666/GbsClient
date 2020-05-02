#ifndef FRMASSAYEDIT_H
#define FRMASSAYEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmAssayEdit;
}

class FrmAssayEdit : public QDialog
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };


public:
    explicit FrmAssayEdit(QWidget *parent = 0);
    ~FrmAssayEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

    void on_btnReturn_clicked();

private:
    void editRoleData(QString editStatus);
    void initForm();
    Ui::FrmAssayEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMASSAYEDIT_H
