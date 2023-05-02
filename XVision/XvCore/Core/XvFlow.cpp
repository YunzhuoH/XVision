#include "XvFlow.h"

//Qt
#include <QUuid>
#include <QMap>
#include <QThread>
//std
#include <queue>

//XvCore
#include "XvFunc.h"
#include "XvFuncAssembly.h"
#include "XvProject.h"
#include "XvCoreManager.h"

#include "LangDef.h"

//XConcurrent
#include "XConcurrentManager.h"

using namespace XvCore;


#define XvFlowThreadGroup "XvCore::XvFlow"
/**************************************************************/
//* [XvFlowPrivate]
/**************************************************************/
namespace XvCore
{
class XvFlowPrivate
{
    Q_DISABLE_COPY(XvFlowPrivate)
    Q_DECLARE_PUBLIC(XvFlow)

public:
    XvFlowPrivate(XvFlow *q):q_ptr(q)
    {
        runThread=nullptr;
    };
    ~XvFlowPrivate(){};
    ///父指针
    XvFlow              *const q_ptr;
    ///算子字典:QString-算子id  XvFunc-算子
    QMap<QString,XvFunc*>   mapFunc;
    ///运行线程
    XThread             *runThread;
};
}
/**************************************************************/
//* [XvFlow]
/**************************************************************/

///获取开始节点
inline static QList<XvFunc*> getFlowGraphStartFunc(QMap<QString,XvFunc*> &map)
{
    QList<XvFunc*> lst;
    foreach (auto func, map)
    {
       if(func->fatherFuncs().count()==0)
       {
           lst.append(func);
       }

    }
    return lst;
}

XvFlow::XvFlow(XvProject *project,const QString &name,QObject *parent)
    : QObject{parent},m_parProject(project),
      _flowId(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
      _flowName(name),_running(false),
      d_ptr(new XvFlowPrivate(this))
{
    registerTokenMsgAble();
}

XvFlow::~XvFlow()
{
    unRegisterTokenMsgAble();
    release();
}

RetXv XvFlow::release()
{
    Q_D(XvFlow);
    foreach (auto func, d->mapFunc)
    {
       if(func->release())
       {
           func->deleteLater();
       }
       else
       {
           delete func;
           func=nullptr;
       }
    }
    return true;
}

void XvFlow::setFlowName(const QString &name)
{
   if(name!=_flowName)
   {
       _flowName=name;
       emit sgFlowNameChanged(this);
   }
}

QString XvFlow::lastErrorMsg()
{
    QString str=_lastErrorMsg;
    _lastErrorMsg="";
    return str;
}

void XvFlow::setParProject(XvProject *project)
{
    m_parProject=project;
}

void XvFlow::setLastErrorMsg(const QString &msg)
{
    _lastErrorMsg=msg;
    Log_Trace(QString("<%1>[%2]:%3").arg(this->flowId()).arg(this->flowName()).arg(msg));
}

/**********************算子操作**********************/
XvFunc *XvFlow::getXvFunc(const QString &id)
{
    Q_D(XvFlow);
    if(d->mapFunc.contains(id))
    {
        return d->mapFunc[id];
    }
    return nullptr;

}

QList<XvFunc *> XvFlow::getXvFuncs() const
{
    Q_D(const XvFlow);
    return d->mapFunc.values();
}

int XvFlow::xvFuncCount() const
{
    Q_D(const XvFlow);
    return d->mapFunc.count();
}

XvFunc *XvFlow::createXvFunc(const QString &role)
{
    Q_D(XvFlow);
    auto func=XvCoreMgr->getXvFuncAsm()->createNewXvFunc(role);
    if(func==nullptr)
    {
       setLastErrorMsg(QString(getLang(Core_XvFlow_CreateXvFuncError1,"创建算子错误，标识符[%1]无效")).arg(role));
       return nullptr;
    }
    func->setParent(this);
    func->setParFlow(this);
    d->mapFunc.insert(func->funcId(),func);
    connect(func,&XvFunc::sgSonFuncDel,this,&XvFlow::onUpdateAllXvFuncLink);
    emit this->sgXvFuncCreated(func);
    return func;
}

bool XvFlow::removeXvFunc(const QString &id)
{
    Q_D(XvFlow);
    if(d->mapFunc.contains(id))
    {
       auto func= d->mapFunc[id];
       if(func->release())
       {
          emit this->sgRemoveXvFuncStart(func);
          disconnect(func,&XvFunc::sgSonFuncDel,this,&XvFlow::onUpdateAllXvFuncLink);
          func->deleteLater();
          d->mapFunc.remove(id);
          emit this->sgRemoveXvFuncEnd(id);
          return true;
       }
       else
       {
          setLastErrorMsg(QString(getLang(Core_XvFlow_RemoveXvFuncError1,"移除算子[%1]错误，算子无法释放")).arg(func->funcName()));
       }
    }
    else
    {
        setLastErrorMsg(QString(getLang(Core_XvFlow_RemoveXvFuncError2,"移除算子错误，算子Id[%1]不存在")).arg(id));
    }
    return false;
}

void XvFlow::onUpdateAllXvFuncLink()
{
    Q_D(XvFlow);
    QElapsedTimer timer;
    timer.start();
    foreach (auto func, d->mapFunc)
    {
        func->onXvFlowLinkRefresh();
    }
}
//xie.y: todo
RetXv XvFlow::runOnce()
{
    Q_D(XvFlow);
    if(isRunning())//检查是否在运行
    {
        return Ret_Xv_FlowRunning;
    }
    if(!checkFlowLegal())//验证流程合法性
    {
        return Ret_Xv_FlowIllegal;
    }
    d->runThread = XConcurrentMgr->getThreadsByGropuName(XvFlowThreadGroup,"FlowRunOnce_"+this->flowName());
    if(!d->runThread)
    {
       d->runThread=XConcurrentMgr->createThreadByFunction(XvFlowThreadGroup,"FlowRunOnce_"+this->flowName(),false,true,&XvFlow::_threadRun,this,false);
    }
    if(d->runThread)
    {
        d->runThread->start(QThread::HighPriority);
    }

    return Ret_Xv_Success;
}

RetXv XvFlow::runLoop()
{
    Q_D(XvFlow);
    if(isRunning())//检查是否在运行
    {
        return Ret_Xv_FlowRunning;
    }
    if(!checkFlowLegal())//验证流程合法性
    {
        return Ret_Xv_FlowIllegal;
    }
    d->runThread= XConcurrentMgr->getThreadsByGropuName(XvFlowThreadGroup,"FlowRunLoop_"+this->flowName());
    if(!d->runThread)
    {
       d->runThread=XConcurrentMgr->createThreadByFunction(XvFlowThreadGroup,"FlowRunLoop_"+this->flowName(),false,true,&XvFlow::_threadRun,this,true);
    }
    if(d->runThread)
    {
        d->runThread->start(QThread::HighPriority);
    }

    return Ret_Xv_Success;
}

RetXv XvFlow::stop()
{
    if(isRunning())
    {
        _running=false;
        emit this->sgFlowRunStop();
        return Ret_Xv_Success;
    }
    else
    {
        return Ret_Xv_FlowNoRun;
    }
}

RetXv XvFlow::wait(unsigned long ms)
{
    Q_D(XvFlow);
    if(!isRunning())
    {
        return Ret_Xv_FlowNoRun;
    }
    if(!d->runThread)
    {
        return Ret_Xv_FlowNoRun;
    }
    bool bRet= d->runThread->wait(ms);
    if(!bRet)
    {
        return Ret_Xv_FlowWaitTimeOut;
    }
    return Ret_Xv_Success;
}

//xie.y todo 检查流程合法性
bool XvFlow::checkFlowLegal()
{
    Q_D(XvFlow);
    auto lstStart=getFlowGraphStartFunc(d->mapFunc);
    if(lstStart.count()!=1)
    {
        setLastErrorMsg(getLang(Core_XvFlow_FlowLegalError1,"流程合法性错误，起始节点(无父节点)数量不等于1"));
        return false;
    }
    return true;
}

//xie.y todo  后续需要优化流程运行(将从图像获取修改为找到流程树根节点)
void XvFlow::_threadRun(bool bLoop)
{
    Q_D(XvFlow);
    _running=true;   
    do
    {
        QElapsedTimer timer;
        timer.start();
        _runInfo.runIdx++;
        _runInfo.runStatus=EXvFlowRunStatus::Running;
        _runInfo.runMsg=getLang(Core_XvFlow_RunStatusRunning,"正在运行");
        emit this->sgFlowRunStart();
        //流程开始运行
    {
        //xie.y 后续需要优化运行流程


            auto lstStart=getFlowGraphStartFunc(d->mapFunc);
            XvFunc* startFunc=lstStart.at(0);
            if(startFunc)
            {
                 std::queue<XvFunc*> q;
                 q.push(startFunc);
                 QList<XvFunc*> lstVisited;
                 while(!q.empty())
                 {
                     if(!_running)
                     {
                        break;
                     }

                     int n = q.size();
                     for (int i = 0; i < n; ++i)
                     {
                       auto curFunc= q.front();
                       q.pop();
                       if(!lstVisited.contains(curFunc))
                       {
                          if(!_running)
                          {
                             break;
                          }

                          lstVisited.append(curFunc);
                          curFunc->runXvFunc();
                          auto sonFuncs= curFunc->sonFuncs();
                          foreach (auto sonFunc, sonFuncs)
                          {
                              if(!lstVisited.contains(sonFunc))
                              {
                                   q.push(sonFunc);
                              }

                          }
                       }
                     }
                 }


            }
            else
            {
                _running=false;
            }


     }
        _runInfo.runElapsed= (timer.nsecsElapsed()*1.0)/1000/1000;
        _runInfo.runStatus=EXvFlowRunStatus::Ok;
        _runInfo.runMsg=getLang(Core_XvFlow_RunStatusOk,"运行成功");
        emit this->sgFlowRunEnd();
        if(!_running)
        {
           break;
        }
        QThread::msleep(10);
    }while(bLoop);
    _running=false;
}
