#ifndef XMATCIRCULARPROGRESS_P_H
#define XMATCIRCULARPROGRESS_P_H

#include <QtGlobal>
#include "XMatProgressDef.h"
#include <QColor>

class XMatCircularProgress;
class XMatCircularProgressDelegate;

class XMatCircularProgressPrivate
{
    Q_DISABLE_COPY(XMatCircularProgressPrivate)
    Q_DECLARE_PUBLIC(XMatCircularProgress)

public:
    XMatCircularProgressPrivate(XMatCircularProgress *q);
    ~XMatCircularProgressPrivate();

    void init();

    XMatCircularProgress         *const q_ptr;
    XMatCircularProgressDelegate *delegate;
    ProgressType                        progressType;
    QColor                              color;
    QColor                              borderColor;
    qreal                               penWidth;
    int                                 size;
};

#endif // XMATCIRCULARPROGRESS_P_H
