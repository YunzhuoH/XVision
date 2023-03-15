#include "VFuncTest_A_FactoryPlugin.h"
#include "VFunc_T1.h"
#include "VFunc_T2.h"
#include "VTest1.h"


VFuncTest_A_FactoryPlugin::VFuncTest_A_FactoryPlugin(QObject *parent)
    :QObject{parent}
{

}

QString VFuncTest_A_FactoryPlugin::name() const
{
    return "VFuncTest";
}

QList<QMetaObject> VFuncTest_A_FactoryPlugin::getPlgXVFunc()
{
    QList<QMetaObject> lst;
    ADD_XVFUNC(lst,VFunc_T1);
    ADD_XVFUNC(lst,VFunc_T2);
    return lst;
}


