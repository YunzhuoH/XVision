#include "LogOutput.h"
#include "LogOutputWdg.h"
using namespace XvCore;

LogOutput::LogOutput(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="LogOutput";
    _funcName=getLang("XvFuncSystem_LogOutput_Name","日志输出");
    _funcType=EXvFuncType::Other;

    param=new LogOutputParam();
}

LogOutput::~LogOutput()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void LogOutput::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new LogOutputWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus LogOutput::run()
{
    auto type=param->outputType->value();
    if(type<XLOG_LEVEL_TRACE||type>XLOG_LEVEL_CRITICAL)
    {
        setRunMsg(getLang("XvFuncSystem_LogOutput_RunError1","日志类型错误"));
        return EXvFuncRunStatus::Fail;
    }
    auto logType=(XLogger::ELogType)type;
    XLog->log(param->outputMsg->toString(),logType);
    return EXvFuncRunStatus::Ok;
}

