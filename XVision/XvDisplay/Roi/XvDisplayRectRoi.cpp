#include "XvDisplayRectRoi.h"
#include <QPainter>

XvDisplayRectRoi::XvDisplayRectRoi(QPointF centerPos,double width,double height, QObject *parent)
    :XvDisplayBaseRoiItem(centerPos,parent)
{
    m_rectF=QRectF(m_ptCenterPos.rx()-width/2,m_ptCenterPos.ry()-height/2,width,height);
    m_rectControlItem=new XvDisplayControlItem(this,m_rectF.bottomRight(),XvDisplayControlItem::Control,XvDisplayControlItem::Circle);
}

void XvDisplayRectRoi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updatePainter(painter);
    painter->drawRect(m_rectF);
}

bool XvDisplayRectRoi::updateRoi(XvDisplayControlItem *controlItem)
{
    if(!XvDisplayBaseRoiItem::updateRoi(controlItem))
    {
        return false;
    }
    if(controlItem!=m_rectControlItem)
    {
        return false;
    }
    auto width=abs(controlItem->getPos().rx()-m_ptCenterPos.rx())*2;
    auto height=abs(controlItem->getPos().ry()-m_ptCenterPos.ry())*2;
    m_rectF=QRectF(m_ptCenterPos.rx()-width/2,m_ptCenterPos.ry()-height/2,width,height);

    return true;
}
