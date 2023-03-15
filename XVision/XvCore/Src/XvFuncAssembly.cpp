#include "XvFuncAssembly.h"
#include <QMutexLocker>

XvFuncAssembly::XvFuncAssembly(QObject *parent)
    : QObject{parent}
{
    m_mapXvFuncInfo.clear();
}



XvFuncAssembly *XvFuncAssembly::s_Instance = NULL;
XvFuncAssembly *XvFuncAssembly::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvFuncAssembly();
    }
  }
  return s_Instance;
}

bool XvFuncAssembly::registerXvFunc(XvFuncBase* func)
{
    if(func==nullptr) return false;
    if(m_mapXvFuncInfo.contains(func->VFuncRole()))
    {
        return false;
    }
    auto role=func->VFuncRole();
    auto type=func->VFuncType();
    auto name=func->VFuncName();
    auto icon=func->VFuncIcon();
    auto meta=*func->metaObject(); 
    S_XVFUNC_BASE_INFO info(role,type,name,icon,meta);
    m_mapXvFuncInfo.insert(role,info);
    emit sgRegisterNewXvFunc(info);
    return true;
}

XvFuncBase *XvFuncAssembly::createNewXvFunc(QString role)
{
    if(m_mapXvFuncInfo.contains(role))
    {
        auto info=m_mapXvFuncInfo[role];
        auto objVfunc= info.meta.newInstance();
        XvFuncBase* iVFunc=qobject_cast<XvFuncBase*>(objVfunc);
        return iVFunc;
    }
    else
    {
        return nullptr;
    }
}

QList<QString> XvFuncAssembly::getRoleList()
{
    return  m_mapXvFuncInfo.keys();
}
