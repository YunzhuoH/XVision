/********************************************************
*XvDisplayControlItem:Roi控制点
********************************************************/
#ifndef XVDISPLAYCONTROLITEM_H
#define XVDISPLAYCONTROLITEM_H

#include "XvDisplayGlobal.h"

#include <QObject>
#include <QAbstractGraphicsShapeItem>

#define ControlSize_Default 20
#define ControlColor_Default  Qt::blue

class XvDisplayBaseRoiItem;
class XVDISPLAY_EXPORT XvDisplayControlItem:public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
    Q_PROPERTY(int controlSize READ controlSize WRITE setControlSize)
    Q_PROPERTY(QColor controlColor READ controlColor WRITE setControlColor)
public:
    enum ShapeType
    {
        Rect=0,//矩形
        Circle=1,//圆形
    };
    enum ControlType
    {
        Center=0,//中心点
        Control=1,//操作点
    };

public:
    explicit XvDisplayControlItem(XvDisplayBaseRoiItem* parRoi, QPointF pt,ControlType controlType,ShapeType shapeType=ShapeType::Rect);
    ~XvDisplayControlItem();
public:
    ///更新位置
    void updatePos(const QPointF &pos);
    ///获取位置
    QPointF getPos() const { return m_ptPos; }
public:
    ///控制点尺寸
    int controlSize() const { return m_nControlSize;}
    ///设置控制点尺寸
    void setControlSize(const int &size) { m_nControlSize=size;}

    ///控制点颜色
    QColor controlColor() const { return m_controlColor;}
    ///设置控制点颜色
    void setControlColor(const QColor &color);

    ///形状类型
    ShapeType shapeType() const { return m_eShapeType; }
    ///设置形状类型
    void setShapeType(const ShapeType &type) { m_eShapeType=type;}
public:
    QRectF boundingRect() const override;
protected:
    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    ControlType  m_eControlType;//控制点类型
    ShapeType m_eShapeType;//控制点形状
    int     m_nControlSize;//控制点尺寸
    QColor  m_controlColor; //控制点颜色
    QPointF m_ptPos;//坐标位置
    QPointF m_ptLastPos;//最后一次的坐标位置
    XvDisplayBaseRoiItem* m_parRoi=nullptr;//父Roi

};



#endif // XVDISPLAYCONTROLITEM_H
