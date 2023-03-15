#ifndef XVTOKENMSG_H
#define XVTOKENMSG_H

#include <QString>
/// <summary>
/// Token消息
/// </summary>
typedef struct S_TOKEN_MSG
{
    S_TOKEN_MSG(const QString &_sendId,const QString &_reviceId,const QString &_tokenCmd)
        :sendId(_sendId),reviceId(_reviceId),tokenCmd(_tokenCmd)
    {

    }
    QString sendId;//发送者ID
    QString reviceId;//接收者ID
    QString tokenCmd;//命令消息
}TokenMsg,*PTokenMsg;

#define TOKEN_ID_BROADCAST "Token_Broadcast" ///广播ID

#endif // XVTOKENMSG_H
