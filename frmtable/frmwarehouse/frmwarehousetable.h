#ifndef FRMWAREHOUSETABLE_H
#define FRMWAREHOUSETABLE_H

#include <QWidget>
#include "frmtablebase.h"

namespace Ui {
class FrmWareHouseTable;
}
class GbsSession;

class FrmWareHouseTable : public QWidget, public FrmTableBase
{
    Q_OBJECT

public:
    explicit FrmWareHouseTable(QWidget *parent = 0);
    ~FrmWareHouseTable();

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
    void queryTableData(qint32 page, qint32 perPage, const QString &warehouseName, \
                        const QString &startTime, const QString &endTime);

    Ui::FrmWareHouseTable *ui;
    QMenu *m_tableMenu;
    QString m_warehouseName;
};

#endif // FRMWAREHOUSETABLE_H
