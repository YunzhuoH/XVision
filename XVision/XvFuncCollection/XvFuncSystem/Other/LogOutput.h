#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"
#include "XLogger.h"
class LogOutputWdg;

namespace XvCore
{
class LogOutputParam:public XvBaseParam
{
public:
    LogOutputParam()
    {
        outputType=new XInt("outputType",XLOG_LEVEL_INFO,this,getLang("XvFuncSystem_LogOutput_OutputType","日志输出类型"));
        outputMsg=new XString("outputMsg","",this,getLang("XvFuncSystem_LogOutput_OutputMsg","输出消息"));
    }
public:
    XInt *outputType=nullptr;
    XString *outputMsg=nullptr;

};


class XVFUNCSYSTEM_EXPORT LogOutput:public XvFunc
{
    Q_OBJECT
    friend class LogOutputWdg;
public:
    Q_INVOKABLE explicit LogOutput(QObject *parent = nullptr);
    ~LogOutput();
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/LogOutput.svg");}
    EXvFuncRunStatus run() override;
    XvBaseParam *getParam() const override { return param;};
protected:
    LogOutputParam *param=nullptr;
    LogOutputWdg* m_frm=nullptr;

};
}


#endif // LOGOUTPUT_H
