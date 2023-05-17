#include "XvDisplayCircleRoi.h"
#include <QPen>
#include <QPainter>

XvDisplayCircleRoi::XvDisplayCircleRoi(QPointF centerPos, double radius, QObject *parent)
    :XvDisplayBaseRoiItem(centerPos,parent),
     m_rRadius(radius)
{
    m_circleControlItem=new XvDisplayControlItem(this,m_ptCenterPos+QPointF(m_rRadius,0),XvDisplayControlItem::Control,XvDisplayControlItem::Circle);
}

QRectF XvDisplayCircleRoi::boundingRect() const
{
  return QRectF(m_ptCenterPos.x()-m_rRadius,m_ptCenterPos.y()-m_rRadius,m_rRadius*2,m_rRadius*2);
}

void XvDisplayCircleRoi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updatePainter(painter);
    painter->drawEllipse(this->boundingRect());
}

bool XvDisplayCircleRoi::updateRoi(XvDisplayControlItem *controlItem)
{
    if(!XvDisplayBaseRoiItem::updateRoi(controlItem))
    {
        return false;
    }
    if(controlItem!=m_circleControlItem)
    {
        return false;
    }
    QPointF tmp=controlItem->getPos()-m_ptCenterPos;
    m_rRadius=sqrt(tmp.x()*tmp.x()+tmp.y()*tmp.y());
    return true;
}
