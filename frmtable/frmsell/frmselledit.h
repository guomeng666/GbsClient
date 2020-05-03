#ifndef FRMSELL_H
#define FRMSELL_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmSellEdit;
}

class FrmSellEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSellEdit(QWidget *parent = 0);
    ~FrmSellEdit();
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
    Ui::FrmSellEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMSELL_H
