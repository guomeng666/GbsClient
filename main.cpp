#include "frmlogin.h"
#include "frmmanager.h"
#include "frmregister.h"
#include "frmregisteredit.h"
#include "gbsimagewidget.h"
#include "gbstoolfunctions.h"
#include "frmsampling.h"
#include "frmsell.h"
#include "frmassay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Frmmanager w;
    w.show();

    return a.exec();
}
