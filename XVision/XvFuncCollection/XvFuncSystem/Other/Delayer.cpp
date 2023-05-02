#include "Delayer.h"
#include "DelayerWdg.h"
#include <QThread>

using namespace XvCore;

Delayer::Delayer(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="Delayer";
    _funcName=getLang("XvFuncSystem_Delayer_Name","延迟器");
    _funcType=EXvFuncType::Other;

    param=new DelayerParam();
}

Delayer::~Delayer()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void Delayer::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new DelayerWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus Delayer::run()
{
    auto ms=param->dealyMs->value();
    if(ms<=0)
    {
        setRunMsg(getLang("XvFuncSystem_Delayer_RunError1","延迟时间小于或者等于0"));
        return EXvFuncRunStatus::Fail;
    }
    QThread::msleep(ms);
    return EXvFuncRunStatus::Ok;
}

