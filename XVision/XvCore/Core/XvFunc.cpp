#include "XvFunc.h"
#include <QUuid>
#include <QElapsedTimer>
#include <QPixmap>

#include "XvFuncAssembly.h"
#include "XvProject.h"
#include "XvFlow.h"

using namespace XvCore;


XvFunc::XvFunc(QObject *parent)
    :QObject{parent},
      _funcId(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
      _funcRole(""),
      _funcType(EXvFuncType::Null),
      _funcName("")
{
    registerTokenMsgAble();
}

XvFunc::~XvFunc()
{
    unRegisterTokenMsgAble();
}

void XvFunc::setFuncName(const QString &name)
{
    if(_funcName!=name)
    {
        _funcName=name;
        emit funcNameChanged(_funcName);
    }

}

QPixmap XvFunc::funcIcon()
{
    return QPixmap(":/image/XvFuncIcon.svg");
}

void XvFunc::setParFlow(XvFlow *flow)
{
    m_parFlow=flow;
}

EXvFuncRunStatus XvFunc::runXvFunc()
{
    _runInfo.runStatus=EXvFuncRunStatus::Running;//开始运行
    emit sgFuncRunStart();
    QElapsedTimer timer;
    timer.start();  
    _runInfo.runStatus=run();
    _runInfo.runElapsed= (timer.nsecsElapsed()*1.0)/1000/1000;
    emit sgFuncRunEnd();
    return _runInfo.runStatus;
}

bool XvFunc::release()
{
    if(_runInfo.runStatus==EXvFuncRunStatus::Running)
    {
        return false;
    }
    else
    {
        return true;
    }
}
