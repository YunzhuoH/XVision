#include "XvFlow.h"

#include <QUuid>
#include <QMap>
#include <QThread>

#include "XvFunc.h"
#include "XvFuncAssembly.h"
#include "XvProject.h"
#include "XvCoreManager.h"


#include "LangDef.h"

using namespace XvCore;
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

    };
    ~XvFlowPrivate(){};
    ///父指针
    XvFlow              *const q_ptr;
    ///算子字典:QString-算子id  XvFunc-算子
    QMap<QString,XvFunc*>   mapFunc;
};
}
/**************************************************************/
//* [XvFlow]
/**************************************************************/
XvFlow::XvFlow(XvProject *project,const QString &name,QObject *parent)
    : QObject{parent},m_parProject(project),
      _flowId(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
      _flowName(name),
      d_ptr(new XvFlowPrivate(this))
{
    registerTokenMsgAble();
}

XvFlow::~XvFlow()
{
    unRegisterTokenMsgAble();
}

RetXv XvFlow::release()
{
    Q_D(XvFlow);


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

void XvFlow::setParProject(XvProject *project)
{
    m_parProject=project;
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
       Log_Warn(QString(getLang(Core_XvFlow_CreateXvFuncError1,"创建算子错误，标识符[%1]无效")).arg(role));
       return func;
    }
    func->setParent(this);
    func->setParFlow(this);
    d->mapFunc.insert(func->funcId(),func);
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
          func->deleteLater();
          d->mapFunc.remove(id);
          emit this->sgRemoveXvFuncEnd(id);
          return true;
       }
       else
       {
           Log_Warn(QString(getLang(Core_XvFlow_RemoveXvFuncError1,"移除算子[%1]错误，算子无法释放")).arg(func->funcName()));
       }
    }
    else
    {
        Log_Warn(QString(getLang(Core_XvFlow_RemoveXvFuncError2,"移除算子错误，算子Id[%1]不存在")).arg(id));
    }
    return false;
}
//xie.y: todo
RetXv XvFlow::runOnce()
{
    Q_D(XvFlow);
    emit this->sgFlowRunStart();

    foreach (auto func, d->mapFunc) {

        func->runXvFunc();//xie.y
        Log_Info(QString("RunFunc_%1").arg(func->funcName()));
        QThread::msleep(500);
    }


    emit this->sgFlowRunEnd();
    return RET_XV_SUCCESS;
}

RetXv XvFlow::runLoop()
{
    return RET_XV_SUCCESS;
}

RetXv XvFlow::stop()
{
    emit this->sgFlowRunStop();
    return RET_XV_SUCCESS;
}
