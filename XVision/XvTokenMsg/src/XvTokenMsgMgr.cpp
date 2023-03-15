#include "XvTokenMsgMgr.h"
#include <QMutexLocker>
#include "IXvTokenMsgable.h"
#include <QtCore>
XvTokenMsgMgr::XvTokenMsgMgr(QObject *parent)
     : QObject{parent}
{

}




XvTokenMsgMgr *XvTokenMsgMgr::s_Instance = NULL;
XvTokenMsgMgr *XvTokenMsgMgr::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvTokenMsgMgr();
    }
  }
  return s_Instance;
}

QMap<QString, IXvTokenMsgable *> XvTokenMsgMgr::getTokenMsgAbles() const
{
  return m_mapTokenMsgAble;
}

bool XvTokenMsgMgr::registerTokenMsgAble(IXvTokenMsgable *IXvTokenMsgAble)
{
    if(!IXvTokenMsgAble) return false;
    if(IXvTokenMsgAble->tokenMsgId().isEmpty()) return false;
    if(m_mapTokenMsgAble.contains(IXvTokenMsgAble->tokenMsgId()))
    {
        return false;
    }
    else
    {
        m_mapTokenMsgAble.insert(IXvTokenMsgAble->tokenMsgId(),IXvTokenMsgAble);
        return true;
    }
}

void XvTokenMsgMgr::unRegisterTokenMsgAble(IXvTokenMsgable *IXvTokenMsgAble)
{
    if(!IXvTokenMsgAble) return;
    if(m_mapTokenMsgAble.contains(IXvTokenMsgAble->tokenMsgId()))
    {
       m_mapTokenMsgAble.remove(IXvTokenMsgAble->tokenMsgId());
    }
}

QVariant XvTokenMsgMgr::sendTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    if(tokenMsg.reviceId!=TOKEN_ID_BROADCAST)
    {
        if(m_mapTokenMsgAble.contains(tokenMsg.reviceId))
        {
            auto revicer=m_mapTokenMsgAble[tokenMsg.reviceId];
            if(revicer!=nullptr)
            {
               return revicer->onReciveTokenMsg(tokenMsg,params);
            }
            else
            {
                m_mapTokenMsgAble.remove(tokenMsg.reviceId);
            }
        }
        return QVariant();
    }
    else
    {
        broadcastTokenMsg(tokenMsg,params);
        return QVariant();
    }
}

void XvTokenMsgMgr::broadcastTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    if(tokenMsg.reviceId!=TOKEN_ID_BROADCAST)
    {
        return;
    }
    QList<QString> lstLostIToken;//失效的消息体
    foreach (auto key, m_mapTokenMsgAble.keys())
    {
        auto revicer=m_mapTokenMsgAble[key];
        if(revicer!=nullptr)
        {
            revicer->onReciveTokenMsg(tokenMsg,params);
        }
        else
        {
            lstLostIToken.append(key);//遇到失效的消息体 进行删除
        }
    }
    foreach (auto lostKey, lstLostIToken)
    {
        m_mapTokenMsgAble.remove(lostKey);//遇到失效的消息体 进行删除
    }

}

