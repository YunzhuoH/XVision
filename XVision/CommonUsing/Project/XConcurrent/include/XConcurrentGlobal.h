#ifndef XCONCURRENT_GLOBAL_H
#define XCONCURRENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XCONCURRENT_LIBRARY)
#  define XCONCURRENT_EXPORT Q_DECL_EXPORT
#else
#  define XCONCURRENT_EXPORT Q_DECL_IMPORT
#endif

typedef int XTHREAD_ID; //线程ID
typedef QString XTHREAD_GROUP;//线程组

#endif // XCONCURRENT_GLOBAL_H
