#ifndef FRMGRAINTYPEEDIT_H
#define FRMGRAINTYPEEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmGrainTypeEdit;
}

class FrmGrainTypeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmGrainTypeEdit(QWidget *parent = 0);
    ~FrmGrainTypeEdit();
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
    Ui::FrmGrainTypeEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMGRAINTYPEEDIT_H
