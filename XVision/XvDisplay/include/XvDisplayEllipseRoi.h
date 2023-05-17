#ifndef XVDISPLAYELLIPSEROI_H
#define XVDISPLAYELLIPSEROI_H

#include "XvDisplayRotateRectRoi.h"

#define RoiTypeEllipse     4

class XVDISPLAY_EXPORT XvDisplayEllipseRoi:public XvDisplayRotateRectRoi
{
    Q_OBJECT
public:
   explicit XvDisplayEllipseRoi(QPointF centerPos,double len1=200,double len2=150,double angle=0, QObject* parent=nullptr);

    // QGraphicsItem interface
public:
    int roiType() const override { return RoiTypeEllipse;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


};




#endif // XVDISPLAYELLIPSEROI_H
