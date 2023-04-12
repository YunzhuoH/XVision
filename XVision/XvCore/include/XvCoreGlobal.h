#ifndef XVCOREGLOBAL_H
#define XVCOREGLOBAL_H

#include <qglobal.h>
#include <QMetaobject>
#include <QPixmap>

#if defined(XVCORE_LIBRARY)
#  define XVCORE_EXPORT Q_DECL_EXPORT
#else
#  define XVCORE_EXPORT Q_DECL_IMPORT
#endif


#endif // XVCOREGLOBAL_H
