#ifndef VFUNCMGR_H
#define VFUNCMGR_H

#include "XvCoreGlobal.h"
#include <QObject>
#include <QMap>
#include "IXvFactoryPlugin.h"

#define XvPlgMgr XvPluginMgr::getInstance()

///插件管理器
class XVCORE_EXPORT XvPluginMgr : public QObject
{
    Q_OBJECT
    friend class IXvFactoryPlugin;
public:
    ///获取单例
    static XvPluginMgr *getInstance();
private:
    explicit XvPluginMgr(QObject *parent = nullptr);
    static XvPluginMgr* s_Instance;

public:
    ///插件管理器初始化
    bool init();
    ///插件管理器反初始化
    bool uninit();
protected:
    bool plgRegisterXvFunc(const QMetaObject &funcMeta);
protected:
    ///插件列表
    QList<IXvFactoryPlugin*> m_lstPlg;
};

#endif // VFUNCMGR_H
