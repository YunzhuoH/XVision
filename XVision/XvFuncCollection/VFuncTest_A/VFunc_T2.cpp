#include "VFunc_T2.h"


#include <thread>
#include <chrono>

using namespace XvCore;
VFunc_T2::VFunc_T2(QObject *parent)
    :XvFuncBase(parent)
{
    _VFuncRole="V-T2";
    setVFuncName("算子-T2");
    _VFuncType=EXvFuncType::Other;
}

XvFuncBase::EVFucRunStatus VFunc_T2::run()
{

    m_tokenTest="Test1";
    QList<QVariant> lst;
    lst={1,"AAA",QVariant::fromValue((QString*)&m_tokenTest)};
    sendTokenMsg(TOKEN_ID_BROADCAST,"AAA",lst);
    qDebug()<<m_tokenTest;
    std::this_thread::sleep_for(std::chrono::milliseconds(77));
    return EVFucRunStatus::OK;
}


VFunc_T4::VFunc_T4(QObject *parent)
    :XvFuncBase(parent)
{
    _VFuncRole="V-T4";
    setVFuncName("算子-T4");
    _VFuncType=EXvFuncType::Other;
}

XvFuncBase::EVFucRunStatus VFunc_T4::run()
{

    m_tokenTest="Test1";
    QList<QVariant> lst;
    lst={1,"AAA",QVariant::fromValue((QString*)&m_tokenTest)};
    sendTokenMsg(TOKEN_ID_BROADCAST,"AAA",lst);
    qDebug()<<m_tokenTest;
    std::this_thread::sleep_for(std::chrono::milliseconds(77));
    return EVFucRunStatus::OK;
}
