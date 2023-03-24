#ifndef XVDATAGLOBAL_H
#define XVDATAGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XVDATA_LIBRARY)
#  define XVDATA_EXPORT Q_DECL_EXPORT
#else
#  define XVDATA_EXPORT Q_DECL_IMPORT
#endif

#endif // XVDATAGLOBAL_H
