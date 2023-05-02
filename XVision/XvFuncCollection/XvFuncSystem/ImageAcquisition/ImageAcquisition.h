#ifndef IMAGEACQUISITION_H
#define IMAGEACQUISITION_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"


namespace XvCore
{
class XVFUNCSYSTEM_EXPORT ImageAcquisition:public XvFunc
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ImageAcquisition(QObject *parent = nullptr);
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/ImageAcquisition.svg");}
    EXvFuncRunStatus run() override;
};
}

#endif // IMAGEACQUISITION_H
