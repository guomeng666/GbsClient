#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QWidget>

namespace Ui {
class frmlogin;
}

class frmlogin : public QWidget
{
    Q_OBJECT

public:
    explicit frmlogin(QWidget *parent = 0);
    ~frmlogin();

private:
    Ui::frmlogin *ui;
};

#endif // FRMLOGIN_H
