#include "XMatMenu.h"
#include "XMatMenu_p.h"
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
 *  \class XMatMenuPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatMenuPrivate::XMatMenuPrivate(XMatMenu *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatMenuPrivate::~XMatMenuPrivate()
{
}

/*!
 *  \internal
 */
void XMatMenuPrivate::init()
{
    Q_Q(XMatMenu);

    rippleOverlay        = new XMatRippleOverlay(q);
    rippleStyle          = XMatCommonDef::PositionedRipple;

    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatMenu
 */
XMatMenu::XMatMenu(QWidget *parent)
    :QMenu(parent),d_ptr(new XMatMenuPrivate(this))
{
    d_func()->init();
}

XMatMenu::XMatMenu(const QString &title, QWidget *parent)
    :QMenu(title,parent),d_ptr(new XMatMenuPrivate(this))
{
    d_func()->init();
}



XMatMenu::~XMatMenu()
{

}

void XMatMenu::setRippleStyle(XMatCommonDef::RippleStyle style)
{
    Q_D(XMatMenu);
    d->rippleStyle = style;
}

XMatCommonDef::RippleStyle XMatMenu::rippleStyle() const
{
    Q_D(const XMatMenu);
    return d->rippleStyle;
}

void XMatMenu::setRippleColor(const QColor &color)
{
    Q_D(XMatMenu);
    d->rippleColor = color;
    update();
}

QColor XMatMenu::rippleColor() const
{
    Q_D(const XMatMenu);
    return d->rippleColor;
}

XMatMenu::XMatMenu(XMatMenuPrivate &d, QWidget *parent)
    :QMenu(parent),d_ptr(&d)
{
    d_func()->init();
}

void XMatMenu::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatMenu);
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


    QMenu::mousePressEvent(event);
}
