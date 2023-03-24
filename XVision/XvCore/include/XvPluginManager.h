#ifndef XVPLUGINMANAGER_H
#define XVPLUGINMANAGER_H

#include "XvCoreGlobal.h"
#include <QObject>
#include <QMap>

#define XvPlgMgr XvCore::XvPluginManager::getInstance()

namespace XvCore
{
class IXvFactoryPlugin;
///插件管理器
class XVCORE_EXPORT XvPluginManager : public QObject
{
    Q_OBJECT
    friend class IXvFactoryPlugin;
public:
    ///获取单例
    static XvPluginManager *getInstance();
private:
    explicit XvPluginManager(QObject *parent = nullptr);
    static XvPluginManager* s_Instance;

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
}
#endif // XVPLUGINMANAGER_H
