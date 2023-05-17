#include "XvDisplayScene.h"
#include "XvDisplayView.h"
#include "XvDisplayImageItem.h"
#include "XvDisplayBaseRoiItem.h"

#include <QGraphicsItem>

/*******************************/
//* [XvDisplayScenePrivate]
/*******************************/

class XvDisplayScenePrivate
{
    Q_DISABLE_COPY(XvDisplayScenePrivate)
    Q_DECLARE_PUBLIC(XvDisplayScene)

public:
    XvDisplayScenePrivate(XvDisplayScene *q):q_ptr(q)
    {
        roiDrawing=false;
    };
    virtual ~XvDisplayScenePrivate(){};

public:
    XvDisplayScene              *const q_ptr;
    bool                        roiDrawing;
};

/*******************************/
//* [XvDisplayScene]
/*******************************/
XvDisplayScene::XvDisplayScene(XvDisplayView *parView)
    :QGraphicsScene(parView),
    m_parView(parView),
    m_displayImageItem(new XvDisplayImageItem(this)),
    d_ptr(new XvDisplayScenePrivate(this))
{
    m_parView->setScene(this);
    setDisplayImageItem(m_displayImageItem);
}

XvDisplayScene::~XvDisplayScene()
{

}


bool XvDisplayScene::displayImage(const QImage &image,bool bAutoFit)
{
    if(!m_displayImageItem) return false;
    emit sgUpdataDisplayImage(image);
    auto bRet= m_displayImageItem->displayImage(image);
    if(!bRet) return false;
    m_parView->updateDisplayFit();//更新父视图图像适合尺寸
    if(bAutoFit)
    {
        m_parView->zoomToDisplayFit();
    }
    return true;
}

void XvDisplayScene::clearImage()
{
    if(!m_displayImageItem) return;
    m_displayImageItem->clearImage();
    emit sgClearDisplayImage();
}

void XvDisplayScene::addDisplayText(const QString &text,const QPointF &pt, const double &size, const QColor &color,const bool &clear)
{
    if(!m_displayImageItem) return;
    m_displayImageItem->addDisplayText(text,pt,size,color,clear);
}


void XvDisplayScene::clearDisplayText()
{
    if(!m_displayImageItem) return;
    m_displayImageItem->clearDisplayText();
}

QPixmap XvDisplayScene::getDisplayImage()
{
    return m_displayImageItem->pixmap();
}

QSize XvDisplayScene::getDisplayImageSize() const
{
    return m_displayImageItem->getDisplayImageSize();
}

void XvDisplayScene::setRoiDrawing(const bool &drawing)
{
    Q_D(XvDisplayScene);
    d->roiDrawing=drawing;

    foreach (auto roi, m_lstRoiItems)
    {
        roi->setMoveAble(drawing);
        roi->setUpdateAble(drawing);
        roi->setFlagByDrawing(drawing);
    }

}
///是否正在绘制Roi
bool XvDisplayScene::roiDrawing() const
{
    Q_D(const XvDisplayScene);
    return d->roiDrawing;
}

void XvDisplayScene::addRoi(XvDisplayBaseRoiItem *roi)
{
    if(!roi) return;
    if(!m_lstRoiItems.contains(roi))
    {
       m_lstRoiItems.append(roi);
       roi->setParScene(this);
       roi->setParent(this);
       this->addItem(roi);
    }
}

bool XvDisplayScene::removeRoi(XvDisplayBaseRoiItem *roi)
{
    if(!roi) return false;
    this->removeItem(roi);
    if(m_lstRoiItems.contains(roi))
    {
       m_lstRoiItems.removeOne(roi);
    }
    return true;
}

void XvDisplayScene::clearRoi()
{
    foreach (auto roi, m_lstRoiItems)
    {
        this->removeRoi(roi);
    }
}

QList<XvDisplayBaseRoiItem*> XvDisplayScene::getSelectRois() const
{
    QList<XvDisplayBaseRoiItem*> lst;
    foreach (auto roi, m_lstRoiItems)
    {
       if(roi->isSelected())
       {
           lst.append(roi);
       }
    }
    return lst;
}

void XvDisplayScene::setRoiVisible(const bool &visible)
{
    foreach (auto roi, m_lstRoiItems)
    {
       roi->setVisible(visible);
    }
}

void XvDisplayScene::setDisplayImageItem(XvDisplayImageItem *imageItem)
{
    //先删除 确保图像图元唯一性
    foreach (auto item, this->items())
    {
        if(item->type()==XvDisplayImageItem::Type)
        {
            this->removeItem(item);
        }
    }
    this->addItem(imageItem);
    if(m_displayImageItem!=imageItem)
    {
        m_displayImageItem=imageItem;
    }
}

void XvDisplayScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sgMousePress(event);
    return QGraphicsScene::mousePressEvent(event);
}

void XvDisplayScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit sgMouseRelease(event);
    return QGraphicsScene::mouseReleaseEvent(event);
}

