#include "SystemXvFactoryPlugin.h"
#include "ImageAcquisition.h"
#include "BaseDataWriter.h"
#include "BaseDataBoolCalc.h"
#include "BaseDataIntCalc.h"
#include "BaseDataRealCalc.h"
#include "BaseDataStringProcess.h"

#include "Delayer.h"
#include "ElapsedTimer.h"

using namespace XvCore;
SystemXvFactoryPlugin::SystemXvFactoryPlugin(QObject *parent)
    :QObject{parent}
{

}

QString SystemXvFactoryPlugin::name() const
{
    return "SystemXvFactoryPlugin";
}

QList<QMetaObject> SystemXvFactoryPlugin::getPlgXvFunc()
{
    QList<QMetaObject> lst;
    ADD_XVFUNC(lst,ImageAcquisition);
    ADD_XVFUNC(lst,BaseDataWriter);
    ADD_XVFUNC(lst,BaseDataBoolCalc);
    ADD_XVFUNC(lst,BaseDataIntCalc);
    ADD_XVFUNC(lst,BaseDataRealCalc);
    ADD_XVFUNC(lst,BaseDataStringProcess);

    ADD_XVFUNC(lst,Delayer);
    ADD_XVFUNC(lst,ElapsedTimer);
    return lst;
}
