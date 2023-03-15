﻿#include "XMatDoubleSpinBox.h"
#include "XMatDoubleSpinBox_p.h"
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
 *  \class XMatDoubleSpinBoxPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatDoubleSpinBoxPrivate::XMatDoubleSpinBoxPrivate(XMatDoubleSpinBox *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatDoubleSpinBoxPrivate::~XMatDoubleSpinBoxPrivate()
{
}

/*!
 *  \internal
 */
void XMatDoubleSpinBoxPrivate::init()
{
    Q_Q(XMatDoubleSpinBox);

    rippleOverlay        = new XMatRippleOverlay(q);


    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatDoubleSpinBox
 */

XMatDoubleSpinBox::XMatDoubleSpinBox(QWidget *parent)
    :QDoubleSpinBox(parent),d_ptr(new XMatDoubleSpinBoxPrivate(this))
{
   d_func()->init();
}

XMatDoubleSpinBox::~XMatDoubleSpinBox()
{

}


void XMatDoubleSpinBox::setRippleColor(const QColor &color)
{
    Q_D(XMatDoubleSpinBox);
    d->rippleColor = color;
    update();
}

QColor XMatDoubleSpinBox::rippleColor() const
{
    Q_D(const XMatDoubleSpinBox);
    return d->rippleColor;
}

XMatDoubleSpinBox::XMatDoubleSpinBox(XMatDoubleSpinBoxPrivate &d, QWidget *parent)
    :QDoubleSpinBox(parent),d_ptr(&d)
{
    d_func()->init();
}

void XMatDoubleSpinBox::mousePressEvent(QMouseEvent *event)
{

    Q_D(XMatDoubleSpinBox);
    QPoint pos = event->pos();
    XMatRipple *ripple = new XMatRipple(pos);
    qreal  radiusEndValue = static_cast<qreal>(width())/2;
    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);

    d->rippleOverlay->addRipple(ripple);
    QDoubleSpinBox::mousePressEvent(event);

}

void XMatDoubleSpinBox::wheelEvent(QWheelEvent *event)
{
    Q_D(XMatDoubleSpinBox);
    QPoint pos = event->position().toPoint();
    XMatRipple *ripple = new XMatRipple(pos);
    qreal  radiusEndValue = static_cast<qreal>(width())/2;
    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);
    d->rippleOverlay->addRipple(ripple);

    QDoubleSpinBox::wheelEvent(event);
}


