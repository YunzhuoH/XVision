﻿#ifndef XMATSPINBOX_P_H
#define XMATSPINBOX_P_H

#include <QtGlobal>
#include <QColor>

class XMatSpinBox;
class XMatRippleOverlay;


class XMatSpinBoxPrivate
{
    Q_DISABLE_COPY(XMatSpinBoxPrivate)
    Q_DECLARE_PUBLIC(XMatSpinBox)

public:
    XMatSpinBoxPrivate(XMatSpinBox *q);
    virtual ~XMatSpinBoxPrivate();

    void init();

    XMatSpinBox                      *const q_ptr;
    XMatRippleOverlay              *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATSPINBOX_P_H