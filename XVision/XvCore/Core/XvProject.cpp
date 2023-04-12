#include "XvProject.h"

#include <QUuid>
#include <QMap>

#include "XvFlow.h"

#include "LangDef.h"

using namespace XvCore;
/**************************************************************/
//* [XvProjectPrivate]
/**************************************************************/
namespace XvCore
{
class XvProjectPrivate
{
    Q_DISABLE_COPY(XvProjectPrivate)
    Q_DECLARE_PUBLIC(XvProject)

public:
    XvProjectPrivate(XvProject *q):q_ptr(q)
    {

    };
    ~XvProjectPrivate(){};
    ///父指针
    XvProject              *const q_ptr;
    ///流程字典
    QMap<QString,XvFlow*>   mapFlow;
};
}
/**************************************************************/
//* [XvProject]
/**************************************************************/

XvProject::XvProject(const QString &name,QObject *parent)
    : QObject{parent},
      _projectId(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
      _projectName(name),
      d_ptr(new XvProjectPrivate(this))
{
    registerTokenMsgAble();
}

XvProject::~XvProject()
{
    unRegisterTokenMsgAble();
}

RetXv XvProject::release()
{
    return false;
}



/**********************流程操作**********************/

XvFlow *XvProject::getXvFlow(const QString &id)
{
    Q_D(XvProject);
    if(d->mapFlow.contains(id))
    {
        return d->mapFlow[id];
    }
    else
    {
        return nullptr;
    }
}

QList<XvFlow *> XvProject::getXvFlows(const QString &name) const
{
    Q_D(const XvProject);
    QList<XvFlow*> lstFlow;
    foreach (auto flow, d->mapFlow)
    {
        if(flow->flowName()==name)
        {
            lstFlow.append(flow);
        }
    }
    return lstFlow;
}

QList<XvFlow *> XvProject::getXvFlows() const
{
    Q_D(const XvProject);
    QList<XvFlow*> lstFlow;
    foreach (auto flow, d->mapFlow)
    {
        lstFlow.append(flow);
    }
    return lstFlow;
}

int XvProject::xvFlowCount() const
{
    Q_D(const XvProject);
    return d->mapFlow.count();
}

XvFlow *XvProject::createXvFlow(const QString &name)
{
    Q_D(XvProject);
    XvFlow* flow=new XvFlow(this,name,this);
    d->mapFlow.insert(flow->flowId(),flow);
    emit this->sgXvFlowCreated(flow);
    return flow;
}

bool XvProject::removeXvFlow(const QString &id)
{
    Q_D(XvProject);
    if(d->mapFlow.contains(id))
    {
       auto flow= d->mapFlow[id];
       if(flow->release())
       {
          emit this->sgRemoveXvFlowStart(flow);
          flow->deleteLater();
          d->mapFlow.remove(id);
          emit this->sgRemoveXvFlowEnd(id);
          return true;
       }
       else
       {
           Log_Warn(QString(getLang(Core_XvProject_RemoveXvFuncError1,"移除流程[%1]错误，流程无法释放")).arg(flow->flowName()));
       }
    }
    else
    {
        Log_Warn(QString(getLang(Core_XvProject_RemoveXvFuncError2,"移除流程错误，流程Id[%1]不存在")).arg(id));
    }
    return false;
}

int XvProject::removeXvFlows(const QString &name)
{
    Q_D(XvProject);
    int nRemoveCount=0;
    QList<QString> lstRemoveId;
    foreach (auto flow, d->mapFlow)
    {
        if(flow->flowName()==name)
        {
            lstRemoveId.append(flow->flowId());
        }
    }
    foreach (auto id, lstRemoveId)
    {
        bool bRet=removeXvFlow(id);
        if(bRet)
        {
            nRemoveCount++;
        }
    }
    return nRemoveCount;
}



void XvProject::setProjectName(const QString &name)
{
    if(name!=_projectName)
    {
        _projectName=name;
        emit projectNameChanged(name);
    }
}
