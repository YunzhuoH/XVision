#include "XMatScrollBar.h"
#include "XMatScrollBar_p.h"
#include <QPainter>
#include <QPainterPath>
#include "XMatScrollBar_internal.h"
#include "XMatStyleDef.h"

/*!
 *  \class XMatScrollBarPrivate
 *  \internal
 */

XMatScrollBarPrivate::XMatScrollBarPrivate(XMatScrollBar *q)
    : q_ptr(q)
{
    backgroundColor=C_XMatBackgroundColor;
    sliderColor=C_XMatThemeColor;
    canvasColor=C_XMatBackgroundColor;
}

XMatScrollBarPrivate::~XMatScrollBarPrivate()
{
}

void XMatScrollBarPrivate::init()
{
    Q_Q(XMatScrollBar);

    stateMachine   = new XMatScrollBarStateMachine(q);
    hideOnMouseOut = true;


    q->setMouseTracking(true);
    q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
                     "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
                     "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");

    stateMachine->start();
}

/*!
 *  \class XMatScrollBar
 */

XMatScrollBar::XMatScrollBar(QWidget *parent)
    : QScrollBar(parent),
      d_ptr(new XMatScrollBarPrivate(this))
{
    d_func()->init();
}

XMatScrollBar::~XMatScrollBar()
{
}

/*!
 *  \reimp
 */
QSize XMatScrollBar::sizeHint() const
{
    if (Qt::Horizontal == orientation()) {
        return QSize(1, 10);
    } else {
        return QSize(10, 1);
    }
}



void XMatScrollBar::setCanvasColor(const QColor &color)
{
    Q_D(XMatScrollBar);

    d->canvasColor = color;
    update();
}

QColor XMatScrollBar::canvasColor() const
{
    Q_D(const XMatScrollBar);

    return d->canvasColor;
}

void XMatScrollBar::setBackgroundColor(const QColor &color)
{
    Q_D(XMatScrollBar);

    d->backgroundColor = color;

    update();
}

QColor XMatScrollBar::backgroundColor() const
{
    Q_D(const XMatScrollBar);

    return d->backgroundColor;
}

void XMatScrollBar::setSliderColor(const QColor &color)
{
    Q_D(XMatScrollBar);

    d->sliderColor = color;

    update();
}

QColor XMatScrollBar::sliderColor() const
{
    Q_D(const XMatScrollBar);

   return d->sliderColor;
}

void XMatScrollBar::setHideOnMouseOut(bool value)
{
    Q_D(XMatScrollBar);

    d->hideOnMouseOut = value;
    update();
}

bool XMatScrollBar::hideOnMouseOut() const
{
    Q_D(const XMatScrollBar);

    return d->hideOnMouseOut;
}

/*!
 *  \reimp
 */
void XMatScrollBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatScrollBar);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), canvasColor());

    int x, y, w, h;
    rect().getRect(&x, &y, &w, &h);

    QMargins margins(2, 2, 2, 2);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (d->hideOnMouseOut) {
        painter.setOpacity(d->stateMachine->opacity());
    }

    QRect trimmed(rect().marginsRemoved(margins));

    QPainterPath path;
    path.addRoundedRect(trimmed, 3, 3);
    painter.setClipPath(path);

    painter.drawRect(trimmed);

    const qreal q = (Qt::Horizontal == orientation() ? w : h) /
            static_cast<qreal>(maximum()-minimum()+pageStep()-1);

    QRect handle = Qt::Horizontal == orientation()
            ? QRect(sliderPosition()*q, y, pageStep()*q, h)
            : QRect(x, sliderPosition()*q, w, pageStep()*q);

    brush.setColor(sliderColor());
    painter.setBrush(brush);

    painter.drawRoundedRect(handle, 9, 9);
}
