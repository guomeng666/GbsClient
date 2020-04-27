#ifndef FRMTABLEBASE_H
#define FRMTABLEBASE_H

#include <QObject>
#include "servicemanager.h"
#include "gbssession.h"
#include "singleton.h"
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QMenu>
#include <QDebug>

class GbsSession;

class FrmTableBase
{
public:
    FrmTableBase();

protected:
    bool m_firstShow;
    qint32 m_curPage;//当前显示的页数
    qint32 m_totalPage;//数据总页数
    qint32 m_total;//数据总条数
    qint32 m_perPage; //一页显示多少条数据
    QString m_startTime;
    QString m_endTime;
};

#endif // FRMTABLEBASE_H
