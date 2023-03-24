#include "XvFuncBase.h"
#include <QUuid>
#include <QElapsedTimer>
#include <QPixmap>

using namespace XvCore;


XvFuncBase::XvFuncBase(QObject *parent)
    :QObject{parent},
      _VFuncId(QUuid::createUuid().toString(QUuid::StringFormat::Id128)),
      _VFuncRole(""),
      _VFuncType(EXvFuncType::Null),
      _VFuncName(""),
      VFuncCustomName("")
{
    registerTokenMsgAble();
}

XvFuncBase::~XvFuncBase()
{
    unRegisterTokenMsgAble();
}

QPixmap XvFuncBase::VFuncIcon()
{
    return QPixmap(":/image/XvFuncIcon.svg");
}

XvFuncBase::EVFucRunStatus XvFuncBase::runVFunc()
{
    emit sgVFuncRunStart();
    QElapsedTimer timer;
    timer.start();
    VFuncRunStatus=run();
    LastRunTime= (timer.nsecsElapsed()*1.0)/1000/1000;
    emit sgVFuncRunEnd();
    return VFuncRunStatus;
}
