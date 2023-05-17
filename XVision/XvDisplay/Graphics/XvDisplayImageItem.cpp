#include "XvDisplayImageItem.h"
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>


/*******************************/
//* [SImageItemDisplayText]
/*******************************/
///显示文本结构体
struct SDisplayText
{
    SDisplayText()
    {
        text="";
        pos=QPointF(0,0);
        factor=1.0;
        color=QColor(Qt::green);
    }
    SDisplayText(const QString &_text,const QPointF &_pos,const double &_factor,const QColor &_color)
        :text(_text),pos(_pos),factor(_factor),color(_color)
    {

    }

    QString                         text; //显示文本
    QPointF                         pos;//显示文本位置
    double                          factor;//显示文本的大小系数
    QColor                          color;//显示文本的颜色
};

/*******************************/
//* [XvDisplayImageItemPrivate]
/*******************************/

class XvDisplayImageItemPrivate
{
    Q_DISABLE_COPY(XvDisplayImageItemPrivate)
    Q_DECLARE_PUBLIC(XvDisplayImageItem)

public:
    XvDisplayImageItemPrivate(XvDisplayImageItem *q):q_ptr(q)
    {
        centerCrossShow=false;
        centerCrosspen=QPen(Qt::green);
        centerCrosspen.setStyle(Qt::SolidLine);
        centerCrosspen.setWidth(1);
        lstDisplayText.clear();
    };
    virtual ~XvDisplayImageItemPrivate(){};

public:
    XvDisplayImageItem              *const q_ptr;
    bool                            centerCrossShow;//显示中心十字
    QPen                            centerCrosspen;//中心十字画笔
    QList<SDisplayText>             lstDisplayText;
};

/*******************************/
//* [XvDisplayImageItem]
/*******************************/
XvDisplayImageItem::XvDisplayImageItem(QObject *parent)
    :QObject{parent},
    QGraphicsPixmapItem(nullptr),
    d_ptr(new XvDisplayImageItemPrivate(this))
{
    setAcceptHoverEvents(true);
}

XvDisplayImageItem::~XvDisplayImageItem()
{

}

bool XvDisplayImageItem::centerCrossShow() const
{
    Q_D(const XvDisplayImageItem);
    return d->centerCrossShow;
}

void XvDisplayImageItem::setCenterCrossShow(const bool &show)
{
    Q_D(XvDisplayImageItem);
    d->centerCrossShow=show;
}

QPen XvDisplayImageItem::centerCrossPen() const
{
    Q_D(const XvDisplayImageItem);
    return d->centerCrosspen;
}

void XvDisplayImageItem::setCenterCrossPen(const QPen &pen)
{
    Q_D(XvDisplayImageItem);
    d->centerCrosspen=pen;
}

QColor XvDisplayImageItem::centerCrossColor() const
{
    Q_D(const XvDisplayImageItem);
    return d->centerCrosspen.color();
}

void XvDisplayImageItem::setCenterCrossColor(const QColor &color)
{
    Q_D(XvDisplayImageItem);
    d->centerCrosspen.setColor(color);
}

bool XvDisplayImageItem::displayImage(const QImage &image)
{
    if(image.isNull()) return false;
    setPixmap(QPixmap::fromImage(image));
    return true;
}

void XvDisplayImageItem::clearImage()
{
    setPixmap(QPixmap());
}

void XvDisplayImageItem::addDisplayText(const QString &text,const QPointF &pt,const double &size,const QColor &color,const bool &clear)
{
    Q_D(XvDisplayImageItem);
    if(clear)
    {
        d->lstDisplayText.clear();
    }
    d->lstDisplayText.append(SDisplayText(text,pt,size,color));
    this->update();
}

void XvDisplayImageItem::clearDisplayText()
{
    Q_D(XvDisplayImageItem);
    d->lstDisplayText.clear();
    this->update();
}

QPointF XvDisplayImageItem::getDisplayImageCenter() const
{
    auto width=this->pixmap().width();
    auto height=this->pixmap().height();
    QPointF center=QPointF(width/2.0,height/2.0);
    return mapToScene(center);
}

void XvDisplayImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter,option,widget);
    Q_D(XvDisplayImageItem);
    if(d->centerCrossShow&&!this->pixmap().isNull())
    {
        painter->save();
        painter->setPen(d->centerCrosspen);
        auto width=this->pixmap().width();
        auto height=this->pixmap().height();
        QPointF center=QPointF(width/2.0,height/2.0);
        QList<QLineF> lst;
        lst.append(QLineF(center,QPointF(0,center.ry())));
        lst.append(QLineF(center,QPointF(center.rx(),0)));
        lst.append(QLineF(center,QPointF(center.rx(),height)));
        lst.append(QLineF(center,QPointF(width,center.ry())));
        painter->drawLines(lst);
        painter->restore();
    }
    //显示文本
    foreach (auto displayText, d->lstDisplayText)
    {
        painter->save();
        auto pen=painter->pen();
        pen.setColor(displayText.color);
        painter->setPen(pen);

        auto font=painter->font();
        auto newPointSize= font.pointSize()*displayText.factor;
        font.setPointSize(newPointSize);
        painter->setFont(font);

        QFontMetricsF metrics(font);
        auto size= metrics.size(Qt::TextExpandTabs,displayText.text);
        painter->drawText(QRectF(displayText.pos,size),Qt::AlignCenter,displayText.text);
        painter->restore();
    }

}

void XvDisplayImageItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF pos = event->pos();
    emit this->sgHoverImagePosition(pos.toPoint());
    return QGraphicsPixmapItem::hoverMoveEvent(event);
}

void XvDisplayImageItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit this->sgHoverLeave();
    return QGraphicsPixmapItem::hoverLeaveEvent(event);
}
