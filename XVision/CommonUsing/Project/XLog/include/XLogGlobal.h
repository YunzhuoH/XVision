#ifndef XLOG_GLOBAL_H
#define XLOG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XLOG_LIBRARY)
#  define XLOG_EXPORT Q_DECL_EXPORT
#else
#  define XLOG_EXPORT Q_DECL_IMPORT
#endif

#endif // XLOG_GLOBAL_H
