#ifndef SYSTEMXVFACTORYPLUGIN_H
#define SYSTEMXVFACTORYPLUGIN_H

#include "XVFuncSystemGlobal.h"
#include "IXvFactoryPlugin.h"

namespace XvCore
{
class XVFUNCSYSTEM_EXPORT SystemXvFactoryPlugin:public QObject, public IXvFactoryPlugin
{
    Q_OBJECT
    Q_INTERFACES(XvCore::IXvFactoryPlugin)
    Q_PLUGIN_METADATA(IID XV_FACTORY_PLG)

public:
    explicit SystemXvFactoryPlugin(QObject *parent = nullptr);
    ~SystemXvFactoryPlugin(){}

    // IXvFactoryPlugin interface
public:
    QString name() const override;
    QList<QMetaObject> getPlgXvFunc() override;

};
}

#endif // SYSTEMXVFACTORYPLUGIN_H
