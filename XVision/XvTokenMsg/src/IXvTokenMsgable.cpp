#include "IXvTokenMsgable.h"
#include "XvTokenMsgMgr.h"



bool IXvTokenMsgable::registerTokenMsgAble()
{
  return XvToken->registerTokenMsgAble(this);
}

void IXvTokenMsgable::unRegisterTokenMsgAble()
{
    return XvToken->unRegisterTokenMsgAble(this);
}

QVariant IXvTokenMsgable::sendTokenMsg(const QString &reviceId, const QString &tokenCmd, QList<QVariant> &params)
{
    return  XvToken->sendTokenMsg(TokenMsg(this->tokenMsgId(),reviceId,tokenCmd),params);
}

QVariant IXvTokenMsgable::onReciveTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    return QVariant();
}
