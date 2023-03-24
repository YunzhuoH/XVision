#include "XMatSuspendWidget.h"
#include "XMatSuspendWidget_p.h"
#include <QStackedLayout>
#include <QGraphicsDropShadowEffect>
#include <QStateMachine>
#include <QState>
#include <QtWidgets/QApplication>
#include <QPropertyAnimation>
#include <QPainter>
#include "XMatSuspendWidget_internal.h"
#include "XMatSuspendWidgetStateTransition.h"

/*!
 *  \class XMatSuspendWidgetPrivate
 *  \internal
 */

XMatSuspendWidgetPrivate::XMatSuspendWidgetPrivate(XMatSuspendWidget *q)
    : q_ptr(q)
{
}

XMatSuspendWidgetPrivate::~XMatSuspendWidgetPrivate()
{
}

void XMatSuspendWidgetPrivate::init()
{
    Q_Q(XMatSuspendWidget);

    widgetWindow = new XMatSuspendWidgetWindow(q);
    proxyStack   = new QStackedLayout;
    stateMachine = new QStateMachine(q);
    proxy        = new XMatSuspendWidgetProxy(widgetWindow, proxyStack, q);

    QVBoxLayout *layout = new QVBoxLayout;
    q->setLayout(layout);

    QWidget *widget = new QWidget;
    widget->setLayout(proxyStack);
    widget->setMinimumWidth(400);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 200));
    effect->setBlurRadius(64);
    effect->setOffset(0, 13);
    widget->setGraphicsEffect(effect);

    layout->addWidget(widget);
    layout->setAlignment(widget, Qt::AlignCenter);

    proxyStack->addWidget(widgetWindow);
    proxyStack->addWidget(proxy);
    proxyStack->setCurrentIndex(1);

    q->setAttribute(Qt::WA_TransparentForMouseEvents);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;

    stateMachine->addState(hiddenState);
    stateMachine->addState(visibleState);
    stateMachine->setInitialState(hiddenState);

    XMatSuspendWidgetStateTransition *transition;

    transition = new XMatSuspendWidgetStateTransition(SuspendWidgetShowTransition);
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new XMatSuspendWidgetStateTransition(SuspendWidgetHideTransition);
    transition->setTargetState(hiddenState);
    visibleState->addTransition(transition);

    visibleState->assignProperty(proxy, "opacity", 1);
    visibleState->assignProperty(effect, "color", QColor(0, 0, 0, 200));
    visibleState->assignProperty(widgetWindow, "offset", 0);
    hiddenState->assignProperty(proxy, "opacity", 0);
    hiddenState->assignProperty(effect, "color", QColor(0, 0, 0, 0));
    hiddenState->assignProperty(widgetWindow, "offset", 200);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(proxy, "opacity", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(effect, "color", q);
    animation->setDuration(280);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(widgetWindow, "offset", q);
    animation->setDuration(280);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    stateMachine->addDefaultAnimation(animation);

    QObject::connect(visibleState, SIGNAL(propertiesAssigned()),
                     proxy, SLOT(makeOpaque()));
    QObject::connect(hiddenState, SIGNAL(propertiesAssigned()),
                     proxy, SLOT(makeTransparent()));

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class XMatSuspendWidget
 */

XMatSuspendWidget::XMatSuspendWidget(QWidget *parent)
    : XMatOverlayWidget(parent),
      d_ptr(new XMatSuspendWidgetPrivate(this))
{
    d_func()->init();
}

XMatSuspendWidget::~XMatSuspendWidget()
{
}

QLayout *XMatSuspendWidget::windowLayout() const
{
    Q_D(const XMatSuspendWidget);

    return d->widgetWindow->layout();
}

void XMatSuspendWidget::setWindowLayout(QLayout *layout)
{
    Q_D(XMatSuspendWidget);

    d->widgetWindow->setLayout(layout);
}

void XMatSuspendWidget::showWidget()
{
    Q_D(XMatSuspendWidget);

    d->stateMachine->postEvent(new XMatSuspendWidgetStateTransitionEvent(SuspendWidgetShowTransition));
    raise();
}

void XMatSuspendWidget::hideWidget()
{
    Q_D(XMatSuspendWidget);

    d->stateMachine->postEvent(new XMatSuspendWidgetStateTransitionEvent(SuspendWidgetHideTransition));
    setAttribute(Qt::WA_TransparentForMouseEvents);
    d->proxyStack->setCurrentIndex(1);
}

void XMatSuspendWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatSuspendWidget);

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.setOpacity(d->proxy->opacity()/2.4);
    painter.drawRect(rect());
}
