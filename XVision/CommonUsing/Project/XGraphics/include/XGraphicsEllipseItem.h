#ifndef XGRAPHICSELLIPSEITEM_H
#define XGRAPHICSELLIPSEITEM_H

#include "XGraphicsItem.h"
#include "CommonUtils.h"

///椭圆Item风格
struct SXEllipseItemConfig
{
    SXEllipseItemConfig()
    {


        penItemEllipse.setColor(QColor(25, 150, 255));
        penItemEllipse.setWidth(3);
        brushItemEllipse=QBrush(QColor(Qt::white));

        penSelectEllipse.setColor(QColor(255, 150, 50));
        penSelectEllipse.setWidth(5);
        brushSelectEllipse=QBrush(QColor(Qt::white));

        penSelectBoundingEllipse.setColor(Qt::white);
        penSelectBoundingEllipse.setWidth(1);
        penSelectBoundingEllipse.setStyle(Qt::DashLine);

        rConnectEllipseSize=10;
    }


    ///常规椭圆画笔
    QPen penItemEllipse;
    ///常规椭圆笔刷
    QBrush brushItemEllipse;

    ///选中时矩形画笔
    QPen penSelectEllipse;
    ///选中时矩形笔刷
    QBrush brushSelectEllipse;

    ///选中时边框画笔
    QPen penSelectBoundingEllipse;

    ///连接椭圆环尺寸
    double rConnectEllipseSize;

};

class XGRAPHICS_PUBLIC XGraphicsEllipseItem:public XGraphicsItem,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    XGraphicsEllipseItem(QObject *parent = nullptr);
    XGraphicsEllipseItem(QString type,QString id,QObject *parent = nullptr);
    ~XGraphicsEllipseItem();
    // XGraphicsItem interface
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

public:
    ///配置
    SXEllipseItemConfig* config()
    {
        return &m_config;
    }
protected:
    ///Item配置
    SXEllipseItemConfig m_config;

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


};

#endif // XGRAPHICSELLIPSEITEM_H
