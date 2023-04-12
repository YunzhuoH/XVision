#include "IXvTokenMsgAble.h"
#include "XvTokenMsgManager.h"



bool IXvTokenMsgAble::registerTokenMsgAble()
{
  return XvTokenMsgMgr->registerTokenMsgAble(this);
}

void IXvTokenMsgAble::unRegisterTokenMsgAble()
{
    return XvTokenMsgMgr->unRegisterTokenMsgAble(this);
}

QVariant IXvTokenMsgAble::sendTokenMsg(const QString &reviceId, const QString &tokenCmd, QList<QVariant> &params)
{
    return  XvTokenMsgMgr->sendTokenMsg(TokenMsg(this->tokenMsgId(),reviceId,tokenCmd),params);
}

QVariant IXvTokenMsgAble::onReciveTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    return QVariant();
}
