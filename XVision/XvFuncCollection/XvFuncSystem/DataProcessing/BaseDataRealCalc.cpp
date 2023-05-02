#include "BaseDataRealCalc.h"
#include "BaseDataRealCalcWdg.h"

using namespace XvCore;

BaseDataRealCalc::BaseDataRealCalc(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="BaseDataRealCalc";
    _funcName=getLang("XvFuncSystem_BaseDataRealCalc_Name","浮点数计算");
    _funcType=EXvFuncType::DataProcessing;

    param=new BaseDataRealCalcParam();
    result=new BaseDataRealCalcResult();

}

BaseDataRealCalc::~BaseDataRealCalc()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void BaseDataRealCalc::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new BaseDataRealCalcWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus BaseDataRealCalc::run()
{
    if(m_realCalaType==Div&&param->realParam2->value()==0)
    {
        this->setRunMsg(getLang("XvFuncSystem_BaseDataRealCalc_RunError1","被除数为0"));
        return EXvFuncRunStatus::Error;
    }
    switch (m_realCalaType) {
    case Add:
        result->realResult->setValue(param->realParam1->value()+param->realParam2->value());
        break;
    case Sub:
        result->realResult->setValue(param->realParam1->value()-param->realParam2->value());
        break;
    case Mul:
        result->realResult->setValue(param->realParam1->value()*param->realParam2->value());
        break;
    case Div:
        result->realResult->setValue(param->realParam1->value()/param->realParam2->value());
        break;

    }
    return EXvFuncRunStatus::Ok;
}


