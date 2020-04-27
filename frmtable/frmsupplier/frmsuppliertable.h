#ifndef FRMSUPPLIERTABLE_H
#define FRMSUPPLIERTABLE_H

#include <QWidget>
#include "frmtablebase.h"

namespace Ui {
class FrmSupplierTable;
}
class GbsSession;

class FrmSupplierTable : public QWidget, public FrmTableBase
{
    Q_OBJECT

public:
    explicit FrmSupplierTable(QWidget *parent = 0);
    ~FrmSupplierTable();

private slots:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
    void on_btnAdd_clicked();
    void onEventShowTableData();
    void on_btnQuery_clicked();
    void on_btnRefresh_clicked();
    void on_editName_returnPressed();

    void onFirstBtnClicked(quint32 page);
    void onNextBtnClicked(quint32 page);
    void onPreviousBtnClicked(quint32 page);
    void onLastBtnClicked(quint32 page);
    void onAlterRow(const QStringList &row);
    void onDeleteRow(const QStringList &row);

private:
    void showEvent(QShowEvent *event);
    void initForm();
    void editData(QString editStatus, const QStringList &rowData);
    //查询数据
    void queryTableData(qint32 page, qint32 perPage, const QString &supplierName, \
                        const QString &startTime, const QString &endTime);

    Ui::FrmSupplierTable *ui;
    QMenu *m_tableMenu;
    QString m_warehouseName;
};

#endif // FRMSUPPLIERTABLE_H
