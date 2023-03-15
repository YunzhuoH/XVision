#ifndef XMATRAISEDBUTTON_P_H
#define XMATRAISEDBUTTON_P_H

#include "XMatFlatButton_p.h"

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;
class XMatRaisedButton;

class XMatRaisedButtonPrivate : public XMatFlatButtonPrivate
{
    Q_DISABLE_COPY(XMatRaisedButtonPrivate)
    Q_DECLARE_PUBLIC(XMatRaisedButton)

public:
    XMatRaisedButtonPrivate(XMatRaisedButton *q);
    ~XMatRaisedButtonPrivate();

    void init();

    QStateMachine             *shadowStateMachine;
    QState                    *normalState;
    QState                    *pressedState;
    QGraphicsDropShadowEffect *effect;
};

#endif // XMATRAISEDBUTTON_P_H
