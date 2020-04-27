#ifndef FRMPERMISSIONTABLE_H
#define FRMPERMISSIONTABLE_H

#include <QWidget>
#include "frmtablebase.h"

namespace Ui {
class FrmPermissionTable;
}

class FrmPermissionTable : public QWidget, public FrmTableBase
{
    Q_OBJECT

public:
    explicit FrmPermissionTable(QWidget *parent = 0);
    ~FrmPermissionTable();

private slots:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void on_btnAdd_clicked();
    void on_btnQuery_clicked();
    void on_btnRefresh_clicked();
    void on_editName_returnPressed();
    void onEventShowTableData();

    void onFirstBtnClicked(quint32 page);
    void onNextBtnClicked(quint32 page);
    void onPreviousBtnClicked(quint32 page);
    void onLastBtnClicked(quint32 page);
    void onAlterRow(const QStringList &row);
    void onDeleteRow(const QStringList &row);

private:
    void initForm();
    void initBtn();
    void editData(QString editStatus, const QStringList &row);
    //查询数据
    void queryTableData(qint32 page, qint32 perPage, const QString &postName, \
                        const QString &startTime, const QString &endTime);
    Ui::FrmPermissionTable *ui;
    QMenu *m_tableMenu;
    QString m_permissionName;
};

#endif // FRMPERMISSIONTABLE_H
