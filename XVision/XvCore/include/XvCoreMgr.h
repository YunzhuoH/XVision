#ifndef XVCOREMGR_H
#define XVCOREMGR_H

#include <QObject>
#include "XvPluginMgr.h"
#include "XvFuncAssembly.h"

#define XvCore XvCoreMgr::getInstance()
class XVCORE_EXPORT XvCoreMgr : public QObject
{
    Q_OBJECT
public:
    ///获取单例
    static XvCoreMgr *getInstance();
private:
    explicit XvCoreMgr(QObject *parent = nullptr);
    static XvCoreMgr* s_Instance;
public:
    ///初始化
    bool init();
    ///反初始化
    bool uninit();
public:
    XvPluginMgr* getPlgMgr() const;
    XvFuncAssembly* getXvFuncAsm() const;

};

#endif // XVCOREMGR_H
