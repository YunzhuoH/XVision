#include "XvDisplayRotateRectRoi.h"
#include <QPainter>


XvDisplayRotateRectRoi::XvDisplayRotateRectRoi(QPointF centerPos, double len1, double len2, double angle, QObject *parent)
    :XvDisplayBaseRoiItem(centerPos,parent),
      m_len1(len1),
      m_len2(len2),
      m_angle(angle)
{
    double rSin = sin(-m_angle);
    double rCos = cos(-m_angle);
    m_pt1=m_ptCenterPos+QPointF(0*rCos - m_len2*rSin, 0*rSin+m_len2*rCos);
    m_pt2=m_ptCenterPos+QPointF(m_len1*rCos-0*rSin, m_len1*rSin+0*rCos);
    m_pt3=m_ptCenterPos+QPointF(0*rCos+m_len2*rSin, 0*rSin-m_len2*rCos);
    m_pt4=m_ptCenterPos+QPointF(-m_len1*rCos-0*rSin, -m_len1*rSin+0*rCos);
    m_ptArrow=m_ptCenterPos+QPointF((m_len1+RotateArrowLen)*rCos-0*rSin,(m_len1+RotateArrowLen)*rSin+0*rCos);

    m_controlItem1=new XvDisplayControlItem(this,m_pt1,XvDisplayControlItem::Control,XvDisplayControlItem::Circle);
    m_controlItem2=new XvDisplayControlItem(this,m_pt2,XvDisplayControlItem::Control,XvDisplayControlItem::Circle);
    m_controlItem3=new XvDisplayControlItem(this,m_pt3,XvDisplayControlItem::Control,XvDisplayControlItem::Circle);
    m_controlItem4=new XvDisplayControlItem(this,m_pt4,XvDisplayControlItem::Control,XvDisplayControlItem::Circle);

}

QRectF XvDisplayRotateRectRoi::boundingRect() const
{
    qreal tmp=(m_len1>m_len2?m_len2:m_len1);
    return QRectF(m_ptCenterPos.x()-tmp,m_ptCenterPos.y()-tmp,tmp*2,tmp*2);
}


bool XvDisplayRotateRectRoi::updateRoi(XvDisplayControlItem *controlItem)
{
    auto Pf=controlItem->getPos();

    qreal dx = Pf.x() - m_ptCenterPos.x();
    qreal dy = Pf.y() - m_ptCenterPos.y();
    if ( dx >= 0 && dy < 0 )
    {
        m_angle = atan2( (-1)*(dy), dx );
    }
    else if ( dx < 0 && dy < 0 )
    {
        m_angle = atan2( (-1)*dy, dx );
    }
    else if ( dx < 0 && dy >= 0 )
    {
        m_angle = M_PI*2 + atan2( (-1)*dy, dx );
    }
    else if ( dx >= 0 && dy >= 0 )
    {
        m_angle = M_PI*2 - atan2( dy, dx ) ;
    }

    //角度补偿 角度方向逆时针 控制点排列方向 顺时针
    if(controlItem==m_controlItem1)
    {
        m_angle+=M_PI/2;
    }
    else if(controlItem==m_controlItem3)
    {
       m_angle+=M_PI*3/2;
    }
    else if(controlItem==m_controlItem4)
    {
       m_angle+=M_PI;
    }

    qreal rSin = sin(-m_angle);
    qreal rCos = cos(-m_angle);
    if(controlItem==m_controlItem2||controlItem==m_controlItem4)
    {
       m_len1=sqrt(dx*dx+dy*dy);
    }else if (controlItem==m_controlItem1||controlItem==m_controlItem3)
    {
       m_len2=sqrt(dx*dx+dy*dy);
    }
    m_pt1=m_ptCenterPos+QPointF(0*rCos - m_len2*rSin, 0*rSin+m_len2*rCos);
    m_pt2=m_ptCenterPos+QPointF(m_len1*rCos-0*rSin, m_len1*rSin+0*rCos);
    m_pt3=m_ptCenterPos+QPointF(0*rCos+m_len2*rSin, 0*rSin-m_len2*rCos);
    m_pt4=m_ptCenterPos+QPointF(-m_len1*rCos-0*rSin, -m_len1*rSin+0*rCos);
    m_ptArrow=m_ptCenterPos+QPointF((m_len1+RotateArrowLen)*rCos-0*rSin,(m_len1+RotateArrowLen)*rSin+0*rCos);

    m_controlItem1->updatePos(m_pt1);
    m_controlItem2->updatePos(m_pt2);
    m_controlItem3->updatePos(m_pt3);
    m_controlItem4->updatePos(m_pt4);
    return true;
}

void XvDisplayRotateRectRoi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updatePainter(painter);

    //画角度方向线
    painter->drawLine(m_ptArrow,m_pt2);
    //绘制方向箭头
    double rArrowLen = RotateArrowLen/2;//箭头长度
    double ratan1=atan2((m_ptArrow.y() - m_pt2.y()) , (m_ptArrow.x() - m_pt2.x()));
    double ratan2=atan2((m_ptArrow.x() - m_pt2.x()) , (m_ptArrow.y() - m_pt2.y()));
    QPointF ptArrow1(m_ptArrow.x() - rArrowLen * cos(ratan1 - 0.5),m_ptArrow.y() - rArrowLen * sin(ratan1 - 0.5));
    QPointF ptArrow2(m_ptArrow.x() - rArrowLen * sin(ratan2 - 0.5),m_ptArrow.y() - rArrowLen * cos(ratan2 - 0.5));
    painter->drawLine(m_ptArrow,ptArrow1);
    painter->drawLine(m_ptArrow,ptArrow2);

    //绘制矩形
    painter->save();
    painter->translate(m_ptCenterPos);
    painter->rotate(-m_angle*180/M_PI);
    painter->drawRect(QRectF(-m_len1,-m_len2,m_len1*2,m_len2*2));
    painter->restore();
}
