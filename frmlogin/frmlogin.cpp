#include "frmlogin.h"
#include "ui_frmlogin.h"

frmlogin::frmlogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmlogin)
{
    ui->setupUi(this);
}

frmlogin::~frmlogin()
{
    delete ui;
}
