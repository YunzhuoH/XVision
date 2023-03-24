#ifndef XVCOREMANAGER_H
#define XVCOREMANAGER_H

#include "XvCoreGlobal.h"
#include <QObject>

#define XvCoreMgr XvCore::XvCoreManager::getInstance()

namespace XvCore
{
class XvPluginManager;
class XvFuncAssembly;

class XVCORE_EXPORT XvCoreManager : public QObject
{
    Q_OBJECT
public:
    ///获取单例
    static XvCoreManager *getInstance();
private:
    explicit XvCoreManager(QObject *parent = nullptr);
    static XvCoreManager* s_Instance;
public:
    ///初始化
    bool init();
    ///反初始化
    bool uninit();


public:
    XvPluginManager* getPlgMgr() const;
    XvFuncAssembly* getXvFuncAsm() const;

};
}
#endif // XVCOREMANAGER_H
