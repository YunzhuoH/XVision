#include "ElapsedTimer.h"

#include "XvFlow.h"

using namespace XvCore;

ElapsedTimer::ElapsedTimer(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="ElapsedTimer";
    _funcName=getLang("XvFuncSystem_ElapsedTimer_Name","耗时统计");
    _funcType=EXvFuncType::Other;

    result=new ElapsedTimerResult();

}

ElapsedTimer::~ElapsedTimer()
{

}

bool ElapsedTimer::addSonFunc(XvFunc *sonFunc)
{
    bool bRet=XvFunc::addSonFunc(sonFunc);
    if(bRet)
    {
        connect(sonFunc,&XvFunc::sgFuncRunEnd,this,&ElapsedTimer::onSonFuncRunEnd,Qt::DirectConnection);
    }
    return bRet;
}

bool ElapsedTimer::addFatherFunc(XvFunc *fatherFunc)
{
    bool bRet=XvFunc::addFatherFunc(fatherFunc);
    if(bRet)
    {
        connect(fatherFunc,&XvFunc::sgFuncRunStart,this,&ElapsedTimer::onFatherFuncRunStart,Qt::DirectConnection);
    }
    return bRet;
}

bool ElapsedTimer::delSonFunc(XvFunc *sonFunc)
{
    bool bRet=XvFunc::delSonFunc(sonFunc);
    if(bRet)
    {
        disconnect(sonFunc,&XvFunc::sgFuncRunEnd,this,&ElapsedTimer::onSonFuncRunEnd);
    }
    return bRet;
}

bool ElapsedTimer::delFatherFunc(XvFunc *fatherFunc)
{
    bool bRet=XvFunc::delFatherFunc(fatherFunc);
    if(bRet)
    {
        disconnect(fatherFunc,&XvFunc::sgFuncRunStart,this,&ElapsedTimer::onFatherFuncRunStart);
    }
    return bRet;
}

QList<XvFunc *> ElapsedTimer::sonFuncs() const
{
    return QList<XvFunc*>();
}

EXvFuncRunStatus ElapsedTimer::runXvFunc()
{
    return run();
}


EXvFuncRunStatus ElapsedTimer::run()
{
    result->elapsedResult->setValue(0);
    if(_lstFatherFunc.count()!=1)
    {
        setRunMsg(getLang("XvFuncSystem_ElapsedTimer_RunError1","父节点不存在或大于1"));
        return EXvFuncRunStatus::Fail;
    }

    if(_lstSonFunc.count()!=1)
    {
        setRunMsg(getLang("XvFuncSystem_ElapsedTimer_RunError2","子节点不存在或大于1"));
        return EXvFuncRunStatus::Fail;
    }

    return EXvFuncRunStatus::Running;
}

void ElapsedTimer::setParFlow(XvFlow *flow)
{
    XvFunc::setParFlow(flow);
    if(flow)
    {
        connect(flow,&XvFlow::sgFlowRunStop,this,&ElapsedTimer::onFlowWorngEnd);
    }
}

void ElapsedTimer::onFatherFuncRunStart() //将运行前提前到父算子运行前
{
    _runInfo.runIdx++;
    setRunStatus(EXvFuncRunStatus::Running);
    emit sgFuncRunStart(this);

    m_funcTimer.start();
    m_funcsElapsedTimer.start();
    result->elapsedResult->setValue(0);
}

void ElapsedTimer::onSonFuncRunEnd() //将运行后延迟到子算子运行后
{
    if(this->getXvFuncRunStatus()!=EXvFuncRunStatus::Running) //错误情况
    {
        setRunElapsed((m_funcTimer.nsecsElapsed()*1.0)/1000/1000);
        emit sgFuncRunEnd(this);//延迟到此处才发送运行结束信号
        return;
    }
    setRunElapsed((m_funcTimer.nsecsElapsed()*1.0)/1000/1000);
    double time=(m_funcsElapsedTimer.nsecsElapsed()*1.0)/1000/1000;
    result->elapsedResult->setValue(time);
    QString fatherName,sonName;
    if(_lstFatherFunc.count()>=1)
    {
        auto father=_lstFatherFunc[0];
        fatherName=father->funcName();
    }
    if(_lstSonFunc.count()>=1)
    {
        auto son=_lstSonFunc[0];
        sonName=son->funcName();
    }
    setRunMsg(QString(getLang("XvFuncSystem_ElapsedTimer_RunMsg1","算子<%1>到算子<%2>共耗时(ms)为")).arg(fatherName).arg(sonName) +QString(":%1").arg(time));
    setRunStatus(EXvFuncRunStatus::Ok);
    emit sgFuncRunEnd(this);//延迟到此处才发送运行结束信号
}

void ElapsedTimer::onFlowWorngEnd()
{
    if(this->getXvFuncRunStatus()==EXvFuncRunStatus::Running)
    {
        setRunStatus(EXvFuncRunStatus::Fail);
        onSonFuncRunEnd();
    }
}

