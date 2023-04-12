#ifndef XVTOKENMSGMANAGER_H
#define XVTOKENMSGMANAGER_H

#include <QObject>
#include "XvTokenMsgGlobal.h"
#include "XvTokenMsg.h"

#include <QMap>

#define XvTokenMsgMgr XvTokenMsgManager::getInstance()
class IXvTokenMsgAble;
class XVTOKENMSG_EXPORT XvTokenMsgManager: public QObject
{
    Q_OBJECT
    friend class IXvTokenMsgAble;
public:
    ///获取单例
    static XvTokenMsgManager *getInstance();
public:
    QMap<QString,IXvTokenMsgAble*> getTokenMsgAbles() const;
private:
    explicit XvTokenMsgManager(QObject *parent = nullptr);
    static XvTokenMsgManager* s_Instance;
protected:///消息体注册注销
    ///消息体注册
    bool registerTokenMsgAble(IXvTokenMsgAble *IXvTokenMsgAble);
    ///消息体注销
    void unRegisterTokenMsgAble(IXvTokenMsgAble *IXvTokenMsgAble);
public:///消息传播
    ///消息发送
    QVariant sendTokenMsg(const TokenMsg& tokenMsg,QList<QVariant> &params);
 protected:
    ///消息广播
    void broadcastTokenMsg(const TokenMsg& tokenMsg,QList<QVariant> &params);
protected:
    QMap<QString,IXvTokenMsgAble*> m_mapTokenMsgAble;
};

#endif // XVTOKENMSGMANAGER_H
