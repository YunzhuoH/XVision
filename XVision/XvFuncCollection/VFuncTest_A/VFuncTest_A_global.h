#ifndef VFUNCTEST_A_GLOBAL_H
#define VFUNCTEST_A_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VFUNCTEST_A_LIBRARY)
#  define VFUNCTEST_A_EXPORT Q_DECL_EXPORT
#else
#  define VFUNCTEST_A_EXPORT Q_DECL_IMPORT
#endif

#endif // VFUNCTEST_A_GLOBAL_H
