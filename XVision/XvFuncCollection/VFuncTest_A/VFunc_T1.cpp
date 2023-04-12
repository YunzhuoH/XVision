#include "VFunc_T1.h"

#include <thread>
#include <chrono>
using namespace XvCore;
VFunc_T1::VFunc_T1(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="V-T1";
    _funcName="算子-T1";
    _funcType=EXvFuncType::Other;
}

EXvFuncRunStatus VFunc_T1::run()
{
     std::this_thread::sleep_for(std::chrono::milliseconds(66));
     return EXvFuncRunStatus::Fail;
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
    qDebug()<<tokenMsg.tokenCmd<<tokenMsg.reviceId<<tokenMsg.sendId;
    return QVariant();
}

VFunc_T3::VFunc_T3(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="V-T3";
    _funcName="算子-T3";
    _funcType=EXvFuncType::Other;
}
EXvFuncRunStatus VFunc_T3::run()
{
     std::this_thread::sleep_for(std::chrono::milliseconds(66));
     return EXvFuncRunStatus::Fail;
}
