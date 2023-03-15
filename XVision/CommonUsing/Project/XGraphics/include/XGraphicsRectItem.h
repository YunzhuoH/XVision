#ifndef XNODEVFUNCRECT_H
#define XNODEVFUNCRECT_H

#include "XGraphicsItem.h"

///矩形Item风格
struct SXRectItemConfig
{
    SXRectItemConfig()
    {
        rRoundedRect=5;

        penItemRect.setColor(QColor(25, 150, 255));
        penItemRect.setWidth(3);
        brushItemRect=QBrush(QColor(Qt::white));

        penSelectRect.setColor(QColor(255, 150, 50));
        penSelectRect.setWidth(5);
        brushSelectRect=QBrush(QColor(Qt::white));

        penSelectBoundingRect.setColor(Qt::white);
        penSelectBoundingRect.setWidth(1);
        penSelectBoundingRect.setStyle(Qt::DashLine);

        rConnectRectSize=20;
    }

    ///矩形圆角大小
    double rRoundedRect;

    ///常规矩形画笔
    QPen penItemRect;
    ///常规矩形笔刷
    QBrush brushItemRect;

    ///选中时矩形画笔
    QPen penSelectRect;
    ///选中时矩形笔刷
    QBrush brushSelectRect;

    ///选中时边框画笔
    QPen penSelectBoundingRect;

    ///连接矩形尺寸
    double rConnectRectSize;

};
///pixmap偏移
#define PIX_OFFSET 10
class XGRAPHICS_PUBLIC XGraphicsRectItem:public XGraphicsItem,public QGraphicsRectItem
{
    Q_OBJECT
public:
    XGraphicsRectItem(QObject *parent = nullptr);
    XGraphicsRectItem(QString type,QString id,QObject *parent = nullptr);
    ~XGraphicsRectItem();
    // XGraphicsItem interface
protected:
    ///初始化Item
    void initItem() override;
    ///初始化连接映射
    void initConnectArea() override;
    ///添加连接的矩形框
    void addConnectRect(const QString &key, const QPointF &pt);
    ///绘制文本
    void drawItemText(QPainter *painter,const QString &text,const QRectF &rect);
    ///绘制图标
    void drawItemPix(QPainter *painter, SXItemPixData* data,double widthOffset);

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

    void setText(const QString &text) override;
    void setTip(const QString &tip) override;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

public:
    ///配置
    SXRectItemConfig* config()
    {
        return &m_config;
    }
protected:
    ///Item配置
    SXRectItemConfig m_config;

    ///节点中心、上下左右中心位置
    QPointF   m_ptCenter, m_ptLeft, m_ptRight, m_ptTop, m_ptBottom;

    ///连接区域矩形
    struct SConnectRect
    {
        SConnectRect() {}
        SConnectRect(const QString &_key,const QPointF &_pt,const QRectF &_rect)
            :rect(_rect)
        {
            data.key=_key;
            data.pt=_pt;
            data.area.clear();
            data.area.addRect(_rect);
        }
        ///连接数据
        SConnectData data;
        ///连接矩形
        QRectF rect;
    };

    ///连接矩形区域
    QMap<QString,SConnectRect> m_mapConnectRectArea;


};

#endif // XNODEVFUNCRECT_H
