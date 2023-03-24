#ifndef XNODEVFUNCRECT_H
#define XNODEVFUNCRECT_H

#include "XGraphicsItem.h"

class XGraphicsRectItemPrivate;
///pixmap偏移
#define PIX_OFFSET 10
class XGRAPHICS_PUBLIC XGraphicsRectItem:public XGraphicsItem,public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(double rectRounded READ rectRounded WRITE setRectRounded)
    Q_PROPERTY(double connectRectSize READ connectRectSize WRITE setConnectRectSize)
    Q_PROPERTY(QPen itemRectPen READ itemRectPen WRITE setItemRectPen)
    Q_PROPERTY(QBrush itemRectBrush READ itemRectBrush WRITE setItemRectBrush)
    Q_PROPERTY(QPen selectRectPen READ selectRectPen WRITE setSelectRectPen)
    Q_PROPERTY(QBrush selectRectBrush READ selectRectBrush WRITE setSelectRectBrush)
    Q_PROPERTY(QPen selectBoundingRectPen READ selectBoundingRectPen WRITE setSelectBoundingRectPen)
public:
    XGraphicsRectItem(QObject *parent = nullptr);
    XGraphicsRectItem(QString type,QString id,QObject *parent = nullptr);
    ~XGraphicsRectItem();
public:
 //*[属性接口]*
    ///矩形圆角大小
    double rectRounded() const;
    ///设置矩形圆角大小
    void setRectRounded(const double &rounded);

    ///连接矩形尺寸
    double connectRectSize() const;
    ///设置连接矩形尺寸
    void setConnectRectSize(const double &size);

    ///常规矩形画笔
    QPen itemRectPen() const;
    ///设置常规矩形画笔
    void setItemRectPen(const QPen &pen);

    ///常规矩形笔刷
    QBrush itemRectBrush() const;
    ///设置常规矩形笔刷
    void setItemRectBrush(const QBrush &brush);

    ///选中时矩形画笔
    QPen selectRectPen() const;
    ///设置选中时矩形画笔
    void setSelectRectPen(const QPen &pen);

    ///选中时矩形笔刷
    QBrush selectRectBrush() const;
    ///设置选中时矩形笔刷
    void setSelectRectBrush(const QBrush &brush);

    ///选中时边框画笔
    QPen selectBoundingRectPen() const;
    ///设置选中时边框画笔
    void setSelectBoundingRectPen(const QPen &pen);

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

protected:

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
protected:
    const QScopedPointer<XGraphicsRectItemPrivate> d_ptr;
private:
     Q_DECLARE_PRIVATE(XGraphicsRectItem)

};

#endif // XNODEVFUNCRECT_H
