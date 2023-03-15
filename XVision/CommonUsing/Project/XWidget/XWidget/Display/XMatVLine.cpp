#include "XMatVLine.h"
#include <QPainter>

class XMatVLinePrivate
{
    Q_DISABLE_COPY(XMatVLinePrivate)
    Q_DECLARE_PUBLIC(XMatVLine)

public:
    XMatVLinePrivate(XMatVLine *q):q_ptr(q){};
    virtual ~XMatVLinePrivate(){};


    XMatVLine              *const q_ptr;
    Qt::PenStyle lineStyle=Qt::PenStyle::DashLine;
    QColor lineColor=QColor(Qt::gray);
    int lineWidth=1;
    int lineCutLen=0;
};

XMatVLine::XMatVLine(QWidget *parent)
    : QWidget{parent},
    d_ptr(new XMatVLinePrivate(this))
{
    resize(3,60);
    setMinimumWidth(3);
}

XMatVLine::~XMatVLine()
{

}

Qt::PenStyle XMatVLine::lineStyle() const
{
    Q_D(const XMatVLine);
    return  d->lineStyle;
}

void XMatVLine::setLineStyle(Qt::PenStyle style)
{
    Q_D(XMatVLine);
    d->lineStyle=style;
    update();
}

QColor XMatVLine::lineColor() const
{
    Q_D(const XMatVLine);
    return  d->lineColor;
}

void XMatVLine::setLineColor(QColor color)
{
    Q_D(XMatVLine);
    d->lineColor=color;
    update();
}

int XMatVLine::lineWidth() const
{
    Q_D(const XMatVLine);
    return  d->lineWidth;
}

void XMatVLine::setLineWidth(int width)
{
    Q_D(XMatVLine);
    d->lineWidth=width;
    update();
}

int XMatVLine::lineCutLen() const
{
    Q_D(const XMatVLine);
    return  d->lineCutLen;
}

void XMatVLine::setLineCurLen(int len)
{
    Q_D(XMatVLine);
    d->lineCutLen=len;
    update();
}

void XMatVLine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    QPen pen;
    pen.setStyle(lineStyle());
    pen.setColor(lineColor());
    pen.setWidth(lineWidth());
    painter.setPen(pen);
    QPoint p1=QPoint(width()/2,lineCutLen());
    QPoint p2=QPoint(width()/2,height()-lineCutLen());
    painter.drawLine(p1,p2);
}
