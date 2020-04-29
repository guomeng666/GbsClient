#-------------------------------------------------
#
# Project created by QtCreator 2020-04-16T18:12:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbsclient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

include ($$PWD\frmlogin\frmlogin.pri)
include ($$PWD\frmmanager\frmmanager.pri)
include ($$PWD\frmtable\frmtable.pri)
include ($$PWD\frmbusiness\frmbusiness.pri)
include ($$PWD\service\service.pri)
include ($$PWD\tools\tools.pri)
include ($$PWD\widgets\widgets.pri)

INCLUDEPATH +=  $$PWD\frmlogin\
                $$PWD\frmmanager\
                $$PWD\service\
                $$PWD\tools\
                $$PWD\widgets\
                $$PWD\frmtable\
                $$PWD\frmtable\frmdepartment\
                $$PWD\frmtable\frmpermission\
                $$PWD\frmtable\frmrole\
                $$PWD\frmtable\frmuser\
                $$PWD\frmtable\frmvehicletype\
                $$PWD\frmtable\frmvehicle\
                $$PWD\frmtable\frmwarehouse\
                $$PWD\frmtable\frmbanktype\
                $$PWD\frmtable\frmseller\
                $$PWD\frmtable\frmsupplier\
                $$PWD\frmtable\frmtransport\
                $$PWD\frmtable\frmpaymenttype\
                $$PWD\frmtable\frmpacktype\
                $$PWD\frmtable\frmgraintype\
                $$PWD\frmtable\frmsampleclass\
                $$PWD\frmtable\frmcontracttype\
                $$PWD\frmtable\frmprocedurenode\
                $$PWD\frmtable\frmpurchase\
                $$PWD\frmtable\frmvaluation\
                $$PWD\frmtable\frmcontract\
                $$PWD\frmtable\frmregister\
                $$PWD\frmbusiness\frmregister\
                $$PWD\frmbusiness\frmsampling\

INCLUDEPATH +=  $$PWD\service\base\department\
                $$PWD\service\base\permission\
                $$PWD\service\base\role\
                $$PWD\service\base\user\
                $$PWD\service\base\vehicletype\
                $$PWD\service\base\vehicle\
                $$PWD\service\base\warehouse\
                $$PWD\service\base\banktype\
                $$PWD\service\base\seller\
                $$PWD\service\base\supplier\
                $$PWD\service\base\transport\
                $$PWD\service\base\paymenttype\
                $$PWD\service\base\packtype\
                $$PWD\service\base\graintype\
                $$PWD\service\base\sampleclass\
                $$PWD\service\base\contracttype\
                $$PWD\service\base\procedurenode\
                $$PWD\service\base\purchase\
                $$PWD\service\base\valuation\
                $$PWD\service\base\contract\
                $$PWD\service\business\register\
                $$PWD\service\business\queryseller\
                $$PWD\service\business\querypicture\

SOURCES += systemconfig.cpp \
           main.cpp

HEADERS += systemconfig.h

RESOURCES += main.qrc\



