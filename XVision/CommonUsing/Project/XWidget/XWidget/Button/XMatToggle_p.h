#ifndef XMATTOGGLE_P_H
#define XMATTOGGLE_P_H

#include <Qt>
#include <QColor>

class QStateMachine;
class QState;
class XMatToggle;
class XMatToggleTrack;
class XMatToggleThumb;
class XMatToggleRippleOverlay;

class XMatTogglePrivate
{
    Q_DISABLE_COPY(XMatTogglePrivate)
    Q_DECLARE_PUBLIC(XMatToggle)

public:
    XMatTogglePrivate(XMatToggle *q);
    ~XMatTogglePrivate();

    void init();
    void setupProperties();

    XMatToggle              *const q_ptr;
    XMatToggleTrack         *track;
    XMatToggleThumb         *thumb;
    XMatToggleRippleOverlay *rippleOverlay;
    QStateMachine                 *stateMachine;
    QState                        *offState;
    QState                        *onState;
    Qt::Orientation                orientation;
    QColor                         disabledColor;
    QColor                         activeColor;
    QColor                         inactiveColor;
    QColor                         trackColor;
};

#endif // XMATTOGGLE_P_H
