#include "XMatCheckable.h"
#include "XMatCheckable_p.h"
#include <QPainter>
#include <QEvent>
#include <QStateMachine>
#include <QSignalTransition>
#include <QEventTransition>
#include <QColor>
#include <QCoreApplication>
#include "XMatRippleOverlay.h"
#include "XMatRipple.h"
#include "XMatCheckable_internal.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatCheckablePrivate
 *  \internal
 */

XMatCheckablePrivate::XMatCheckablePrivate(XMatCheckable *q)
    : q_ptr(q)
{
}

XMatCheckablePrivate::~XMatCheckablePrivate()
{
}

void XMatCheckablePrivate::init()
{
    Q_Q(XMatCheckable);

    rippleOverlay          = new XMatRippleOverlay;
    checkedIcon            = new XMatCheckableIcon(QIcon(), q);
    uncheckedIcon          = new XMatCheckableIcon(QIcon(), q);
    stateMachine           = new QStateMachine(q);
    uncheckedState         = new QState;
    checkedState           = new QState;
    disabledUncheckedState = new QState;
    disabledCheckedState   = new QState;
    uncheckedTransition    = new QSignalTransition(q, SIGNAL(toggled(bool)));
    checkedTransition      = new QSignalTransition(q, SIGNAL(toggled(bool)));
    labelPosition          = XMatCheckable::LabelPositionRight;

    rippleOverlay->setParent(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    q->setCheckable(true);

    q->setFont(C_XMatFont);

    stateMachine->addState(uncheckedState);
    stateMachine->addState(checkedState);
    stateMachine->addState(disabledUncheckedState);
    stateMachine->addState(disabledCheckedState);
    stateMachine->setInitialState(uncheckedState);

    // Transition to checked

    uncheckedTransition->setTargetState(checkedState);
    uncheckedState->addTransition(uncheckedTransition);

    // Transition to unchecked

    checkedTransition->setTargetState(uncheckedState);
    checkedState->addTransition(checkedTransition);

    QAbstractTransition *transition;

    // Transitions enabled <==> disabled

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledUncheckedState);
    uncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(uncheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(disabledCheckedState);
    checkedState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::EnabledChange);
    transition->setTargetState(checkedState);
    disabledCheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledCheckedState);
    disabledUncheckedState->addTransition(transition);

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(disabledUncheckedState);
    disabledCheckedState->addTransition(transition);

    //

    checkedState->assignProperty(checkedIcon, "opacity", 1);
    checkedState->assignProperty(uncheckedIcon, "opacity", 0);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    disabledCheckedState->assignProperty(checkedIcon, "opacity", 1);
    disabledCheckedState->assignProperty(uncheckedIcon, "opacity", 0);

    disabledUncheckedState->assignProperty(checkedIcon, "opacity", 0);
    disabledUncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    checkedState->assignProperty(checkedIcon, "color", q->checkedColor());
    checkedState->assignProperty(uncheckedIcon, "color", q->checkedColor());

    uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());
    uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());

    disabledUncheckedState->assignProperty(uncheckedIcon, "color", q->disabledColor());
    disabledCheckedState->assignProperty(checkedIcon, "color", q->disabledColor());

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class XMatCheckable
 */

XMatCheckable::XMatCheckable(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new XMatCheckablePrivate(this))
{
    d_func()->init();
}

XMatCheckable::~XMatCheckable()
{
}

void XMatCheckable::setLabelPosition(XMatCheckable::LabelPosition placement)
{
    Q_D(XMatCheckable);

    d->labelPosition = placement;
    update();
}

XMatCheckable::LabelPosition XMatCheckable::labelPosition() const
{
    Q_D(const XMatCheckable);

    return d->labelPosition;
}


void XMatCheckable::setCheckedColor(const QColor &color)
{
    Q_D(XMatCheckable);

    d->checkedColor = color;

    setupProperties();
}

QColor XMatCheckable::checkedColor() const
{
   Q_D(const XMatCheckable);

     return d->checkedColor;
}

void XMatCheckable::setUncheckedColor(const QColor &color)
{
     Q_D(XMatCheckable);
    d->uncheckedColor = color;

    setupProperties();
}

QColor XMatCheckable::uncheckedColor() const
{
    Q_D(const XMatCheckable);
    return d->uncheckedColor;
}

void XMatCheckable::setTextColor(const QColor &color)
{
     Q_D(XMatCheckable);
    d->textColor = color;
    setupProperties();
}

QColor XMatCheckable::textColor() const
{
    Q_D(const XMatCheckable);
    return d->textColor;
}

void XMatCheckable::setDisabledColor(const QColor &color)
{
      Q_D(XMatCheckable);
    d->disabledColor = color;

    setupProperties();
}

QColor XMatCheckable::disabledColor() const
{
    Q_D(const XMatCheckable);
    return d->disabledColor;
}

void XMatCheckable::setCheckedIcon(const QIcon &icon)
{
    Q_D(XMatCheckable);
    d->checkedIcon->setIcon(icon);
    update();
}

QIcon XMatCheckable::checkedIcon() const
{
    Q_D(const XMatCheckable);
    return d->checkedIcon->icon();
}

void XMatCheckable::setUncheckedIcon(const QIcon &icon)
{
    Q_D(XMatCheckable);  
    d->uncheckedIcon->setIcon(icon);
    update();
}

QIcon XMatCheckable::uncheckedIcon() const
{
    Q_D(const XMatCheckable);
    return d->uncheckedIcon->icon();
}

/*!
 *  \reimp
 */
QSize XMatCheckable::sizeHint() const
{
    if (text().isEmpty()) {
        return QSize(30, 30);
    }
    return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width()+40, 30);
}

XMatCheckable::XMatCheckable(XMatCheckablePrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool XMatCheckable::event(QEvent *event)
{
    Q_D(XMatCheckable);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move:
        d->checkedIcon->setGeometry(rect());
        d->uncheckedIcon->setGeometry(rect());
        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
        break;
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    default:
        break;
    }
    return QAbstractButton::event(event);
}

/*!
 *  \reimp
 */
bool XMatCheckable::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(XMatCheckable);

        d->rippleOverlay->setGeometry(geometry().adjusted(-8, -8, 8, 8));
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void XMatCheckable::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatCheckable);

    if (!isEnabled()) {
        return;
    }
    int y=height()/2+8;//8:checkable中心偏移
    XMatRipple *ripple;
    if (XMatCheckable::LabelPositionRight == d->labelPosition) {

         ripple = new XMatRipple(QPoint(20,y));
    } else {
         ripple = new XMatRipple(QPoint(width()-4,y));
    }
    ripple->setRadiusEndValue(22);
    ripple->setColor(isChecked() ? checkedColor() : uncheckedColor());
    if (isChecked()) {
        ripple->setOpacityStartValue(1);
    }
    d->rippleOverlay->addRipple(ripple);

    setChecked(!isChecked());
}

/*!
 *  \reimp
 */
void XMatCheckable::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatCheckable);

    QPainter painter(this);

    QPen pen;
    pen.setColor(isEnabled() ? textColor() : disabledColor());
    painter.setPen(pen);
    int y=height()/2+4;
    if (XMatCheckable::LabelPositionLeft == d->labelPosition) {
        painter.drawText(4, y, text());
    } else {
        painter.drawText(28, y, text());
    }
}



void XMatCheckable::setupProperties()
{
    Q_D(XMatCheckable);

    d->checkedState->assignProperty(d->checkedIcon, "color", checkedColor());
    d->checkedState->assignProperty(d->uncheckedIcon, "color", checkedColor());
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->disabledUncheckedState->assignProperty(d->uncheckedIcon, "color", disabledColor());
    d->disabledCheckedState->assignProperty(d->checkedIcon, "color", disabledColor());

    if (isEnabled()) {
        if (isChecked()) {
            d->checkedIcon->setColor(checkedColor());
        } else {
            d->uncheckedIcon->setColor(uncheckedColor());
        }
    } else {
        d->checkedIcon->setColor(disabledColor());
        d->uncheckedIcon->setColor(disabledColor());
    }

    update();
}
