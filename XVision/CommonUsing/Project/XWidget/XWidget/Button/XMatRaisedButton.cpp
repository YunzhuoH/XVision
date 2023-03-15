#include "XMatRaisedButton.h"
#include "XMatRaisedButton_p.h"
#include <QStateMachine>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEventTransition>
#include "XMatStyleDef.h"
/*!
 *  \class XMatRaisedButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatRaisedButtonPrivate::XMatRaisedButtonPrivate(XMatRaisedButton *q)
    : XMatFlatButtonPrivate(q)
{
    backgroundColor=C_XMatThemeColor;
    foregroundColor=QColor(255,255,255,255);
    rippleColor=QColor(255,255,255,255);
    overlayColor=C_XMatOverlaydColor;
    disabledForegroundColor=C_XMatDisableForegroundColor;
    disabledBackgroundColor=C_XMatDisableBackgroundColor;
}

/*!
 *  \internal
 */
XMatRaisedButtonPrivate::~XMatRaisedButtonPrivate()
{
}

/*!
 *  \internal
 */
void XMatRaisedButtonPrivate::init()
{
    Q_Q(XMatRaisedButton);

    shadowStateMachine = new QStateMachine(q);
    normalState        = new QState;
    pressedState       = new QState;
    effect             = new QGraphicsDropShadowEffect;

    effect->setBlurRadius(10);
    effect->setOffset(QPointF(0, 2));
    effect->setColor(QColor(0, 0, 0, 75));

    q->setBackgroundMode(Qt::OpaqueMode);
    q->setMinimumHeight(16);
    q->setGraphicsEffect(effect);
    q->setBaseOpacity(0.3);

    shadowStateMachine->addState(normalState);
    shadowStateMachine->addState(pressedState);

    normalState->assignProperty(effect, "offset", QPointF(0, 2));
    normalState->assignProperty(effect, "blurRadius", 10);

    pressedState->assignProperty(effect, "offset", QPointF(0, 5));
    pressedState->assignProperty(effect, "blurRadius", 50);

    QAbstractTransition *transition;

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(normalState);
    pressedState->addTransition(transition);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(effect, "offset", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "blurRadius", q);
    animation->setDuration(100);
    shadowStateMachine->addDefaultAnimation(animation);

    shadowStateMachine->setInitialState(normalState);
    shadowStateMachine->start();

}

/*!
 *  \class XMatRaisedButton
 */

XMatRaisedButton::XMatRaisedButton(QWidget *parent)
    : XMatFlatButton(*new XMatRaisedButtonPrivate(this), parent)
{
    d_func()->init();
    setText("RaisedButton");
    resize(80,26);
}

XMatRaisedButton::XMatRaisedButton(const QString &text, QWidget *parent)
    : XMatFlatButton(*new XMatRaisedButtonPrivate(this), parent)
{
    d_func()->init();

    setText(text);
}

XMatRaisedButton::~XMatRaisedButton()
{
}

XMatRaisedButton::XMatRaisedButton(XMatRaisedButtonPrivate &d, QWidget *parent)
    : XMatFlatButton(d, parent)
{
    d_func()->init();
}

bool XMatRaisedButton::event(QEvent *event)
{
    Q_D(XMatRaisedButton);

    if (QEvent::EnabledChange == event->type()) {
        if (isEnabled()) {
            d->shadowStateMachine->start();
            d->effect->setEnabled(true);
        } else {
            d->shadowStateMachine->stop();
            d->effect->setEnabled(false);
        }
    }
    return XMatFlatButton::event(event);
}
