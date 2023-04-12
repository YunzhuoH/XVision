#ifndef IXVTOKENMSGABLE_H
#define IXVTOKENMSGABLE_H

#include "XvTokenMsgGlobal.h"
#include "XvTokenMsg.h"

#include <QObject>
#include <QVariant>
///消息体
class XvTokenMsgManager;
class  XVTOKENMSG_EXPORT IXvTokenMsgAble
{
    friend class XvTokenMsgManager;
public:
    ///消息体Id
    virtual QString tokenMsgId(){ return QString(); }
protected:///消息注册注销
   ///消息体注册
   bool registerTokenMsgAble();
   ///消息体注销
   void unRegisterTokenMsgAble();

protected:///消息传播

   ///消息发送
   virtual QVariant sendTokenMsg(const QString& reviceId,const QString& tokenCmd,QList<QVariant> &params);
   ///消息接收
   virtual QVariant onReciveTokenMsg(const TokenMsg& tokenMsg,QList<QVariant> &params);

};


#endif // IXVTOKENMSGABLE_H
