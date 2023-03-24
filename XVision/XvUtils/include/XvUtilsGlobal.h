#ifndef XVUTILSGLOBAL_H
#define XVUTILSGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XVUTILS_LIBRARY)
#  define XVUTILS_EXPORT Q_DECL_EXPORT
#else
#  define XVUTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // XVUTILSGLOBAL_H
