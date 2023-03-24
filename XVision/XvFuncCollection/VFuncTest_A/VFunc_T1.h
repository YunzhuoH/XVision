#ifndef VFUNC_T1_H
#define VFUNC_T1_H


#include "VFuncTest_A_global.h"
#include "XVFuncBase.h"
namespace XvCore
{

class VFUNCTEST_A_EXPORT VFunc_T1:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFunc_T1(QObject *parent = nullptr);

    // IVFuncBase interface
protected:
    EVFucRunStatus run() override;

    // IXVTokenMsgable interface
protected:
    QVariant onReciveTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params) override;
};

class VFUNCTEST_A_EXPORT VFunc_T3:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFunc_T3(QObject *parent = nullptr);

    // IVFuncBase interface
protected:
    EVFucRunStatus run() override;

    // IXVTokenMsgable interface

};
}
#endif // VFUNC_T1_H
