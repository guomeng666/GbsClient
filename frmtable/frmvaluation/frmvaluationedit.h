#ifndef FRMVALUATIONEDIT_H
#define FRMVALUATIONEDIT_H

#include <QDialog>
#include "frmtablebase.h"

namespace Ui {
class FrmValuationEdit;
}
class FrmValuationList;

class FrmValuationEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FrmValuationEdit(QWidget *parent = 0);
    ~FrmValuationEdit();
    void setEditType(const QString type);
    void setDetailData(const QStringList &detail);
    void deleteRowData(const QStringList &detail);
    void showEvent(QShowEvent *event);

private slots:
    void onEventShowDetail();
    void on_btnEdit_clicked();
    void on_btnReturn_clicked();

private:
    bool checkFrmEditData();
    void editRoleData(QString editStatus);
    void initForm();
    void showDetailRules(QByteArray &json);
    QJsonObject generateJsonObject(QList<QByteArray>& listRules);
    Ui::FrmValuationEdit *ui;
    QStringList m_detailData;
    QString m_editStatus;
    QString m_jsonData;
    qint32 m_number;//数据在数据库中的编号
    QList<QWidget*> m_listWidget;

    FrmValuationList *m_waterRule;       //水分规则窗口
    FrmValuationList *m_weightRule;      //容重规则窗口
    FrmValuationList *m_impurityRule;    //杂志规则窗口
    FrmValuationList *m_sideImpurityRule;//并肩杂规则窗口
    FrmValuationList *m_mildewRule;      //霉变规则窗口
    FrmValuationList *m_brokenRule;      //破碎规则窗口
    FrmValuationList *m_heatHarmRule;    //热损规则窗口
};

#endif // FRMVALUATIONEDIT_H
