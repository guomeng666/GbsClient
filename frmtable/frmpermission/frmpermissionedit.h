#ifndef FRMPERMISSIONADD_H
#define FRMPERMISSIONADD_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmpermissionEdit;
}

class FrmpermissionEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmpermissionEdit(QWidget *parent = 0);
    ~FrmpermissionEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void on_btnEdit_clicked();
    void onEventShowDetail();

private:
    void editPermissionData(QString editStatus);
    bool checkFrmEditData();
    qint32 generateQueryPerssionBits();
    qint32 generateMaintainPerssionBits();
    qint32 generateRegisterPerssionBits();
    qint32 generateSamplingPerssionBits();
    qint32 generateAssayPerssionBits();
    qint32 generateSellPerssionBits();
    qint32 generateWeighPerssionBits();
    qint32 generateUnloadPerssionBits();
    qint32 generateSettlementPerssionBits();

    void setQueryPersissionCheckBox(quint32 bits);
    void setMaintainPersissionCheckBox(quint32 bits);
    void setRegisterPersissionCheckBox(quint32 bits);
    void setSamplingPersissionCheckBox(quint32 bits);
    void setAssayPersissionCheckBox(quint32 bits);
    void setSellPersissionCheckBox(quint32 bits);
    void setWeighPersissionCheckBox(quint32 bits);
    void setUnloadPersissionCheckBox(quint32 bits);
    void setSettlementPersissionCheckBox(quint32 bits);
    Ui::FrmpermissionEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    qint32 m_number;//数据在数据库中的编号
};

#endif // FRMPERMISSIONADD_H
