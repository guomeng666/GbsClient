#ifndef FRMREGISTEREDIT_H
#define FRMREGISTEREDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmRegisterEdit;
}

class FrmRegisterEdit : public QDialog
{
    Q_OBJECT
    enum PurchaseType
    {
      Scattered,
      Contarct
    };


public:
    explicit FrmRegisterEdit(QWidget *parent = 0);
    ~FrmRegisterEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

private:
    void editRoleData(QString editStatus);

    Ui::FrmRegisterEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
    qint32 m_pictureID; // 图片索引位置
    QList<QImage> m_listImage;
    void setVehicleType();
    void setGrainType();
    void setPackType();
    void setPayMentType();
    void setBankType();
    void setPurchaseType();
    bool checkFrmEditData(PurchaseType type);
};

#endif // FrmRegisterEdit_H
