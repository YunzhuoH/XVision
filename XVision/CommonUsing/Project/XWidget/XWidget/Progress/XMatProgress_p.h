#ifndef XMATPROGRESS_P_H
#define XMATPROGRESS_P_H

#include <QtGlobal>
#include <QColor>

#include "XMatProgressDef.h"

class XMatProgress;
class XMatProgressDelegate;

class XMatProgressPrivate
{
    Q_DISABLE_COPY(XMatProgressPrivate)
    Q_DECLARE_PUBLIC(XMatProgress)

public:
    XMatProgressPrivate(XMatProgress *q);
    ~XMatProgressPrivate();

    void init();

    XMatProgress         *const q_ptr;
    XMatProgressDelegate *delegate;
    ProgressType                progressType;
    QColor                      progressColor;
    QColor                      backgroundColor;
    QColor                      disabledColor;
};

#endif // XMATPROGRESS_P_H
