#include "XvCoreManager.h"
#include <QMutexLocker>
#include <QIcon>

#include "XvPluginManager.h"
#include "XvFuncAssembly.h"

#include "LangDef.h"

using namespace XvCore;

XvCoreManager::XvCoreManager(QObject *parent)
    : QObject{parent}
{

}



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
    return true;
}
