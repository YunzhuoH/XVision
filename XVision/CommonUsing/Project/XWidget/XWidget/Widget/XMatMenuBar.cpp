#include "XMatMenuBar.h"
#include "XMatMenuBar_p.h"
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
 *  \class XMatMenuBarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatMenuBarPrivate::XMatMenuBarPrivate(XMatMenuBar *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatMenuBarPrivate::~XMatMenuBarPrivate()
{
}

/*!
 *  \internal
 */
void XMatMenuBarPrivate::init()
{
    Q_Q(XMatMenuBar);

    rippleOverlay        = new XMatRippleOverlay(q);
    rippleStyle          = XMatCommonDef::PositionedRipple;

    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatMenuBar
 */
XMatMenuBar::XMatMenuBar(QWidget *parent)
    :QMenuBar(parent),d_ptr(new XMatMenuBarPrivate(this))
{
    d_func()->init();
}



XMatMenuBar::~XMatMenuBar()
{

}

void XMatMenuBar::setRippleStyle(XMatCommonDef::RippleStyle style)
{
    Q_D(XMatMenuBar);
    d->rippleStyle = style;
}

XMatCommonDef::RippleStyle XMatMenuBar::rippleStyle() const
{
    Q_D(const XMatMenuBar);
    return d->rippleStyle;
}

void XMatMenuBar::setRippleColor(const QColor &color)
{
    Q_D(XMatMenuBar);
    d->rippleColor = color;
    update();
}

QColor XMatMenuBar::rippleColor() const
{
    Q_D(const XMatMenuBar);
    return d->rippleColor;
}

XMatMenuBar::XMatMenuBar(XMatMenuBarPrivate &d, QWidget *parent)
    :QMenuBar(parent),d_ptr(&d)
{
    d_func()->init();
}

void XMatMenuBar::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatMenuBar);
    if (XMatCommonDef::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (XMatCommonDef::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->pos();
        }

        radiusEndValue = static_cast<qreal>(width())/2;

        XMatRipple *ripple = new XMatRipple(pos);
        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(rippleColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);
        d->rippleOverlay->addRipple(ripple);
    }

    QMenuBar::mousePressEvent(event);
}
