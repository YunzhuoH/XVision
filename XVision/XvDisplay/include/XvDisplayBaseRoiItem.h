#ifndef XVDISPLAYBASEROIITEM_H
#define XVDISPLAYBASEROIITEM_H

#include "XvDisplayGlobal.h"

#include <QObject>
#include <QGraphicsItemGroup>
#include "XvDisplayControlItem.h"

#define XvDisplayRoiItem_Type XvGraphicsItemUserType+2
#define RoiTypeBase     0
#define RoiColor_Default  Qt::green
#define RoiSelectColor_Default  Qt::yellow
#define RoiLineWidth_Default  1

class XvDisplayScene;
class XvDisplayBaseRoiItemPrivate;
class XVDISPLAY_EXPORT XvDisplayBaseRoiItem: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(bool moveAble READ moveAble WRITE setMoveAble)
    Q_PROPERTY(bool updateAble READ updateAble WRITE setUpdateAble)

    Q_PROPERTY(QColor roiColor READ roiColor WRITE setRoiColor)
    Q_PROPERTY(QColor roiSelectColor READ roiSelectColor WRITE setRoiSelectColor)
    Q_PROPERTY(int roiLineWidth READ roiLineWidth WRITE setRoiLineWidth)
    friend class XvDisplayControlItem;
public:
    explicit  XvDisplayBaseRoiItem(QPointF centerPos,QObject* parent=nullptr);
    virtual ~XvDisplayBaseRoiItem();
public:
    enum { Type = XvDisplayRoiItem_Type };
    int type() const override
    {
        return Type;
    }
    ///roi类型
    virtual int roiType() const =0;
public:
    ///ROI移动使能
    bool moveAble() const;
    ///设置ROI移动使能
    void setMoveAble(const bool &able);

    ///ROI更新使能
    bool updateAble() const;
    ///设置ROI更新使能
    void setUpdateAble(const bool &able);

    ///ROI颜色
    QColor roiColor() const;
    ///设置ROI颜色
    void setRoiColor(const QColor &color);

    ///ROI选中颜色
    QColor roiSelectColor() const;
    ///设置ROI选中颜色
    void setRoiSelectColor(const QColor &color);

    ///ROI颜色
    int roiLineWidth() const;
    ///设置ROI颜色
    void setRoiLineWidth(const int &width);

    ///设置绘制时的flag
    virtual void setFlagByDrawing(const bool &drawing);
    ///设置父场景
    void setParScene(XvDisplayScene* parScene);
    ///获取父场景
    XvDisplayScene* parScene() const
    {
        return m_parScene;
    }
    // QGraphicsItem interface
protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;
protected:
    ///移动Roi
    virtual bool moveRoiByOffset(const QPointF &offset);
    ///更新Roi
    virtual bool updateRoi(XvDisplayControlItem* controlItem);
    ///添加控制点
    void addControlItem(XvDisplayControlItem* item);

    ///更新画笔颜色
    void updatePainter(QPainter *painter);
protected:
    XvDisplayScene* m_parScene=nullptr;
    QList<XvDisplayControlItem*> m_lstControlItem;

    XvDisplayControlItem* m_centerControlItem=nullptr;//中心点
    QPointF    m_ptCenterPos; //坐标

protected:
    const QScopedPointer<XvDisplayBaseRoiItemPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(XvDisplayBaseRoiItem)
};

#endif // XVDISPLAYBASEROIITEM_H
