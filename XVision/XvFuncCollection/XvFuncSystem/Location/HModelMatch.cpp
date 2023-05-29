#include "HModelMatch.h"
#include "HModelMatchWdg.h"
#include "HalconDef.h"

using namespace XvCore;

HModelMatch::HModelMatch(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="HModelMatch";
    _funcName=getLang("XvFuncSystem_HModelMatch_Name","模板匹配(H)");
    _funcType=EXvFuncType::Location;

    param=new HModelMatchParam();
    result=new HModelMatchResult();
}

HModelMatch::~HModelMatch()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void HModelMatch::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new HModelMatchWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus HModelMatch::run()
{
    HObject obj;


    return EXvFuncRunStatus::Ok;
}


