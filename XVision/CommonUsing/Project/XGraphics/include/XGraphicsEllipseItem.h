#ifndef XGRAPHICSELLIPSEITEM_H
#define XGRAPHICSELLIPSEITEM_H

#include "XGraphicsItem.h"
#include "XGraphicsUtils.h"

class XGraphicsEllipseItemPrivate;
class XGRAPHICS_PUBLIC XGraphicsEllipseItem:public XGraphicsItem,public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QPen itemEllipsePen READ itemEllipsePen WRITE setItemEllipsePen)
    Q_PROPERTY(QBrush itemEllipseBrush READ itemEllipseBrush WRITE setItemEllipseBrush)
    Q_PROPERTY(QPen selectEllipsePen READ selectEllipsePen WRITE setSelectEllipsePen)
    Q_PROPERTY(QBrush selectEllipseBrush READ selectEllipseBrush WRITE setSelectEllipseBrush)
    Q_PROPERTY(QPen selectBoundingEllipsePen READ selectBoundingEllipsePen WRITE setSelectBoundingEllipsePen)
    Q_PROPERTY(double connectEllipseSize READ connectEllipseSize WRITE setConnectEllipseSize)
public:
    XGraphicsEllipseItem(QObject *parent = nullptr);
    XGraphicsEllipseItem(QString type,QString id,QObject *parent = nullptr);
    ~XGraphicsEllipseItem();
    // XGraphicsItem interface
public:
 //*[属性接口]*
    ///常规椭圆画笔
    QPen itemEllipsePen() const;
    ///设置常规椭圆画笔
    void setItemEllipsePen(const QPen &pen);

    ///常规常规椭圆笔刷
    QBrush itemEllipseBrush() const;
    ///设置常规椭圆笔刷
    void setItemEllipseBrush(const QBrush &brush);

    ///选中时矩形画笔
    QPen selectEllipsePen() const;
    ///设置选中时矩形画笔
    void setSelectEllipsePen(const QPen &pen);

    ///选中时矩形笔刷
    QBrush selectEllipseBrush() const;
    ///设置选中时矩形笔刷
    void setSelectEllipseBrush(const QBrush &brush);

    ///选中时边框画笔
    QPen selectBoundingEllipsePen() const;
    ///设置选中时边框画笔
    void setSelectBoundingEllipsePen(const QPen &pen);


    ///连接椭圆环尺寸
    double connectEllipseSize() const;
    ///设置连接椭圆环尺寸
    void setConnectEllipseSize(const double &size);
protected:
    ///初始化Item
    void initItem() override;
    ///初始化连接映射
    void initConnectArea() override;

    ///绘制文本
    void drawItemText(QPainter *painter,const QString &text,const QRectF &rect);
    ///绘制图标
    void drawItemPix(QPainter *painter, SXItemPixData* data,const QRectF &rect);

    ///设置提示
    inline void setItemToolTip();

    // XGraphicsItem interface
public:
    void updateShape() override;
    QGraphicsItem *item() override;

    bool isInConnectArea(const QPointF &sPt) override;
    bool hasConnectKey(const QString &key) override;
    bool getConnectData(const QString &key, SConnectData &connData) override;
    bool getConnectData(const QPointF &sPt, SConnectData &connData) override;
    bool getFatherConnectData(XGraphicsConnectLink *fatherLink, SConnectData &connData) override;
    bool getSonConnectData(XGraphicsConnectLink *sonLink, SConnectData &connData) override;

    void setText(const QString &text) override;
    void setTip(const QString &tip) override;


    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

protected:

    ///椭圆中心点
    QPointF m_ptCenter;
    ///椭圆x,y半径
    double m_rRadiusX,m_rRadiusY;

    ///连接椭圆环
    struct SConnectEllipseRing
    {
        SConnectEllipseRing() {}
        SConnectEllipseRing(const QString &_key,const QPointF &_ptCenter,const double &_rx,const double &_ry,const double &_thickness)
        {
            data.key=_key;
            data.pt=_ptCenter;
            updateEllipseRing(_ptCenter,_rx,_ry,_thickness);
        }
        ///连接数据
        SConnectData data;

        ///圆环中心
        QPointF ptCenter;
        ///连接椭圆环dx
        double rx;
        ///连接椭圆环dy
        double ry;
        ///椭圆环厚度
        double thickness;

        void updateEllipseRing(const QPointF &_ptCenter,const double &_rx,const double &_ry,const double &_thickness)
        {
            ptCenter=_ptCenter;
            rx=_rx;
            ry=_ry;
            thickness=_thickness;
            data.area.clear();
            data.area.addPath(genEllipseRing(ptCenter,rx,ry,thickness));
        }
    };

    ///连接椭圆环区域
    SConnectEllipseRing m_connectEllipseRingArea;

protected:
    const QScopedPointer<XGraphicsEllipseItemPrivate> d_ptr;
private:
     Q_DECLARE_PRIVATE(XGraphicsEllipseItem)
};

#endif // XGRAPHICSELLIPSEITEM_H
