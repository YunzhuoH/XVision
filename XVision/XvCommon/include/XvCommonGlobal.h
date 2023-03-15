#ifndef XVCOMMON_GLOBAL_H
#define XVCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XVCOMMON_LIBRARY)
#  define XVCOMMON_EXPORT Q_DECL_EXPORT
#else
#  define XVCOMMON_EXPORT Q_DECL_IMPORT
#endif

#endif // XVCOMMON_GLOBAL_H
