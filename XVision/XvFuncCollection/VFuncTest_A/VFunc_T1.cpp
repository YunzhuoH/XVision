#include "VFunc_T1.h"

#include <thread>
#include <chrono>
using namespace XvCore;
VFunc_T1::VFunc_T1(QObject *parent)
    :XvFuncBase(parent)
{
    _VFuncRole="V-T1";
    _VFuncName="算子-T1";
    _VFuncType=EXvFuncType::Other;
}

XvFuncBase::EVFucRunStatus VFunc_T1::run()
{
     std::this_thread::sleep_for(std::chrono::milliseconds(66));
     return EVFucRunStatus::Fail;
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

VFunc_T3::VFunc_T3(QObject *parent)
    :XvFuncBase(parent)
{
    _VFuncRole="V-T3";
    _VFuncName="算子-T3";
    _VFuncType=EXvFuncType::Other;
}

XvFuncBase::EVFucRunStatus VFunc_T3::run()
{
     std::this_thread::sleep_for(std::chrono::milliseconds(66));
     return EVFucRunStatus::Fail;
}
