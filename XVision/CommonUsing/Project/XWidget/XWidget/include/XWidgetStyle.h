#ifndef XWIDGETSTYLEDEF_H
#define XWIDGETSTYLEDEF_H

#include "XWidgetGlobal.h"
#include <QString>
class XWIDGET_EXPORT XWidgetStyle
{
public:
    ///初始化控件库风格
    static void initStyle();
    ///获取控件库风格
    static QString getStyle();
};

#endif // XWIDGETSTYLEDEF_H
