#ifndef XVUTILS_H
#define XVUTILS_H

#include "XvUtilsGlobal.h"

#include <QString>

namespace XvUtils
{
    ///通过路径获取stylesheet样式表
    XVUTILS_EXPORT QString getStyleByPath(const QString &path);
}


#endif // XVUTILS_H
