#include "XMatHLine.h"
#include <QPainter>

class XMatHLinePrivate
{
    Q_DISABLE_COPY(XMatHLinePrivate)
    Q_DECLARE_PUBLIC(XMatHLine)

public:
    XMatHLinePrivate(XMatHLine *q):q_ptr(q){};
    virtual ~XMatHLinePrivate(){};


    XMatHLine              *const q_ptr;
    Qt::PenStyle lineStyle=Qt::PenStyle::DashLine;
    QColor lineColor=QColor(Qt::gray);
    int lineWidth=1;
    int lineCutLen=0;
};

XMatHLine::XMatHLine(QWidget *parent)
    : QWidget{parent},
    d_ptr(new XMatHLinePrivate(this))
{
    resize(60,3);
    setMinimumHeight(3);
}

XMatHLine::~XMatHLine()
{

}

Qt::PenStyle XMatHLine::lineStyle() const
{
    Q_D(const XMatHLine);
    return  d->lineStyle;
}

void XMatHLine::setLineStyle(Qt::PenStyle style)
{
    Q_D(XMatHLine);
    d->lineStyle=style;
    update();
}

QColor XMatHLine::lineColor() const
{
    Q_D(const XMatHLine);
    return  d->lineColor;
}

void XMatHLine::setLineColor(QColor color)
{
    Q_D(XMatHLine);
    d->lineColor=color;
    update();
}

int XMatHLine::lineWidth() const
{
    Q_D(const XMatHLine);
    return  d->lineWidth;
}

void XMatHLine::setLineWidth(int width)
{
    Q_D(XMatHLine);
    d->lineWidth=width;
    update();
}

int XMatHLine::lineCutLen() const
{
    Q_D(const XMatHLine);
    return  d->lineCutLen;
}

void XMatHLine::setLineCurLen(int len)
{
    Q_D(XMatHLine);
    d->lineCutLen=len;
    update();
}

void XMatHLine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QPen pen;
    pen.setStyle(lineStyle());
    pen.setColor(lineColor());
    pen.setWidth(lineWidth());
    painter.setPen(pen);
    QPoint p1=QPoint(lineCutLen(),height()/2);
    QPoint p2=QPoint(width()-lineCutLen(),height()/2);
    painter.drawLine(p1,p2);
}
