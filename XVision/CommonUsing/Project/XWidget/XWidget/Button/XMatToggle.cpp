#include "XMatToggle.h"
#include "XMatToggle_p.h"
#include <QtWidgets/QApplication>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "XMatToggle_internal.h"
#include "XMatStyleDef.h"

/*!
 *  \class XMatTogglePrivate
 *  \internal
 */

XMatTogglePrivate::XMatTogglePrivate(XMatToggle *q)
    : q_ptr(q)
{
    disabledColor=C_XMatDisableForegroundColor;
    activeColor=C_XMatThemeColor;
    inactiveColor=QColor(Qt::white);
    trackColor=QColor(150,150,150);
}

XMatTogglePrivate::~XMatTogglePrivate()
{
}

void XMatTogglePrivate::init()
{
    Q_Q(XMatToggle);

    track          = new XMatToggleTrack(q);
    thumb          = new XMatToggleThumb(q);
    rippleOverlay  = new XMatToggleRippleOverlay(thumb, track, q);
    stateMachine   = new QStateMachine(q);
    offState       = new QState;
    onState        = new QState;
    orientation    = Qt::Horizontal;


    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    setupProperties();

    stateMachine->start();
    QCoreApplication::processEvents();
}

void XMatTogglePrivate::setupProperties()
{
    Q_Q(XMatToggle);

    if (q->isEnabled()) {
        const qreal shift = thumb->shift();
        if (qFuzzyCompare(shift, 1)) {
            thumb->setThumbColor(q->activeColor());
            track->setTrackColor(q->activeColor().lighter(110));
        } else if (qFuzzyCompare(1+shift, 1)) {
            thumb->setThumbColor(q->inactiveColor());
            track->setTrackColor(q->trackColor());
        }
    }

    offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
    onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
    onState->assignProperty(thumb, "thumbColor", q->activeColor());

    q->update();
}

/*!
 *  \class XMatToggle
 */

XMatToggle::XMatToggle(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new XMatTogglePrivate(this))
{
    d_func()->init();
}

XMatToggle::~XMatToggle()
{
}


void XMatToggle::setDisabledColor(const QColor &color)
{
    Q_D(XMatToggle);
    d->disabledColor = color;
    d->setupProperties();
}

QColor XMatToggle::disabledColor() const
{
    Q_D(const XMatToggle);

    return d->disabledColor;
}

void XMatToggle::setActiveColor(const QColor &color)
{
    Q_D(XMatToggle);
    d->activeColor = color;
    d->setupProperties();
}

QColor XMatToggle::activeColor() const
{
    Q_D(const XMatToggle);

    return d->activeColor;
}

void XMatToggle::setInactiveColor(const QColor &color)
{
    Q_D(XMatToggle);
    d->inactiveColor = color;
    d->setupProperties();
}

QColor XMatToggle::inactiveColor() const
{
    Q_D(const XMatToggle);

    return d->inactiveColor;
}

void XMatToggle::setTrackColor(const QColor &color)
{
    Q_D(XMatToggle);

    d->trackColor = color;
    d->setupProperties();
}

QColor XMatToggle::trackColor() const
{
    Q_D(const XMatToggle);

    return d->trackColor;
}

void XMatToggle::setOrientation(Qt::Orientation orientation)
{
    Q_D(XMatToggle);

    if (d->orientation == orientation) {
        return;
    }

    d->orientation = orientation;
    updateGeometry();
}

Qt::Orientation XMatToggle::orientation() const
{
    Q_D(const XMatToggle);

    return d->orientation;
}

QSize XMatToggle::sizeHint() const
{
    Q_D(const XMatToggle);

    return Qt::Horizontal == d->orientation
        ? QSize(64, 36)
        : QSize(36, 64);
}

bool XMatToggle::event(QEvent *event)
{
    Q_D(XMatToggle);

    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

void XMatToggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}
