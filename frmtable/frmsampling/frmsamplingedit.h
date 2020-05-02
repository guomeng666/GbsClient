#ifndef FRMSAMPLINGEDIT_H
#define FRMSAMPLINGEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmSamplingEdit;
}

class FrmSamplingEdit : public QDialog
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };


public:
    explicit FrmSamplingEdit(QWidget *parent = 0);
    ~FrmSamplingEdit();
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
    Ui::FrmSamplingEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
    qint32 m_pictureID; // 图片索引位置
    QList<QImage> m_listImage;
    void setVehicleType();
};

#endif // FRMSAMPLINGEDIT_H
