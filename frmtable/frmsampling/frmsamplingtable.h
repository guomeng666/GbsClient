#ifndef FRMSAMPLINGTABLE_H
#define FRMSAMPLINGTABLE_H

#include <QWidget>
#include "frmtablebase.h"

namespace Ui {
class FrmSamplingTable;
}
class GbsSession;

class FrmSamplingTable : public QWidget, public FrmTableBase
{
    Q_OBJECT

public:
    explicit FrmSamplingTable(QWidget *parent = 0);
    ~FrmSamplingTable();

private slots:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
    void onEventShowTableData();
    void on_btnQuery_clicked();
    void on_btnRefresh_clicked();
    void on_editField_returnPressed();

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
    void queryTableData(qint32 page, qint32 perPage, const QString &field, const QString &name, \
                        const QString &startTime, const QString &endTime);

    Ui::FrmSamplingTable *ui;
    QMenu *m_tableMenu;
    QString m_fieldName;
    QString m_fieldContent;
};

#endif // FRMSAMPLINGTABLE_H
