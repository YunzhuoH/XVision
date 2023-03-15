#ifndef XVCORE_GLOBAL_H
#define XVCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XVCORE_LIBRARY)
#  define XVCORE_EXPORT Q_DECL_EXPORT
#else
#  define XVCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // XVCORE_GLOBAL_H
