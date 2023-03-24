#include "XvAppCoreManager.h"
#include <QMutexLocker>
#include "XvCoreManager.h"

XvAppCoreManager::XvAppCoreManager(QObject *parent)
    : QObject{parent}
{

}



XvAppCoreManager *XvAppCoreManager::s_Instance = NULL;
XvAppCoreManager *XvAppCoreManager::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvAppCoreManager();
    }
  }
  return s_Instance;
}

void XvAppCoreManager::init()
{
    //初始化核心管理器
    XvCoreMgr->init();
}

void XvAppCoreManager::uninit()
{
    //反初始化核心管理器
    XvCoreMgr->uninit();
}
