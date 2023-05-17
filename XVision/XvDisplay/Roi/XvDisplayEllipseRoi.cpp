#include "XvDisplayEllipseRoi.h"
#include <QPainter>

XvDisplayEllipseRoi::XvDisplayEllipseRoi(QPointF centerPos, double len1, double len2, double angle, QObject *parent)
    :XvDisplayRotateRectRoi(centerPos,len1,len2,angle,parent)
{

}

void XvDisplayEllipseRoi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updatePainter(painter);
    painter->drawLine(m_ptCenterPos,m_pt2);
    painter->save();
    painter->translate(m_ptCenterPos);
    painter->rotate(-m_angle*180/M_PI);
    painter-> drawEllipse(QRectF(-m_len1,-m_len2,m_len1*2,m_len2*2));
    painter->restore();
}
