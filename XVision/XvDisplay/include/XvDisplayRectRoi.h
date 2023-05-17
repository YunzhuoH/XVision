#ifndef XVDISPLAYRECTROI_H
#define XVDISPLAYRECTROI_H

#include "XvDisplayBaseRoiItem.h"

#define RoiTypeRect     1

class XVDISPLAY_EXPORT XvDisplayRectRoi:public XvDisplayBaseRoiItem
{
    Q_OBJECT
public:
   explicit XvDisplayRectRoi(QPointF centerPos,double width=200,double height=150, QObject* parent=nullptr);

    // QGraphicsItem interface
public:
    int roiType() const override { return RoiTypeRect;}
    QRectF boundingRect() const override { return m_rectF;};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // XvDisplayBaseRoiItem interface
protected:
   bool updateRoi(XvDisplayControlItem *controlItem) override;
protected:
    QRectF  m_rectF;//当前矩形
    XvDisplayControlItem* m_rectControlItem=nullptr;//控制点

};

#endif // XVDISPLAYRECTROI_H
