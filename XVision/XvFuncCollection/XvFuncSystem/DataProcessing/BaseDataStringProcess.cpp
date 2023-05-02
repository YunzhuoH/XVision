#include "BaseDataStringProcess.h"
#include "BaseDataStringProcessWdg.h"


using namespace XvCore;

BaseDataStringProcess::BaseDataStringProcess(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="BaseDataStringProcess";
    _funcName=getLang("XvFuncSystem_BaseDataStringProcess_Name","字符串处理");
    _funcType=EXvFuncType::DataProcessing;

    param=new BaseDataStringProcessParam();
    result=new BaseDataStringProcessResult();
}

BaseDataStringProcess::~BaseDataStringProcess()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void BaseDataStringProcess::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new BaseDataStringProcessWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus BaseDataStringProcess::run()
{
    resetResult();

    auto pS1=param->stringParam1;
    auto pS2=param->stringParam2;
    auto pI1=param->intParam1;
    auto pI2=param->intParam2;
    auto pB=param->boolParam;
    auto pR=param->realParam;

    auto rb=result->boolResult;
    auto ri=result->intResult;
    auto rr=result->realResult;
    auto rs=result->stringResult;

    switch (m_stringProcessType)
    {
    case EStringProcessType::IsEqual:
    {
        auto bRet= (pS1->value()==pS2->value());
        rb->setValue(bRet);
    }
        break;
    case EStringProcessType::IsNoEqual:
    {
        auto bRet= (pS1->value()!=pS2->value());
        rb->setValue(bRet);
    }
        break;
    case EStringProcessType::Contain:
    {
        auto bRet=pS1->value().contains(pS2->value());
        rb->setValue(bRet);
    }
        break;
    case EStringProcessType::Add:
    {
        rs->setValue(pS1->value()+pS2->value());
    }
        break;
    case EStringProcessType::Left:
    {
        rs->setValue(pS1->value().left(pI1->value()));
    }
        break;
    case EStringProcessType::Mid:
    {
        rs->setValue(pS1->value().mid(pI1->value(),pI2->value()));
    }
        break;
    case EStringProcessType::Right:
    {
        rs->setValue(pS1->value().right(pI1->value()));
    }
        break;
    case EStringProcessType::Length:
    {
        ri->setValue(pS1->value().length());
    }
        break;
    case EStringProcessType::ToLower:
    {
        rs->setValue(pS1->value().toLower());
    }
        break;
    case EStringProcessType::ToUpper:
    {
        rs->setValue(pS1->value().toUpper());
    }
        break;
    case EStringProcessType::TryToBool:
    {
        auto strBool=pS1->value().toLower();
        if(strBool=="false")
        {
            rb->setValue(false);
        }
        else if(strBool=="true")
        {
            rb->setValue(true);
        }
        else
        {
            bool bRet=false;
            int nVal=strBool.toInt(&bRet);
            if(bRet)
            {
                rb->setValue(nVal);
            }
            else
            {
                this->setRunMsg(getLang("XvFuncSystem_BaseDataStringProcess_RunError1","无法将字符串解析为布尔量"));
                return EXvFuncRunStatus::Fail;
            }
        }
    }
        break;
    case EStringProcessType::TryToInt:
    {
        bool bRet=false;
        int nVal=pS1->value().toInt(&bRet);
        if(bRet)
        {
            ri->setValue(nVal);
        }
        else
        {
            this->setRunMsg(getLang("XvFuncSystem_BaseDataStringProcess_RunError2","无法将字符串解析为整数"));
            return EXvFuncRunStatus::Fail;
        }
    }
        break;
    case EStringProcessType::TryToReal:
    {
        bool bRet=false;
        double rVal=pS1->value().toDouble(&bRet);
        if(bRet)
        {
            rr->setValue(rVal);
        }
        else
        {
            this->setRunMsg(getLang("XvFuncSystem_BaseDataStringProcess_RunError3","无法将字符串解析为浮点数"));
            return EXvFuncRunStatus::Fail;
        }
    }
        break;
    case EStringProcessType::BoolToString:
    {
        rs->setValue(pB->toString());
    }
        break;
    case EStringProcessType::IntToString:
    {
        rs->setValue(pI1->toString());
    }
        break;
    case EStringProcessType::RealToString:
    {
        rs->setValue(pR->toString());
    }
        break;
    }
    return EXvFuncRunStatus::Ok;
}

void BaseDataStringProcess::resetResult()
{
    if(result)
    {
        result->boolResult->setValue(false);
        result->intResult->setValue(0);
        result->realResult->setValue(0);
        result->stringResult->setValue("");
    }
}


