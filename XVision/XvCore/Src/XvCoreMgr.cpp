#include "XvCoreMgr.h"
#include <QMutexLocker>

XvCoreMgr::XvCoreMgr(QObject *parent)
    : QObject{parent}
{

}



XvCoreMgr *XvCoreMgr::s_Instance = NULL;
XvCoreMgr *XvCoreMgr::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvCoreMgr();
    }
  }
  return s_Instance;
}

XvPluginMgr *XvCoreMgr::getPlgMgr() const
{
    return XvPlgMgr;
}

XvFuncAssembly *XvCoreMgr::getXvFuncAsm() const
{
    return XvFuncAsm;
}

bool XvCoreMgr::init()
{
    XvPlgMgr->init();
    return true;
}

bool XvCoreMgr::uninit()
{
    XvPlgMgr->uninit();
    return true;
}
