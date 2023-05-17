#include "XvDisplayControlItem.h"
#include "XvDisplayBaseRoiItem.h"
#include <QPen>
#include <QBrush>
#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

XvDisplayControlItem::XvDisplayControlItem(XvDisplayBaseRoiItem *parRoi, QPointF pt,ControlType controlType, ShapeType shapeType)
    :QObject(parRoi),
     QAbstractGraphicsShapeItem(parRoi),
     m_parRoi(parRoi),
     m_ptPos(pt),
     m_eControlType(controlType),
     m_eShapeType(shapeType),
     m_nControlSize(ControlSize_Default)
{
    setCacheMode(DeviceCoordinateCache);
    setFlags(ItemIsSelectable|ItemIsMovable|ItemStopsFocusHandling);

    auto pen=this->pen();
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::NoBrush);
    this->setPen(pen);
    switch (m_eControlType)
    {
    case ControlType::Center:
        this->setCursor(Qt::SizeAllCursor);
        break;
    case ControlType::Control:
        this->setCursor(Qt::CrossCursor);
        break;
    }

    this->setPos(m_ptPos);
    m_ptLastPos=m_ptPos;
    m_parRoi->addControlItem(this);
    setControlColor(ControlColor_Default);
}

XvDisplayControlItem::~XvDisplayControlItem()
{

}

void XvDisplayControlItem::updatePos(const QPointF &pos)
{
    m_ptLastPos=m_ptPos;
    m_ptPos=pos;
    this->setPos(m_ptPos);
}

void XvDisplayControlItem::setControlColor(const QColor &color)
{
   m_controlColor=color;
    auto pen=this->pen();
    pen.setColor(m_controlColor);
    this->setPen(pen);
}

QRectF XvDisplayControlItem::boundingRect() const
{
   return QRectF(-m_nControlSize/2,-m_nControlSize/2,m_nControlSize, m_nControlSize);
}

void XvDisplayControlItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(this->pen());
    switch (m_eShapeType)
    {
    case ShapeType::Rect:
    {
        painter->drawRect(this->boundingRect());
    }
        break;
    case ShapeType::Circle:
    {
        auto penWidth=painter->pen().width();
        painter->drawEllipse(this->boundingRect().adjusted(penWidth,penWidth,-penWidth,-penWidth));
    }
        break;
    }
}

void XvDisplayControlItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton )
    {
        auto  dx = event->scenePos().x() - event->lastScenePos().x();
        auto  dy = event->scenePos().y() - event->lastScenePos().y();
        auto pt=event->pos();
        m_ptLastPos=m_ptPos;
        m_ptPos=this->mapToParent(pt);
        if(m_parRoi)
        {
            switch (m_eControlType)
            {
            case ControlType::Center:
            {
                if(!m_parRoi->moveRoiByOffset(QPointF(dx,dy)))
                {
                    m_ptPos=m_ptLastPos;
                    this->setPos(m_ptLastPos);
                }
            }
                break;
            case ControlType::Control:
            {
                if(!m_parRoi->updateRoi(this))
                {
                    m_ptPos=m_ptLastPos;

                }
                this->setPos(m_ptPos);
            }
                break;
            }

        }

    }
}

void XvDisplayControlItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->m_eControlType==ControlType::Center)
    {
        if(m_parRoi)
        {
            m_parRoi->setFocus();
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

