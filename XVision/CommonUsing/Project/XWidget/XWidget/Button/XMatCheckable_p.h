#ifndef XMATCHECKABLE_P_H
#define XMATCHECKABLE_P_H

#include <QtGlobal>
#include "XMatCheckable.h"

class QStateMachine;
class QState;
class QSignalTransition;
class XMatRippleOverlay;
class XMatCheckableIcon;

class XMatCheckablePrivate
{
    Q_DISABLE_COPY(XMatCheckablePrivate)
    Q_DECLARE_PUBLIC(XMatCheckable)

public:
    XMatCheckablePrivate(XMatCheckable *q);
    virtual ~XMatCheckablePrivate();

    void init();

    XMatCheckable                *const q_ptr;
    XMatRippleOverlay            *rippleOverlay;
    XMatCheckableIcon            *checkedIcon;
    XMatCheckableIcon            *uncheckedIcon;
    QStateMachine                      *stateMachine;
    QState                             *uncheckedState;
    QState                             *checkedState;
    QState                             *disabledUncheckedState;
    QState                             *disabledCheckedState;
    QSignalTransition                  *uncheckedTransition;
    QSignalTransition                  *checkedTransition;
    XMatCheckable::LabelPosition        labelPosition;
    QColor                              checkedColor;
    QColor                              uncheckedColor;
    QColor                              textColor;
    QColor                              disabledColor;
};

#endif // XMATCHECKABLE_P_H
