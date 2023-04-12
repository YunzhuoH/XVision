#include "XvTokenMsgManager.h"
#include <QMutexLocker>
#include "IXvTokenMsgAble.h"
#include <QtCore>
XvTokenMsgManager::XvTokenMsgManager(QObject *parent)
     : QObject{parent}
{

}




XvTokenMsgManager *XvTokenMsgManager::s_Instance = NULL;
XvTokenMsgManager *XvTokenMsgManager::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvTokenMsgManager();
    }
  }
  return s_Instance;
}

QMap<QString, IXvTokenMsgAble *> XvTokenMsgManager::getTokenMsgAbles() const
{
  return m_mapTokenMsgAble;
}

bool XvTokenMsgManager::registerTokenMsgAble(IXvTokenMsgAble *IXvTokenMsgAble)
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

void XvTokenMsgManager::unRegisterTokenMsgAble(IXvTokenMsgAble *IXvTokenMsgAble)
{
    if(!IXvTokenMsgAble) return;
    if(m_mapTokenMsgAble.contains(IXvTokenMsgAble->tokenMsgId()))
    {
       m_mapTokenMsgAble.remove(IXvTokenMsgAble->tokenMsgId());
    }
}

QVariant XvTokenMsgManager::sendTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    TokenMsg tm(tokenMsg);
    if(!m_mapTokenMsgAble.contains(tm.sendId))//消息体列表中不存在发送者ID，则修改为匿名ID
    {
        tm.sendId=Token_SId_Anonymity;
    }
    if(tm.reviceId!=Token_RId_Broadcast)
    {
        if(m_mapTokenMsgAble.contains(tm.reviceId))
        {
            auto revicer=m_mapTokenMsgAble[tm.reviceId];
            if(revicer!=nullptr)
            {
               return revicer->onReciveTokenMsg(tm,params);
            }
            else
            {
                m_mapTokenMsgAble.remove(tm.reviceId);
            }
        }
        return QVariant();
    }
    else
    {
        broadcastTokenMsg(tm,params);
        return QVariant();
    }
}

void XvTokenMsgManager::broadcastTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    if(tokenMsg.reviceId!=Token_RId_Broadcast)
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

