#include "XMatSpinBox.h"
#include "XMatSpinBox_p.h"
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
 *  \class XMatSpinBoxPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatSpinBoxPrivate::XMatSpinBoxPrivate(XMatSpinBox *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatSpinBoxPrivate::~XMatSpinBoxPrivate()
{
}

/*!
 *  \internal
 */
void XMatSpinBoxPrivate::init()
{
    Q_Q(XMatSpinBox);

    rippleOverlay        = new XMatRippleOverlay(q);
    rippleStyle          = XMatCommonDef::PositionedRipple;

    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatSpinBox
 */

XMatSpinBox::XMatSpinBox(QWidget *parent)
    :QSpinBox(parent),d_ptr(new XMatSpinBoxPrivate(this))
{
   d_func()->init();
}

XMatSpinBox::~XMatSpinBox()
{

}

void XMatSpinBox::setRippleStyle(XMatCommonDef::RippleStyle style)
{
    Q_D(XMatSpinBox);
    d->rippleStyle = style;
}

XMatCommonDef::RippleStyle XMatSpinBox::rippleStyle() const
{
    Q_D(const XMatSpinBox);
    return d->rippleStyle;
}



void XMatSpinBox::setRippleColor(const QColor &color)
{
    Q_D(XMatSpinBox);
    d->rippleColor = color;
    update();
}

QColor XMatSpinBox::rippleColor() const
{
    Q_D(const XMatSpinBox);
    return d->rippleColor;
}

XMatSpinBox::XMatSpinBox(XMatSpinBoxPrivate &d, QWidget *parent)
    :QSpinBox(parent),d_ptr(&d)
{
    d_func()->init();
}

void XMatSpinBox::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatSpinBox);
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
    QSpinBox::mousePressEvent(event);
}

void XMatSpinBox::wheelEvent(QWheelEvent *event)
{
    Q_D(XMatSpinBox);
    if (XMatCommonDef::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (XMatCommonDef::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->position().toPoint();
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

    QSpinBox::wheelEvent(event);
}


