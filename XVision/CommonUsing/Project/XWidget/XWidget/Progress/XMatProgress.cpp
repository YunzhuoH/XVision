#include "XMatProgress.h"
#include "XMatProgress_p.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QPainterPath>
#include "XMatProgress_internal.h"
#include "XMatStyleDef.h"

/*!
 *  \class XMatProgressPrivate
 *  \internal
 */

XMatProgressPrivate::XMatProgressPrivate(XMatProgress *q)
    : q_ptr(q)
{  
    progressColor=C_XMatThemeColor;
    backgroundColor=QColor(170,170,170,170);
    disabledColor=C_XMatDisableForegroundColor;
}

XMatProgressPrivate::~XMatProgressPrivate()
{
}

void XMatProgressPrivate::init()
{
    Q_Q(XMatProgress);

    delegate       = new XMatProgressDelegate(q);
    progressType   = IndeterminateProgress;


    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("offset");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(1000);

    animation->setLoopCount(-1);

    animation->start();
}

/*!
 *  \class XMatProgress
 */

XMatProgress::XMatProgress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new XMatProgressPrivate(this))
{
    d_func()->init();
}

XMatProgress::~XMatProgress()
{
}

void XMatProgress::setProgressType(ProgressType type)
{
    Q_D(XMatProgress);

    d->progressType = type;
    update();
}

ProgressType XMatProgress::progressType() const
{
    Q_D(const XMatProgress);

    return d->progressType;
}


void XMatProgress::setProgressColor(const QColor &color)
{
    Q_D(XMatProgress);

    d->progressColor = color;

    update();
}

QColor XMatProgress::progressColor() const
{
    Q_D(const XMatProgress);

    return d->progressColor;
}

void XMatProgress::setBackgroundColor(const QColor &color)
{
    Q_D(XMatProgress);

    d->backgroundColor = color;

    update();
}

QColor XMatProgress::backgroundColor() const
{
    Q_D(const XMatProgress);
    return d->backgroundColor;
}

void XMatProgress::setDisabledColor(const QColor &color)
{
    Q_D(XMatProgress);

    d->disabledColor = color;

    update();
}

QColor XMatProgress::disabledColor() const
{
    Q_D(const XMatProgress);
    return d->disabledColor;
}

/*!
 *  \reimp
 */
void XMatProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled() ? backgroundColor()
                               :d->disabledColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, height()/2-3, width(), 6, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(0, 0, width(), height());

    if (isEnabled())
    {
        brush.setColor(progressColor());
        painter.setBrush(brush);

        if (IndeterminateProgress == d->progressType) {
            painter.drawRect(d->delegate->offset()*width()*2-width(), 0, width(), height());
        } else {
            qreal p = static_cast<qreal>(width())*(value()-minimum())/(maximum()-minimum());
            painter.drawRect(0, 0, p, height());
        }
    }
}
