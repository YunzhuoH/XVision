#ifndef XVDISPLAYROTATERECTROI_H
#define XVDISPLAYROTATERECTROI_H

#include "XvDisplayBaseRoiItem.h"
#define RotateArrowLen        30
#define RoiTypeRotateRect     2

class XVDISPLAY_EXPORT XvDisplayRotateRectRoi:public XvDisplayBaseRoiItem
{
    Q_OBJECT
public:
   explicit XvDisplayRotateRectRoi(QPointF centerPos,double len1=200,double len2=150,double angle=0, QObject* parent=nullptr);

    // QGraphicsItem interface
public:
    int roiType() const override { return RoiTypeRotateRect;}
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // XvDisplayBaseRoiItem interface
protected:
   bool updateRoi(XvDisplayControlItem *controlItem) override;
protected:
    double  m_len1;
    double  m_len2;
    double  m_angle;

    QPointF m_pt1;
    QPointF m_pt2;
    QPointF m_pt3;
    QPointF m_pt4;
    QPointF m_ptArrow;//箭头点

    XvDisplayControlItem* m_controlItem1=nullptr;//控制点1
    XvDisplayControlItem* m_controlItem2=nullptr;//控制点2
    XvDisplayControlItem* m_controlItem3=nullptr;//控制点3
    XvDisplayControlItem* m_controlItem4=nullptr;//控制点4
};



#endif // XVDISPLAYROTATERECTROI_H
