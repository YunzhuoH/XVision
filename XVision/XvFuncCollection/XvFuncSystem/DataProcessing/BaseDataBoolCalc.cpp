#include "BaseDataBoolCalc.h"
#include "BaseDataBoolCalcWdg.h"


using namespace XvCore;

BaseDataBoolCalc::BaseDataBoolCalc(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="BaseDataBoolCalc";
    _funcName=getLang("XvFuncSystem_BaseDataBoolCalc_Name","布尔计算");
    _funcType=EXvFuncType::DataProcessing;

    param=new BaseDataBoolCalcParam();
    result=new BaseDataBoolCalcResult();
}

BaseDataBoolCalc::~BaseDataBoolCalc()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void BaseDataBoolCalc::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new BaseDataBoolCalcWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus BaseDataBoolCalc::run()
{
    switch (m_boolCalaType)
    {
    case IsEqual:
        result->boolResult->setValue(param->boolParam1->value()==param->boolParam2->value());

        break;
    case IsNoEqual:
        result->boolResult->setValue(param->boolParam1->value()!=param->boolParam2->value());
        break;
    case And:
        result->boolResult->setValue(param->boolParam1->value()&&param->boolParam2->value());
        break;
    case Or:
        result->boolResult->setValue(param->boolParam1->value()||param->boolParam2->value());
        break;
    case Nand:
        result->boolResult->setValue(!(param->boolParam1->value()&&param->boolParam2->value()));
        break;
    case Nor:
        result->boolResult->setValue(!(param->boolParam1->value()||param->boolParam2->value()));
        break;
    case Xor:
        result->boolResult->setValue(param->boolParam1->value()^param->boolParam2->value());
        break;
    case Xnor:
        result->boolResult->setValue(!(param->boolParam1->value()^param->boolParam2->value()));
        break;
    }
    return EXvFuncRunStatus::Ok;
}


