#ifndef FRMMANAGER_H
#define FRMMANAGER_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class Frmmanager;
}

class Frmmanager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Frmmanager(QWidget *parent = 0);
    ~Frmmanager();

private slots:
    void onMenuAction();
    void onLockAction();
    void onPurchaseQueryAction();

    void on_tabWidget_tabCloseRequested(int index);

private:
    void initForm();
    void initToolBar();
    void systemMenuInit();
    void dayMenuInit();
    void businessQueryMenuInit();
    void businessOperationMenuInit();
    void baseMenuInit();
    QWidget *frmFactory(const QString &name);


    typedef void (Frmmanager::*actionHander)();
    Ui::Frmmanager *ui;
    QMap<QString, actionHander> m_handlerMap;
    QMap<QString, QWidget*> m_frmMap;
};

#endif // FRMMANAGER_H
