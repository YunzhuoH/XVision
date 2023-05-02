#include "BaseDataIntCalc.h"
#include "BaseDataIntCalcWdg.h"

using namespace XvCore;

BaseDataIntCalc::BaseDataIntCalc(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="BaseDataIntCalc";
    _funcName=getLang("XvFuncSystem_BaseDataIntCalc_Name","整数计算");
    _funcType=EXvFuncType::DataProcessing;

    param=new BaseDataIntCalcParam();
    result=new BaseDataIntCalcResult();

}

BaseDataIntCalc::~BaseDataIntCalc()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void BaseDataIntCalc::onShowFunc()
{ 
    if(!m_frm)
    {
        m_frm=new BaseDataIntCalcWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus BaseDataIntCalc::run()
{
    if(m_intCalaType==Div&&param->intParam2->value()==0)
    {
        this->setRunMsg(getLang("XvFuncSystem_BaseDataIntCalc_RunError1","被除数为0"));
        return EXvFuncRunStatus::Error;
    }
    switch (m_intCalaType) {
    case Add:
        result->intResult->setValue(param->intParam1->value()+param->intParam2->value());
        break;
    case Sub:
        result->intResult->setValue(param->intParam1->value()-param->intParam2->value());
        break;
    case Mul:
        result->intResult->setValue(param->intParam1->value()*param->intParam2->value());
        break;
    case Div:
        result->intResult->setValue(param->intParam1->value()/param->intParam2->value());
        break;
    case SelfAdd:
        result->intResult->setValue(((*param->intParam1)++).value());
        break;
    case SelfSub:
        result->intResult->setValue(((*param->intParam1)--).value());
        break;

    }
    return EXvFuncRunStatus::Ok;
}



