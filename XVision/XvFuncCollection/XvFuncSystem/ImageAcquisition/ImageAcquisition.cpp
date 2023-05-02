#include "ImageAcquisition.h"
#include "XLogger.h"
#include <QThread>
using namespace XvCore;

ImageAcquisition::ImageAcquisition(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="ImageAcquisition";
    _funcName=getLang("XvFuncSystem_ImageAcquisition_Name","图像采集");
    _funcType=EXvFuncType::ImageAcquisition;
}

EXvFuncRunStatus ImageAcquisition::run()
{
    QThread::msleep(500);
    Log_Info(this->funcName()+" ImageAcquisition::run");
    return EXvFuncRunStatus::Ok;
}
