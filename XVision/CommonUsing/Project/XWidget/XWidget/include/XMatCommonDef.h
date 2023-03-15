#ifndef XMATCOMMONDEF_H
#define XMATCOMMONDEF_H
#include <qglobal.h>
#include <qmetaobject.h>
#include "XWidgetGlobal.h"
struct QMetaObject;
///XMat公共定义命名空间
namespace XMatCommonDef
{
 Q_NAMESPACE_EXPORT(XWIDGET_EXPORT)



///Ripple风格
enum RippleStyle
{
    CenteredRipple,
    PositionedRipple,
    NoRipple
};
Q_ENUM_NS(RippleStyle)


///Overlay风格
enum OverlayStyle
{
    NoOverlay,
    TintedOverlay,
    GrayOverlay
};
Q_ENUM_NS(OverlayStyle)



}


#endif // XMATCOMMONDEF_H
