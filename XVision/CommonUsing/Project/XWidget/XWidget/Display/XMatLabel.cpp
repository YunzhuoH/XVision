#include "XMatLabel.h"
#include "XMatLabel_p.h"
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
 *  \class XMatLabelPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatLabelPrivate::XMatLabelPrivate(XMatLabel *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatLabelPrivate::~XMatLabelPrivate()
{
}

/*!
 *  \internal
 */
void XMatLabelPrivate::init()
{
    Q_Q(XMatLabel);

    rippleOverlay        = new XMatRippleOverlay(q);


    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatLabel
 */
XMatLabel::XMatLabel(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f),d_ptr(new XMatLabelPrivate(this))
{
    d_func()->init();
    setText("XMatLabel");
}

XMatLabel::XMatLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text,parent,f),d_ptr(new XMatLabelPrivate(this))
{
    d_func()->init();

}

XMatLabel::~XMatLabel()
{

}

void XMatLabel::setRippleColor(const QColor &color)
{
    Q_D(XMatLabel);
    d->rippleColor = color;
    update();
}

QColor XMatLabel::rippleColor() const
{
    Q_D(const XMatLabel);
    return d->rippleColor;
}

XMatLabel::XMatLabel(XMatLabelPrivate &d, QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f),d_ptr(&d)
{
    d_func()->init();
    setText("XMatLabel");
}

void XMatLabel::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatLabel);
    QPoint pos = event->pos();
    XMatRipple *ripple = new XMatRipple(pos);
    qreal  radiusEndValue = static_cast<qreal>(width())/2;
    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);

    d->rippleOverlay->addRipple(ripple);

    QLabel::mousePressEvent(event);
}
