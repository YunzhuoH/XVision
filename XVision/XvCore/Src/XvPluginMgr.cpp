#include "XvPluginMgr.h"
#include <QMutexLocker>
#include <QtGlobal>
#include <QtCore>
#include <QPluginLoader>

#include "XvFuncBase.h"
#include "XvFuncAssembly.h"
#include "LangDef.h"
#include "XLogger.h"

XvPluginMgr::XvPluginMgr(QObject *parent)
    : QObject{parent}
{

}





XvPluginMgr *XvPluginMgr::s_Instance = NULL;
XvPluginMgr *XvPluginMgr::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvPluginMgr();
    }
  }
  return s_Instance;
}

bool XvPluginMgr::init()
{
    QString dllPath=qApp->applicationDirPath()+"/XvFuncCollection";
    QDir pluginsDir(dllPath);
    for (const QString& filename : pluginsDir.entryList(QDir::Files))
    {
        QFileInfo fileinfo(filename);
        if (fileinfo.suffix() != "so" && fileinfo.suffix() != "dll" &&
            fileinfo.suffix() != "dylib")
        {
          continue;
        }
        QString path=pluginsDir.absoluteFilePath(filename);
        QPluginLoader pluginLoader(path);

        auto plugin=pluginLoader.instance();
        if(plugin && dynamic_cast<IXvFactoryPlugin*>(plugin))
        {
             IXvFactoryPlugin *vFuncplg = qobject_cast<IXvFactoryPlugin*>(plugin);
             if(vFuncplg)
             {
                QString plgName=vFuncplg->name();
                if(!vFuncplg->init())//初始化失败
                {
                    Log_Error(QString("#%1#%2").arg(plgName).arg(getLang(CORE_PLG_INITFAIL,"插件初始化失败")));
                }
                else
                {
                   m_lstPlg.append(vFuncplg);
                   QString strError="";
                   QString strEvent="";
                   auto lst=vFuncplg->getPlgXVFunc();
                   foreach (auto meta, lst)
                   {
                       bool bRet=this->plgRegisterXvFunc(meta);
                       if(!bRet)
                       {
                            strError+=QString("<%1>").arg(meta.className());
                       }
                       else
                       {
                           strEvent+=QString("<%1>").arg(meta.className());
                       }
                   }
                   if(!strError.isEmpty())
                   {
                       Log_Error(QString("%1:%2 %3").arg(plgName).arg(strError).arg(getLang(CORE_XVFUNC_REG_FAIL,"算子注册失败")));
                   }
                   if(!strEvent.isEmpty())
                   {
                      Log_Event(QString("%1:%2 %3").arg(plgName).arg(strEvent).arg(getLang(CORE_XVFUNC_REG_SUCCESS,"算子注册成功")));
                   }
                }
             }
        }
    }

    return false;
}

bool XvPluginMgr::uninit()
{
    foreach (auto plg, m_lstPlg)
    {
        plg->uninit();
    }
    return false;
}

bool XvPluginMgr::plgRegisterXvFunc(const QMetaObject &funcMeta)
{
    if(funcMeta.superClass()->className()!= XvFuncBase::staticMetaObject.className())
    {
        return false;
    }
    auto objVfunc= funcMeta.newInstance();
    XvFuncBase* iVFunc=qobject_cast<XvFuncBase*>(objVfunc);
    if(iVFunc)
    {
        bool bRet= XvFuncAsm->registerXvFunc(iVFunc);
        delete iVFunc;
        iVFunc=nullptr;
        return bRet;
    }
    else
    {
        return false;
    }
}

