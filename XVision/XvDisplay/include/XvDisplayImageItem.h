/********************************************************
*XvDisplayImageItem:显示图像Item
********************************************************/
#ifndef XVDISPLAYIMAGEITEM_H
#define XVDISPLAYIMAGEITEM_H

#include "XvDisplayGlobal.h"
#include <QPen>
#include <QGraphicsPixmapItem>
#define XvDisplayImageItem_Type  XvGraphicsItemUserType+1
class XvDisplayImageItemPrivate;
class XVDISPLAY_EXPORT XvDisplayImageItem :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    Q_PROPERTY(bool centerCrossShow READ centerCrossShow WRITE setCenterCrossShow)
    Q_PROPERTY(QPen centerCrossPen READ centerCrossPen WRITE setCenterCrossPen)
    Q_PROPERTY(QColor centerCrossColor READ centerCrossColor WRITE setCenterCrossColor)

    friend class XvDisplayScene;
public:
    explicit XvDisplayImageItem(QObject *parent = nullptr);
    ~XvDisplayImageItem();

public:
    //显示中心十字画笔
    bool centerCrossShow() const;
    //设置显示中心十字画笔
    void setCenterCrossShow(const bool &show);

    //中心十字画笔
    QPen centerCrossPen() const;
    //设置中心十字画笔
    void setCenterCrossPen(const QPen &pen);

    //中心十字颜色
    QColor centerCrossColor() const;
    //设置中心十字颜色
    void setCenterCrossColor(const QColor &color);
protected:
    ///显示图像
    bool displayImage(const QImage &image);
    ///清除图像
    void clearImage();
    ///显示文本
    void addDisplayText(const QString &text,const QPointF &pt=QPointF(0,0),const double &size=1,const QColor &color=QColor(Qt::green),const bool &clear=false);
    ///清除文本
    void clearDisplayText();
public:
    enum { Type = XvDisplayImageItem_Type };
    int type() const override
    {
        return Type;
    }
    ///获取图像尺寸
    QSize getDisplayImageSize() const { return this->pixmap().size();}
    ///获取图像显示总线
    QPointF getDisplayImageCenter() const;
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
signals:
    ///hover图像坐标
    void sgHoverImagePosition(const QPoint &pt);
    ///hover离开
    void sgHoverLeave();
protected:
    const QScopedPointer<XvDisplayImageItemPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(XvDisplayImageItem)





};
#endif // XVDISPLAYIMAGEITEM_H
