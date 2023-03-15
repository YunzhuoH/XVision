#include "XMatToolButton.h"
#include "XMatToolButton_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QBitmap>
#include <QPainterPath>
#include <QIcon>
#include "XMatRippleoverlay.h"
#include "XMatRipple.h"

#include "XMatStyleDef.h"
/*!
 *  \class XMatToolButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatToolButtonPrivate::XMatToolButtonPrivate(XMatToolButton *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatToolButtonPrivate::~XMatToolButtonPrivate()
{
}

/*!
 *  \internal
 */
void XMatToolButtonPrivate::init()
{
    Q_Q(XMatToolButton);

    rippleOverlay        = new XMatRippleOverlay(q);


    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);
    q->setAutoRaise(true);
    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatLabel
 */
XMatToolButton::XMatToolButton(QWidget *parent)
    :QToolButton(parent),d_ptr(new XMatToolButtonPrivate(this))
{
    d_func()->init();
    setText("...");
}


XMatToolButton::~XMatToolButton()
{

}

void XMatToolButton::setRippleColor(const QColor &color)
{
    Q_D(XMatToolButton);
    d->rippleColor = color;
    update();
}

QColor XMatToolButton::rippleColor() const
{
    Q_D(const XMatToolButton);
    return d->rippleColor;
}

XMatToolButton::XMatToolButton(XMatToolButtonPrivate &d, QWidget *parent)
    :QToolButton(parent),d_ptr(&d)
{
    d_func()->init();
    setText("...");
}

void XMatToolButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatToolButton);
    QPoint pos = event->pos();
    XMatRipple *ripple = new XMatRipple(pos);
    qreal  radiusEndValue = static_cast<qreal>(width())/2;
    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);

    d->rippleOverlay->addRipple(ripple);

    QToolButton::mousePressEvent(event);
}
