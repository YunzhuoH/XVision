#ifndef XVDISPLAYCIRCLEROI_H
#define XVDISPLAYCIRCLEROI_H

#include "XvDisplayBaseRoiItem.h"

#define RoiTypeCircle     3

class XVDISPLAY_EXPORT XvDisplayCircleRoi:public XvDisplayBaseRoiItem
{
    Q_OBJECT
public:
   explicit XvDisplayCircleRoi(QPointF centerPos,double radius=100, QObject* parent=nullptr);

    // QGraphicsItem interface
public:
    int roiType() const override { return RoiTypeCircle;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // XvDisplayBaseRoiItem interface
protected:
   bool updateRoi(XvDisplayControlItem *controlItem) override;
protected:
    double  m_rRadius;//半径
    XvDisplayControlItem* m_circleControlItem=nullptr;//控制点

};



#endif // XVDISPLAYCIRCLEROI_H
