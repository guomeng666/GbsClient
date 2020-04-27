#ifndef FRMPAYMENTTYPEEDIT_H
#define FRMPAYMENTTYPEEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmPaymenttypeEdit;
}

class FrmPaymenttypeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmPaymenttypeEdit(QWidget *parent = 0);
    ~FrmPaymenttypeEdit();
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
    Ui::FrmPaymenttypeEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FrmPaymenttypeEdit_H
