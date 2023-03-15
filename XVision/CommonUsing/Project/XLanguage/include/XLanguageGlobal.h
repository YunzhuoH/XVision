#ifndef XLANGUAGEGLOBAL_H
#define XLANGUAGEGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XLANGUAGE_LIBRARY)
#  define XLANGUAGE_EXPORT Q_DECL_EXPORT
#else
#  define XLANGUAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // XLANGUAGEGLOBAL_H
