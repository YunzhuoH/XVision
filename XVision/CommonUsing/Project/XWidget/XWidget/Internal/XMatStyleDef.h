#ifndef XMATSTYLEDEF_H
#define XMATSTYLEDEF_H
#include <QColor>
#include <QFont>

/*************颜色*************/
///主题颜色
const QColor C_XMatThemeColor=QColor(50,130,250,200);
///涟漪颜色
const QColor C_XMatRippleColor=QColor(50,100,250,200);

///使能颜色(前景) (灰色-250透明度)
const QColor C_XMatForegroundColor=QColor(40,40,40,250);
///使能颜色(背景) (白-200透明度)
const QColor C_XMatBackgroundColor=QColor(255,255,255,200);

///失能颜色(前景) (黑-半透明)
const QColor C_XMatDisableForegroundColor=QColor(0,0,0,66);
///失能颜色(背景) (白-225透明度)
const QColor C_XMatDisableBackgroundColor=QColor(224,224,224,225);
///覆盖颜色(白色)
const QColor C_XMatOverlaydColor=QColor(255,255,255,255);
///字体颜色
const QColor C_XMatFontdColor=QColor(40,40,40,255);

/*************字体*************/
const QFont C_XMatFont=QFont("Microsoft YaHei UI", 9, QFont::Normal);

#endif // XMATSTYLEDEF_H
