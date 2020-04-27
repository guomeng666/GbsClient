#include "gbssession.h"
#include <assert.h>

GbsSession::GbsSession(QObject *parent) :
    QObject(parent),
    m_errno(0)
{
    m_errMap[errNetWork] = "网络通讯错误";
    m_errMap[errDataExist] = "添加的数据已经存在";
    m_errMap[errDataNoExist] = "修改的数据不存在";
    m_errMap[errSelectItem] = "修改的数据选择项已经被删除了";
    m_errMap[errNoExist] = "没有查到数据";
}

void GbsSession::addRequestData(QString key, QString value)
{
    m_dataMap[key] = value;
}

bool GbsSession::sendDataToServer(QByteArray &data)
{
    qDebug()<<"发送请求数据";
    Q_ASSERT(m_rawData.isEmpty());
    m_rawData =  httpService.sendJsonData(data,m_errStr);
    if(m_rawData.isEmpty()){
        return false;
    }
    return true;
}

QString GbsSession::getCmd()
{
    Q_ASSERT(m_dataMap.find("Cmd")!=m_dataMap.end());
    return m_dataMap.value("Cmd");
}

const QString GbsSession::getRequestData(const QString &k) const
{
    return m_dataMap.value(k);
}

quint32 GbsSession::getCloumSize()
{
    if(m_row.isEmpty())
        return 0;
    else
        return m_row.at(0).size();
}

QString GbsSession::getLastErrString()
{
    return getErrString(m_errno);
}

//根据错误码返回错误原因
const QString GbsSession::getErrString(int errNo)
{
    QString errStr = m_errMap.value(errNo);
    if(errStr.isEmpty())
        return "未定义错误";
    else
        return errStr;
}
