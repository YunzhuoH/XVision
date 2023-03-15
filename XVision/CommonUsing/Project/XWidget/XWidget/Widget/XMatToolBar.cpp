﻿#include "XMatToolBar.h"
#include "XMatToolBar_p.h"
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
 *  \class XMatToolBarPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatToolBarPrivate::XMatToolBarPrivate(XMatToolBar *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatToolBarPrivate::~XMatToolBarPrivate()
{
}

/*!
 *  \internal
 */
void XMatToolBarPrivate::init()
{
    Q_Q(XMatToolBar);

    rippleOverlay        = new XMatRippleOverlay(q);


    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatToolBar
 */
XMatToolBar::XMatToolBar(QWidget *parent)
    :QToolBar(parent),d_ptr(new XMatToolBarPrivate(this))
{
    d_func()->init();
}

XMatToolBar::XMatToolBar(const QString &title, QWidget *parent)
    :QToolBar(title,parent),d_ptr(new XMatToolBarPrivate(this))
{
    d_func()->init();
}



XMatToolBar::~XMatToolBar()
{

}

void XMatToolBar::setRippleColor(const QColor &color)
{
    Q_D(XMatToolBar);
    d->rippleColor = color;
    update();
}

QColor XMatToolBar::rippleColor() const
{
    Q_D(const XMatToolBar);
    return d->rippleColor;
}

XMatToolBar::XMatToolBar(XMatToolBarPrivate &d, QWidget *parent)
    :QToolBar(parent),d_ptr(&d)
{
    d_func()->init();
}

void XMatToolBar::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatToolBar);
    QPoint pos = event->pos();
    XMatRipple *ripple = new XMatRipple(pos);
    qreal  radiusEndValue = static_cast<qreal>(width())/2;
    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);

    d->rippleOverlay->addRipple(ripple);

    QToolBar::mousePressEvent(event);
}
