#ifndef ELAPSEDTIMER_H
#define ELAPSEDTIMER_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"
#include <QElapsedTimer>

namespace XvCore
{

class ElapsedTimerResult:public XvBaseResult
{
public:
    ElapsedTimerResult()
    {
        elapsedResult=new XReal("elapsedResult",0,this,getLang("XvFuncSystem_ElapsedTimer_ElapsedResult","耗时(ms)"));
    }
public:
    XReal *elapsedResult=nullptr;

};

class XVFUNCSYSTEM_EXPORT ElapsedTimer:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ElapsedTimer(QObject *parent = nullptr);
    ~ElapsedTimer();

public:
    bool addSonFunc(XvFunc *sonFunc) override;
    bool addFatherFunc(XvFunc *fatherFunc) override;
    bool delSonFunc(XvFunc *sonFunc) override;
    bool delFatherFunc(XvFunc *fatherFunc) override;
    QList<XvFunc *> sonFuncs() const override;
    bool release() override { return true;}
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/ElapsedTimer.svg");}
    EXvFuncRunStatus runXvFunc() override;
    EXvFuncRunStatus run() override;
    XvBaseResult *getResult() const override { return result;};
    void setParFlow(XvFlow *flow) override;
protected slots:
    ///父节点开始运行,进行计时
    void onFatherFuncRunStart();
    ///子节点开始运行，进行计时
    void onSonFuncRunEnd();
    ///流程异常结束事件
    void onFlowWorngEnd();
protected:
    ElapsedTimerResult *result=nullptr;
    QElapsedTimer m_funcsElapsedTimer;
    QElapsedTimer m_funcTimer;



};

}



#endif // ELAPSEDTIMER_H
