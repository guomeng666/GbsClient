#ifndef FRMCONTRACTEDIT_H
#define FRMCONTRACTEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmContractEdit;
}

class FrmContractEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmContractEdit(QWidget *parent = 0);
    ~FrmContractEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();

    void on_btnEdit_2_clicked();

private:
    void initForm();
    bool checkFrmEditData();
    void editRoleData(QString editStatus);
    void setGrainTypeCombox();
    void setContractTypeCombox();
    void setSupplierCombox();
    void setTransportCompanyCombox();
    void setPayTypeCombox();
    void setValuationCombox();
    void setBankTypeCombox();
    Ui::FrmContractEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMCONTRACTEDIT_H
