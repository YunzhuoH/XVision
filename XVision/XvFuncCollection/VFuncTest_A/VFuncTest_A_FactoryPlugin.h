#ifndef VFUNCTEST_A_FACTORYPLUGIN_H
#define VFUNCTEST_A_FACTORYPLUGIN_H

#include "VFuncTest_A_global.h"
#include "IXvFactoryPlugin.h"

#include <QObject>

class VFUNCTEST_A_EXPORT VFuncTest_A_FactoryPlugin:public QObject, public IXvFactoryPlugin
{
    Q_OBJECT
    Q_INTERFACES(IXvFactoryPlugin)
    Q_PLUGIN_METADATA(IID XV_FACTORY_PLG)

public:
    explicit VFuncTest_A_FactoryPlugin(QObject *parent = nullptr);
    ~VFuncTest_A_FactoryPlugin(){}

    // IXvFactoryPlugin interface
public:
    QString name() const override;
    QList<QMetaObject> getPlgXVFunc() override;


};

#endif // VFUNCTEST_A_FACTORYPLUGIN_H
