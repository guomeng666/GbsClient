#ifndef FRMUNLOADEDIT_H
#define FRMUNLOADEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmUnloadEdit;
}

class FrmUnloadEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmUnloadEdit(QWidget *parent = 0);
    ~FrmUnloadEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

private:
    bool checkFrmEditData();
    void editData(QString editStatus);
    Ui::FrmUnloadEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMUNLOADEDIT_H
