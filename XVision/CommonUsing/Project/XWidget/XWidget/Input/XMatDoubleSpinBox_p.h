﻿#ifndef XMATDOUBLESPINBOX_P_H
#define XMATDOUBLESPINBOX_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatDoubleSpinBox.h"
class XMatDoubleSpinBox;
class XMatRippleOverlay;


class XMatDoubleSpinBoxPrivate
{
    Q_DISABLE_COPY(XMatDoubleSpinBoxPrivate)
    Q_DECLARE_PUBLIC(XMatDoubleSpinBox)

public:
    XMatDoubleSpinBoxPrivate(XMatDoubleSpinBox *q);
    virtual ~XMatDoubleSpinBoxPrivate();

    void init();

    XMatDoubleSpinBox              *const q_ptr;
    XMatRippleOverlay              *rippleOverlay;
    XMatCommonDef::RippleStyle      rippleStyle;
    QColor                          rippleColor;

};

#endif // XMATDOUBLESPINBOX_P_H
