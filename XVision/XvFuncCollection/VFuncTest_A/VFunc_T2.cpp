#include "VFunc_T2.h"


#include <thread>
#include <chrono>

using namespace XvCore;
VFunc_T2::VFunc_T2(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="V-T2";

    _funcType=EXvFuncType::Other;
}

EXvFuncRunStatus VFunc_T2::run()
{

    m_tokenTest="Test1";
    QList<QVariant> lst;
    lst={1,"AAA",QVariant::fromValue((QString*)&m_tokenTest)};
    sendTokenMsg(Token_RId_Broadcast,"AAA",lst);
    qDebug()<<m_tokenTest;
    std::this_thread::sleep_for(std::chrono::milliseconds(77));
    return EXvFuncRunStatus::Ok;
}


VFunc_T4::VFunc_T4(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="V-T4";
    _funcType=EXvFuncType::Other;
}

EXvFuncRunStatus VFunc_T4::run()
{

    m_tokenTest="Test1";
    QList<QVariant> lst;
    lst={1,"AAA",QVariant::fromValue((QString*)&m_tokenTest)};
    sendTokenMsg(Token_RId_Broadcast,"AAA",lst);
    qDebug()<<m_tokenTest;
    std::this_thread::sleep_for(std::chrono::milliseconds(77));
    return EXvFuncRunStatus::Ok;
}
