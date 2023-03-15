#ifndef XVTOKENMSGMGR_H
#define XVTOKENMSGMGR_H

#include <QObject>
#include "XvTokenMsgGlobal.h"
#include "XvTokenMsg.h"

#include <QMap>

#define XvToken XvTokenMsgMgr::getInstance()
class IXvTokenMsgable;
class XVTOKENMSG_EXPORT XvTokenMsgMgr: public QObject
{
    Q_OBJECT
    friend class IXvTokenMsgable;
public:
    ///获取单例
    static XvTokenMsgMgr *getInstance();
public:
    QMap<QString,IXvTokenMsgable*> getTokenMsgAbles() const;
private:
    explicit XvTokenMsgMgr(QObject *parent = nullptr);
    static XvTokenMsgMgr* s_Instance;
protected:///消息体注册注销
    ///消息体注册
    bool registerTokenMsgAble(IXvTokenMsgable *IXvTokenMsgAble);
    ///消息体注销
    void unRegisterTokenMsgAble(IXvTokenMsgable *IXvTokenMsgAble);
protected:///消息传播
    ///消息发送
    QVariant sendTokenMsg(const TokenMsg& tokenMsg,QList<QVariant> &params);
    ///消息广播
    void broadcastTokenMsg(const TokenMsg& tokenMsg,QList<QVariant> &params);
protected:
    QMap<QString,IXvTokenMsgable*> m_mapTokenMsgAble;
};

#endif // XVTOKENMSGMGR_H
