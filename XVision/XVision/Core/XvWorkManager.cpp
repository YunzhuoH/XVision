#include "XvWorkManager.h"
//Qt
#include <QMutexLocker>

//XGraphics
#include "XGraphicsScene.h"
#include "XGraphicsItem.h"

//XVsion
#include "LangDef.h"
#include "XvViewManager.h"
#include "UiXvWorkManager.h"

//XvCore
#include "XvCoreManager.h"
#include "XvProject.h"
#include "XvFlow.h"
#include "XvFunc.h"


using namespace XvCore;

/**************************************************************/
//* [XvWorkManagerPrivate]
/**************************************************************/
class XvWorkManagerPrivate
{
    Q_DISABLE_COPY(XvWorkManagerPrivate)
    Q_DECLARE_PUBLIC(XvWorkManager)

public:
    XvWorkManagerPrivate(XvWorkManager *q):q_ptr(q)
    {

    };
    ~XvWorkManagerPrivate(){};

    XvWorkManager              *const q_ptr;

};
/**************************************************************/
//* [XvWorkManager]
/**************************************************************/
XvWorkManager::XvWorkManager(QObject *parent)
    : QObject{parent},d_ptr(new XvWorkManagerPrivate(this))
{

}

XvWorkManager::~XvWorkManager()
{

}



XvWorkManager *XvWorkManager::s_Instance = NULL;
XvWorkManager *XvWorkManager::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvWorkManager();
    }
  }
  return s_Instance;
}
/*********[初始化接口]*********/

void XvWorkManager::init()
{
    //初始化核心管理器
    XvCoreMgr->init();
    //连接槽
    connect(XvCoreMgr,&XvCore::XvCoreManager::sgUpdateXvProject,this,&XvWorkManager::onUpdateXvProject);

}

void XvWorkManager::uninit()
{
    //反初始化核心管理器
    XvCoreMgr->uninit();
}

void XvWorkManager::onInitWork()
{
    if(this->getXvProjevt()==nullptr)//创建初始项目
    {
       auto prj= this->createNewProject("Project");
       if(prj)
       {
           prj->createXvFlow(getLang(App_XvWorkMgr_XvFlowDefaultName,"流程1"));
       }
    }
}
/*********[内部工具接口]*********/


/*********[公共接口]*********/
//[核心管理器]
XvCoreManager *XvWorkManager::getXvCoreMgr() const
{
    return XvCoreMgr;
}
 //[项目]
XvCore::XvProject *XvWorkManager::getXvProjevt() const
{
    return XvCoreMgr->getXvProject();
}

XvCore::XvProject *XvWorkManager::createNewProject(const QString &name)
{
    auto project=XvCoreMgr->createNewXvProject(name);
    if(project)
    {
        return project;
    }
    else
    {
        Log_Error(QString(getLang(App_XvWorkMgr_CreateProjectError1,"创建项目%1失败")).arg(name));
        return nullptr;
    }
}
 //[流程]
XvFlow *XvWorkManager::getXvFlow(const QString &id) const
{
    auto prj=this->getXvProjevt();
    if(prj==nullptr)
    {
        return nullptr;
    }
    return prj->getXvFlow(id);
}

XvFlow *XvWorkManager::createXvFlow (const QString &name)
{
    auto prj=this->getXvProjevt();
    if(prj==nullptr)
    {
        Log_Error(getLang(App_XvWorkMgr_CreateXvFlowError1,"创建流程失败,当前无项目"));
        return nullptr;
    }
    return prj->createXvFlow(name);
}

bool XvWorkManager::removeXvFlow(const QString &id)
{
    auto prj=this->getXvProjevt();
    if(prj==nullptr)
    {
        Log_Error(getLang(App_XvWorkMgr_RemoveXvFlowError1,"删除流程失败,当前无项目"));
        return false;
    }
    auto flowsCount= prj->xvFlowCount();
    if(flowsCount==1)
    {
        Log_Warn(getLang(App_XvWorkMgr_RemoveXvFlowError2,"删除流程失败,无法删除唯一一个流程"));
        return false;
    }
    return prj->removeXvFlow(id);
}

bool XvWorkManager::onceRunXvFlow(const QString &id)
{
    auto flow=getXvFlow(id);
    if(!flow)
    {
        Log_Error(App_XvWorkMgr_XvFlowIsNull,"流程为空");
        return false;
    }

    RetXv ret=flow->runOnce();
    if(ret!=Ret_Xv_Success)
    {
        Log_Warn(getLang(App_XvWorkMgr_OnceRunXvFlowError1,"单次运行流程<%1>失败,错误码<%2>,运行信息:%3").arg(flow->flowName()).arg(ret).arg(flow->lastErrorMsg()));
        return false;
    }
    else
    {
        return true;
    }
}

bool XvWorkManager::loopRunXvFlow(const QString &id)
{
    auto flow=getXvFlow(id);
    if(!flow)
    {
        Log_Error(App_XvWorkMgr_XvFlowIsNull,"流程为空");
        return false;
    }
    RetXv ret=flow->runLoop();
    if(ret!=Ret_Xv_Success)
    {
        Log_Warn(getLang(App_XvWorkMgr_LoopRunXvFlowError1,"重复运行流程<%1>失败,错误码<%2>,运行信息:%3").arg(flow->flowName()).arg(ret).arg(flow->lastErrorMsg()));
        return false;
    }
    else
    {
        return true;
    }
}

bool XvWorkManager::stopRunXvFlow(const QString &id)
{
    auto flow=getXvFlow(id);
    if(!flow)
    {
        Log_Error(App_XvWorkMgr_XvFlowIsNull,"流程为空");
        return false;
    }
    RetXv ret=flow->stop();
    if(ret!=Ret_Xv_Success)
    {
        Log_Warn(getLang(App_XvWorkMgr_StopRunXvFlowError1,"停止运行流程失败,错误码")+QString(":%1").arg(ret));
        return false;
    }
    else
    {
        return true;
    }
}



/***********************{槽接口:项目Project-流程Flow-算子Func---<关联>---图元XItem-场景Scene-工作界面管理器UiXvWorkManager]***********************/

/*********[项目]*********/

void XvWorkManager::onUpdateXvProject(XvCore::XvProject *project)
{
    auto str=  QString("UpdateXvProject:Prj<Id-%1> Prj<Name-%2>").arg(project->projectId()).arg(project->projectName());
    Log_Trace(str);
    connect(project,&XvProject::destroyed,this,&XvWorkManager::onXvProjectDestroyed);
    connect(project,&XvProject::sgXvFlowCreated,this,&XvWorkManager::onXvFlowCreated);
    connect(project,&XvProject::sgRemoveXvFlowStart,this,&XvWorkManager::onRemoveXvFlowStart);
    connect(project,&XvProject::sgRemoveXvFlowEnd,this,&XvWorkManager::onRemoveXvFlowEnd);
}

void XvWorkManager::onXvProjectDestroyed(QObject* obj)
{
    if(!obj) return;
    auto project=qobject_cast<XvProject*>(obj);
    if(!project) return;

    disconnect(project,&XvProject::destroyed,this,&XvWorkManager::onXvProjectDestroyed);
    disconnect(project,&XvProject::sgXvFlowCreated,this,&XvWorkManager::onXvFlowCreated);
    disconnect(project,&XvProject::sgRemoveXvFlowStart,this,&XvWorkManager::onRemoveXvFlowStart);
    disconnect(project,&XvProject::sgRemoveXvFlowEnd,this,&XvWorkManager::onRemoveXvFlowEnd);

}


/*********[流程]*********/

void XvWorkManager::onXvFlowCreated(XvCore::XvFlow *flow)
{
    auto objPrj=sender();
    if(!objPrj) return;
    auto prj=qobject_cast<XvProject*>(objPrj);
    if(!prj) return;

    if(!flow)
    {
        Log_Trace("onXvFlowCreated:flow==nullptr");
        return;
    }

    auto str=  QString("XvFlowCreated:Prj<Id-%1> Prj<Name-%2> Flow<Id-%3> Flow<Name-%4>").arg(prj->projectId()).arg(prj->projectName()).arg(flow->flowId()).arg(flow->flowName());
    Log_Trace(str);

    auto flowDockMgr=XvViewMgr->uiXvWorkManager();
    if(flowDockMgr==nullptr)
    {
        Log_Error(getLang(App_XvWorkMgr_CreateXvFlowError2,"创建流程失败,当前流程界面管理器为空"));
        prj->removeXvFlow(flow->flowId());
        return;
    }
    auto scene=flowDockMgr->createFlowScene(flow);
    if(scene==nullptr)
    {
        Log_Error(getLang(App_XvWorkMgr_CreateXvFlowError3,"创建流程失败,当前流程界面为空"));
        prj->removeXvFlow(flow->flowId());
        return;
    }
    Log_Event(getLang(App_XvWorkMgr_CreateXvFlow,"创建流程")+":"+flow->flowName());

    connect(flow,&XvFlow::sgXvFuncCreated,this,&XvWorkManager::onXvFuncCreated);
    connect(flow,&XvFlow::sgRemoveXvFuncStart,this,&XvWorkManager::onRemoveXvFuncStart);
    connect(flow,&XvFlow::sgRemoveXvFuncEnd,this,&XvWorkManager::onRemoveXvFuncEnd);

}

void XvWorkManager::onRemoveXvFlowStart(XvCore::XvFlow *flow)
{
    auto objPrj=sender();
    if(!objPrj) return;
    auto prj=qobject_cast<XvProject*>(objPrj);
    if(!prj) return;
    if(!flow)
    {
        Log_Trace("onRemoveXvFlowStart:flow==nullptr");
        return;
    }

    auto str=  QString("RemoveXvFlowStart:Prj<Id-%1> Prj<Name-%2> Flow<Id-%3> Flow<Name-%4>").arg(prj->projectId()).arg(prj->projectName()).arg(flow->flowId()).arg(flow->flowName());
    Log_Trace(str);

    auto flowDockMgr=XvViewMgr->uiXvWorkManager();
    if(flowDockMgr==nullptr)
    {
        Log_Error(getLang(App_XvWorkMgr_RemoveXvFlowError3,"创删除流程失败,当前流程界面管理器为空"));
        return;
    }
    flowDockMgr->removeFlowScene(flow);
    Log_Event(getLang(App_XvWorkMgr_RemoveXvFlow,"删除流程")+":"+flow->flowName());
    disconnect(flow,&XvFlow::sgXvFuncCreated,this,&XvWorkManager::onXvFuncCreated);
    disconnect(flow,&XvFlow::sgRemoveXvFuncStart,this,&XvWorkManager::onRemoveXvFuncStart);
    disconnect(flow,&XvFlow::sgRemoveXvFuncEnd,this,&XvWorkManager::onRemoveXvFuncEnd);
}

void XvWorkManager::onRemoveXvFlowEnd(const QString &flowId)
{
    auto objPrj=sender();
    if(!objPrj) return;
    auto prj=qobject_cast<XvProject*>(objPrj);
    if(!prj) return;
    auto str=  QString("RemoveXvFlowEnd:Prj<Id-%1> Prj<Name-%2> Flow<Id-%3>").arg(prj->projectId()).arg(prj->projectName()).arg(flowId);
    Log_Trace(str);
}

/*********[算子]*********/
//xie.y todo
void XvWorkManager::onXvFuncCreated(XvCore::XvFunc *func)
{

}

void XvWorkManager::onRemoveXvFuncStart(XvCore::XvFunc *func)
{

}

void XvWorkManager::onRemoveXvFuncEnd(const QString &funcId)
{

}

