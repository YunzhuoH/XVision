#include "XMatCircularProgress.h"
#include "XMatCircularProgress_p.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <QPainterPath>
#include "XMatCircularProgress_internal.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatCircularProgressPrivate
 *  \internal
 */

XMatCircularProgressPrivate::XMatCircularProgressPrivate(XMatCircularProgress *q)
    : q_ptr(q)
{
    color=C_XMatThemeColor;
    borderColor=QColor(170,170,170,170);
}

XMatCircularProgressPrivate::~XMatCircularProgressPrivate()
{
}

void XMatCircularProgressPrivate::init()
{
    Q_Q(XMatCircularProgress);

    delegate       = new XMatCircularProgressDelegate(q);
    progressType   = IndeterminateProgress;
    penWidth       = 6.25;
    size           = 64;


    q->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,
                                 QSizePolicy::MinimumExpanding));

    QParallelAnimationGroup *group = new QParallelAnimationGroup(q);
    group->setLoopCount(-1);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashLength");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->setStartValue(0.1);
    animation->setKeyValueAt(0.15, 0.2);
    animation->setKeyValueAt(0.6, 20);
    animation->setKeyValueAt(0.7, 20);
    animation->setEndValue(20);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("dashOffset");
    animation->setTargetObject(delegate);
    animation->setEasingCurve(QEasingCurve::InOutSine);
    animation->setStartValue(0);
    animation->setKeyValueAt(0.15, 0);
    animation->setKeyValueAt(0.6, -7);
    animation->setKeyValueAt(0.7, -7);
    animation->setEndValue(-25);
    animation->setDuration(2050);

    group->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("angle");
    animation->setTargetObject(delegate);
    animation->setStartValue(0);
    animation->setEndValue(719);
    animation->setDuration(2050);

    group->addAnimation(animation);

    group->start();
}

/*!
 *  \class XMatCircularProgress
 */

XMatCircularProgress::XMatCircularProgress(QWidget *parent)
    : QProgressBar(parent),
      d_ptr(new XMatCircularProgressPrivate(this))
{
    d_func()->init();
}

XMatCircularProgress::~XMatCircularProgress()
{
}

void XMatCircularProgress::setProgressType(ProgressType type)
{
    Q_D(XMatCircularProgress);

    d->progressType = type;
    update();
}

ProgressType XMatCircularProgress::progressType() const
{
    Q_D(const XMatCircularProgress);

    return d->progressType;
}



void XMatCircularProgress::setLineWidth(qreal width)
{
    Q_D(XMatCircularProgress);

    d->penWidth = width;
    update();
    updateGeometry();
}

qreal XMatCircularProgress::lineWidth() const
{
    Q_D(const XMatCircularProgress);

    return d->penWidth;
}

void XMatCircularProgress::setSize(int size)
{
    Q_D(XMatCircularProgress);

    d->size = size;
    update();
    updateGeometry();
}

int XMatCircularProgress::size() const
{
    Q_D(const XMatCircularProgress);

    return d->size;
}

void XMatCircularProgress::setColor(const QColor &color)
{
    Q_D(XMatCircularProgress);

    d->color = color;


    update();
}

QColor XMatCircularProgress::color() const
{
    Q_D(const XMatCircularProgress);

    return d->color;
}

void XMatCircularProgress::setBorderColor(const QColor &color)
{

        Q_D(XMatCircularProgress);

        d->borderColor = color;

        update();
}

QColor XMatCircularProgress::borderColor() const
{
    Q_D(const XMatCircularProgress);

    return d->borderColor;
}

/*!
 *  \reimp
 */
QSize XMatCircularProgress::sizeHint() const
{
    Q_D(const XMatCircularProgress);

    const qreal s = d->size+d->penWidth+8;
    return QSize(s, s);
}

/*!
 *  \reimp
 */
void XMatCircularProgress::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatCircularProgress);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!isEnabled())
    {
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(d->penWidth);
        pen.setColor(d->borderColor);
        painter.setPen(pen);
        painter.drawLine(rect().center()-QPointF(20, 20), rect().center()+QPointF(20, 20));
        painter.drawLine(rect().center()+QPointF(20, -20), rect().center()-QPointF(20, -20));
        return;
    }

    if (IndeterminateProgress == d->progressType)
    {
        painter.translate(width()/2, height()/2);
        painter.rotate(d->delegate->angle());
    }

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(d->penWidth);
    pen.setColor(color());

    if (IndeterminateProgress == d->progressType)
    {
        QVector<qreal> pattern;
        pattern << d->delegate->dashLength()*d->size/50 << 30*d->size/50;

        pen.setDashOffset(d->delegate->dashOffset()*d->size/50);
        pen.setDashPattern(pattern);

        painter.setPen(pen);

        painter.drawEllipse(QPoint(0, 0), d->size/2, d->size/2);
    }
    else
    {
        painter.setPen(pen);

        const qreal x = (width()-d->size)/2;
        const qreal y = (height()-d->size)/2;

        const qreal a = 360*(value()-minimum())/(maximum()-minimum());

        QPainterPath path;
        path.arcMoveTo(x, y, d->size, d->size, 0);
        path.arcTo(x, y, d->size, d->size, 0, a);

        painter.drawPath(path);
    }
}
