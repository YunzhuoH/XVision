#ifndef XVDISPLAYGLOBAL_H
#define XVDISPLAYGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XVDISPLAY_LIBRARY)
#  define XVDISPLAY_EXPORT Q_DECL_EXPORT
#else
#  define XVDISPLAY_EXPORT Q_DECL_IMPORT
#endif

///自定义图元类型起始值
#define XvGraphicsItemUserType  100

#endif // XVDISPLAYGLOBAL_H
