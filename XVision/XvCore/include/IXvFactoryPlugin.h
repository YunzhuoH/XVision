#ifndef IXVFACTORYBASEPLUGIN_H
#define IXVFACTORYBASEPLUGIN_H

#include "XvCoreGlobal.h"
#include <QObject>
#include <QList>

namespace XvCore
{

///工厂生成插件
class XVCORE_EXPORT  IXvFactoryPlugin
{
public:
    IXvFactoryPlugin();
    //析构函数
   virtual ~IXvFactoryPlugin() {}
public:
    ///插件名称(dll名称)
    virtual QString name()const=0;
    ///初始化
    virtual bool init() {return true;}
    ///反初始化
    virtual bool uninit(){return true;}
    ///获取插件算子
    virtual QList<QMetaObject> getPlgXVFunc()=0;
    #define ADD_XVFUNC(lst,cls) lst.append(cls::staticMetaObject)

};

}

#define XV_FACTORY_PLG "Xv.Factory.PlgSys"
Q_DECLARE_INTERFACE(XvCore::IXvFactoryPlugin, XV_FACTORY_PLG);

#endif // IXVFACTORYBASEPLUGIN_H
