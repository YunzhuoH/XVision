#include "XvDisplayBaseRoiItem.h"
#include "XvDisplayScene.h"

#include <QPainter>

/*******************************/
//* [XvDisplayBaseRoiItemPrivate]
/*******************************/

class XvDisplayBaseRoiItemPrivate
{
    Q_DISABLE_COPY(XvDisplayBaseRoiItemPrivate)
    Q_DECLARE_PUBLIC(XvDisplayBaseRoiItem)

public:
    XvDisplayBaseRoiItemPrivate(XvDisplayBaseRoiItem *q):q_ptr(q)
    {
        roiColor=RoiColor_Default;
        roiLineWidth=RoiLineWidth_Default;
        roiSelectColor=RoiSelectColor_Default;
        moveAble=true;
        updateAble=true;
    };
    virtual ~XvDisplayBaseRoiItemPrivate(){};
public:
    XvDisplayBaseRoiItem              *const q_ptr;
    bool                              moveAble;//可移动
    bool                              updateAble;//可更新

    QColor                            roiColor; //ROI颜色
    QColor                            roiSelectColor; //ROI选中颜色
    int                               roiLineWidth;//ROI线宽
};


/*******************************/
//* [XvDisplayBaseRoiItem]
/*******************************/

XvDisplayBaseRoiItem::XvDisplayBaseRoiItem(QPointF centerPos, QObject *parent)
    :QObject(parent),
    m_ptCenterPos(centerPos),
    d_ptr(new XvDisplayBaseRoiItemPrivate(this))
{
    setHandlesChildEvents(false);
    setFlags(ItemIsSelectable|ItemIsFocusable);
    m_centerControlItem=new XvDisplayControlItem(this,m_ptCenterPos,XvDisplayControlItem::Center,XvDisplayControlItem::Rect);
}

XvDisplayBaseRoiItem::~XvDisplayBaseRoiItem()
{

}

bool XvDisplayBaseRoiItem::moveAble() const
{
    Q_D(const XvDisplayBaseRoiItem);
    return d->moveAble;
}

void XvDisplayBaseRoiItem::setMoveAble(const bool &able)
{
    Q_D(XvDisplayBaseRoiItem);
    d->moveAble=able;
}


bool XvDisplayBaseRoiItem::updateAble() const
{
    Q_D(const XvDisplayBaseRoiItem);
    return d->updateAble;
}

void XvDisplayBaseRoiItem::setUpdateAble(const bool &able)
{
    Q_D(XvDisplayBaseRoiItem);
    d->updateAble=able;
}


QColor XvDisplayBaseRoiItem::roiColor() const
{
    Q_D(const XvDisplayBaseRoiItem);
    return d->roiColor;
}

void XvDisplayBaseRoiItem::setRoiColor(const QColor &color)
{
    Q_D(XvDisplayBaseRoiItem);
    d->roiColor=color;
}

QColor XvDisplayBaseRoiItem::roiSelectColor() const
{
    Q_D(const XvDisplayBaseRoiItem);
    return d->roiSelectColor;
}

void XvDisplayBaseRoiItem::setRoiSelectColor(const QColor &color)
{
    Q_D(XvDisplayBaseRoiItem);
    d->roiSelectColor=color;
}

int XvDisplayBaseRoiItem::roiLineWidth() const
{
    Q_D(const XvDisplayBaseRoiItem);
    return d->roiLineWidth;
}

void XvDisplayBaseRoiItem::setRoiLineWidth(const int &width)
{
    Q_D(XvDisplayBaseRoiItem);
    d->roiLineWidth=width;
}

void XvDisplayBaseRoiItem::setFlagByDrawing(const bool &drawing)
{
   if(drawing)
   {
       setFlags(flags()|ItemIsSelectable|ItemIsFocusable);
   }
   else
   {
       setFlags(flags()^ItemIsSelectable^ItemIsFocusable);
   }

}

void XvDisplayBaseRoiItem::setParScene(XvDisplayScene *parScene)
{
    m_parScene=parScene;
}

void XvDisplayBaseRoiItem::focusInEvent(QFocusEvent *event)
{
    foreach (auto ctrItem, m_lstControlItem)
    {
        ctrItem->setVisible(true);
    }
}

void XvDisplayBaseRoiItem::focusOutEvent(QFocusEvent *event)
{
    foreach (auto ctrItem, m_lstControlItem)
    {
        ctrItem->setVisible(false);
    }
}

bool XvDisplayBaseRoiItem::moveRoiByOffset(const QPointF &offset)
{
    Q_D(XvDisplayBaseRoiItem);
    if(!d->moveAble)
    {
        return false;
    }
    this->moveBy(offset.x(),offset.y());
    return true;
}

bool XvDisplayBaseRoiItem::updateRoi(XvDisplayControlItem *controlItem)
{
    Q_D(XvDisplayBaseRoiItem);
    return d->updateAble;
}

void XvDisplayBaseRoiItem::addControlItem(XvDisplayControlItem *item)
{
    if(!m_lstControlItem.contains(item))
    {
        m_lstControlItem.append(item);
    }
}

void XvDisplayBaseRoiItem::updatePainter(QPainter *painter)
{
    QPen pen=painter->pen();
    if(this->isSelected())
    {
        pen.setColor(roiSelectColor());
    }
    else
    {
        pen.setColor(roiColor());
    }
    pen.setWidth(roiLineWidth());
    painter->setPen(pen);
}
