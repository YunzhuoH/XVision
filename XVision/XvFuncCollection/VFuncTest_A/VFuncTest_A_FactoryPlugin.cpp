#include "VFuncTest_A_FactoryPlugin.h"
#include "VFunc_T1.h"
#include "VFunc_T2.h"
#include "VTest1.h"
#include "XvFuncTest.h"

using namespace XvCore;
VFuncTest_A_FactoryPlugin::VFuncTest_A_FactoryPlugin(QObject *parent)
    :QObject{parent}
{

}

QString VFuncTest_A_FactoryPlugin::name() const
{
    return "VFuncTest";
}

QList<QMetaObject> VFuncTest_A_FactoryPlugin::getPlgXvFunc()
{
    QList<QMetaObject> lst;
    ADD_XVFUNC(lst,VFunc_T1);
    ADD_XVFUNC(lst,VFunc_T2);   
    ADD_XVFUNC(lst,VFunc_T3);
    ADD_XVFUNC(lst,VFunc_T4);

    ADD_XVFUNC(lst,VFuncA);
    ADD_XVFUNC(lst,VFuncB);
    ADD_XVFUNC(lst,VFuncC);
    ADD_XVFUNC(lst,VFuncC1);
    ADD_XVFUNC(lst,VFuncC2);
    ADD_XVFUNC(lst,VFuncX);
    ADD_XVFUNC(lst,VFuncY);
    ADD_XVFUNC(lst,VFuncZ);
    ADD_XVFUNC(lst,VFuncU);
    ADD_XVFUNC(lst,VFuncV);
    ADD_XVFUNC(lst,VFuncW);

    ADD_XVFUNC(lst,VFuncQ1);
    ADD_XVFUNC(lst,VFuncQ2);
    ADD_XVFUNC(lst,VFuncQ3);
    ADD_XVFUNC(lst,VFuncQ4);
    ADD_XVFUNC(lst,VFuncQ5);
    ADD_XVFUNC(lst,VFuncQ6);
    ADD_XVFUNC(lst,VFuncQ7);
    ADD_XVFUNC(lst,VFuncQ8);
    ADD_XVFUNC(lst,VFuncQ9);
    ADD_XVFUNC(lst,VFuncQA);
    ADD_XVFUNC(lst,VFuncQB);

    ADD_XVFUNC(lst,VFuncW1);
    ADD_XVFUNC(lst,VFuncW2);
    ADD_XVFUNC(lst,VFuncW3);
    ADD_XVFUNC(lst,VFuncW4);





    return lst;
}


