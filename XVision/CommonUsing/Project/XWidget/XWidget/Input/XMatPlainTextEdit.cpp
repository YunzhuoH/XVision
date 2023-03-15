#include "XMatPlainTextEdit.h"
#include "XMatPlainTextEdit_p.h"
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
 *  \class XMatPlainTextEditPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatPlainTextEditPrivate::XMatPlainTextEditPrivate(XMatPlainTextEdit *q)
    : q_ptr(q)
{
    rippleColor=C_XMatThemeColor;

}

/*!
 *  \internal
 */
XMatPlainTextEditPrivate::~XMatPlainTextEditPrivate()
{
}

/*!
 *  \internal
 */
void XMatPlainTextEditPrivate::init()
{
    Q_Q(XMatPlainTextEdit);

    rippleOverlay        = new XMatRippleOverlay(q);


    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

}

/*!
 *  \class XMatPlainTextEdit
 */
XMatPlainTextEdit::XMatPlainTextEdit(QWidget *parent)
    :QPlainTextEdit(parent),d_ptr(new XMatPlainTextEditPrivate(this))
{
    d_func()->init();
}

XMatPlainTextEdit::XMatPlainTextEdit(const QString &text, QWidget *parent)
    :QPlainTextEdit(text,parent),d_ptr(new XMatPlainTextEditPrivate(this))
{
    d_func()->init();

}

XMatPlainTextEdit::~XMatPlainTextEdit()
{

}

void XMatPlainTextEdit::setRippleColor(const QColor &color)
{
    Q_D(XMatPlainTextEdit);
    d->rippleColor = color;
    update();
}

QColor XMatPlainTextEdit::rippleColor() const
{
    Q_D(const XMatPlainTextEdit);
    return d->rippleColor;
}

XMatPlainTextEdit::XMatPlainTextEdit(XMatPlainTextEditPrivate &d, QWidget *parent)
    :QPlainTextEdit(parent),d_ptr(&d)
{
    d_func()->init();
}

void XMatPlainTextEdit::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatPlainTextEdit);
    QPoint pos = event->pos();
    XMatRipple *ripple = new XMatRipple(pos);
    qreal  radiusEndValue = static_cast<qreal>(width())/2;
    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);

    d->rippleOverlay->addRipple(ripple);

    QPlainTextEdit::mousePressEvent(event);
}

void XMatPlainTextEdit::wheelEvent(QWheelEvent *event)
{
    Q_D(XMatPlainTextEdit);

    QPoint pos;
    qreal radiusEndValue;

    pos = event->position().toPoint();

    radiusEndValue = static_cast<qreal>(width())/2;
    XMatRipple *ripple = new XMatRipple(pos);

    ripple->setRadiusEndValue(radiusEndValue);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(rippleColor());
    ripple->radiusAnimation()->setDuration(600);
    ripple->opacityAnimation()->setDuration(1300);

    d->rippleOverlay->addRipple(ripple);
    QPlainTextEdit::wheelEvent(event);
}
