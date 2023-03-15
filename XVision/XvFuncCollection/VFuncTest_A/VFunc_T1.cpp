#include "VFunc_T1.h"

#include <thread>
#include <chrono>

VFunc_T1::VFunc_T1(QObject *parent)
    :XvFuncBase(parent)
{
    _VFuncRole="V-T1";
    _VFuncName="算子-T1";
    _VFuncType=EXvFuncType::Other;
}

XvFuncBase::EVFucRunResult VFunc_T1::run()
{
     std::this_thread::sleep_for(std::chrono::milliseconds(66));
     return EVFucRunResult::Fail;
}

QVariant VFunc_T1::onReciveTokenMsg(const TokenMsg &tokenMsg, QList<QVariant> &params)
{
    if(tokenMsg.tokenCmd=="AAA")
    {
        qDebug()<<params.count();
        auto pQString=params[2];
         auto str=  pQString.value<QString*>();
         qDebug()<<"当前:"<<*str;
         *str="XIEYI1";
        foreach (auto var, params)
        {
            qDebug()<<var<<var.canConvert(QMetaType::Int)<<var.canConvert(QMetaType::QString);
        }
    }
    return QVariant();
}
