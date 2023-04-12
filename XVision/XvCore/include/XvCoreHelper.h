#ifndef XVCOREHELPER_H
#define XVCOREHELPER_H

#include "XvCoreGlobal.h"
#include <QObject>
#include "XvCoreDef.h"

///XvCore助手类
namespace XvCore
{
class XVCORE_EXPORT XvCoreHelper
{
public:
    XvCoreHelper();
public:
    static QMap<EXvFuncRunStatus,QString> getRunStatusLang();

};
}
#endif // XVCOREHELPER_H
