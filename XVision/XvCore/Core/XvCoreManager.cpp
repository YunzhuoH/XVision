#include "XvCoreManager.h"
#include <QMutexLocker>
#include <QIcon>

#include "LangDef.h"

#include "XvPluginManager.h"
#include "XvFuncAssembly.h"
#include "XvProject.h"
#include "XvFlow.h"
#include "XvFunc.h"


using namespace XvCore;
/**************************************************************/
//* [XvCoreManagerPrivate]
/**************************************************************/
namespace XvCore
{
class XvCoreManagerPrivate
{
    Q_DISABLE_COPY(XvCoreManagerPrivate)
    Q_DECLARE_PUBLIC(XvCoreManager)

public:
    XvCoreManagerPrivate(XvCoreManager *q):q_ptr(q)
    {
        project=nullptr;
    };
    ~XvCoreManagerPrivate(){};

    XvCoreManager              *const q_ptr;
    XvProject                  *project;
};
}

/**************************************************************/
//* [XvCoreManager]
/**************************************************************/

XvCoreManager::XvCoreManager(QObject *parent)
    : QObject{parent},d_ptr(new XvCoreManagerPrivate(this))
{
    registerTokenMsgAble();
}

XvCoreManager::~XvCoreManager()
{
    unRegisterTokenMsgAble();
};

XvCoreManager *XvCoreManager::s_Instance = NULL;
XvCoreManager *XvCoreManager::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvCoreManager();
    }
  }
  return s_Instance;
}

XvPluginManager *XvCoreManager::getPlgMgr() const
{
    return XvPlgMgr;
}

XvFuncAssembly *XvCoreManager::getXvFuncAsm() const
{
    return XvFuncAsm;
}

bool XvCoreManager::init()
{
    XvPlgMgr->init();
    return true;
}

bool XvCoreManager::uninit()
{
    XvPlgMgr->uninit();
    Q_D(XvCoreManager);
    if(d->project)
    {
       if(d->project->release())
       {
           d->project->deleteLater();
       }
       else
       {
           delete d->project;
           d->project=nullptr;
       }
    }
    return true;
}

XvProject* XvCoreManager::getXvProject() const
{
    Q_D(const XvCoreManager);
    return d->project;
}

XvProject* XvCoreManager::createNewXvProject(const QString &name)
{
    Q_D(XvCoreManager);
    if(d->project)
    {
        if(d->project->release())
        {
            d->project->deleteLater();
        }
        else
        {
            Log_Error(getLang(Core_XvCoreMgr_CreateProjectError1,"创建项目失败,项目无法释放"),false);
            return nullptr;
        }
    }
    d->project=new XvProject(name,this);
    emit sgUpdateXvProject(d->project);
    return d->project;
}

bool XvCoreManager::loadXvProject(const QString &path)
{
    return false;
}

bool XvCoreManager::saveXvProject(const QString &path)
{
    return false;
}



