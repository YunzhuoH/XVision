#include "XGraphicsScene.h"

#include <QGraphicsSceneEvent>
#include <QKeyEvent>

#include "XGraphicsItem.h"
#include "XGraphicsMimeData.h"
#include "XGraphicsUtils.h"

/****************************构建与析构****************************/

XGraphicsScene::XGraphicsScene(QObject *parent)
   :QGraphicsScene(parent),
   m_pView(new XGraphicsView(this))
{
    m_pView->setScene(this);
    m_pView->setAcceptDrops(true);
    m_pView->installEventFilter(this);
    m_mapXItem.clear();
    m_mapXLink.clear();
}

XGraphicsScene::~XGraphicsScene()
{

}


/****************************常规公共接口****************************/

XGraphicsView *XGraphicsScene::getView()
{
    if (m_pView == nullptr) {
        m_pView = new XGraphicsView(this);
        return m_pView;
    }
    return m_pView;
}

void XGraphicsScene::setXItemDelegateFactory(XGraphicsItemDelegateFactory* factory)
{
    m_pXItemFactory=factory;
    m_pXItemFactory->setScene(this);
}

void XGraphicsScene::setXLinkDelegateFactory(XGraphicsLinkDelegateFactory *factory)
{
    m_pXLinkFactory=factory;
    m_pXLinkFactory->setScene(this);
}

void XGraphicsScene::setDisplayRect(const QRectF &rect)
{
    this->setSceneRect(rect);
    this->getView()->setSceneRect(rect);
}

void XGraphicsScene::zoomToItemRect()
{
    if(this->items().count()<1)
    {
        return;
    }
    auto rect= itemsBoundingRect();
    getView()->zoomToRect(rect);
}


/****************************XItem字典****************************/

void XGraphicsScene::addXItem(XGraphicsItem *xItem)
{
    if(!xItem) return;
    if(!xItem->item()) return;
    if(!m_mapXItem.contains(xItem->itemId()))
    {
       m_mapXItem.insert(xItem->itemId(),xItem);
       xItem->setParScene(this);
       xItem->setParent(this);
       this->addItem(xItem->item());
       connect(xItem,&XGraphicsItem::posChanged,this,&XGraphicsScene::onXItemPosChanged);
       connect(xItem,&XGraphicsItem::shapeChanged,this,&XGraphicsScene::onXItemShapeChanged);
       emit xItemAdd(xItem);
    }
}

void XGraphicsScene::removeXItem(XGraphicsItem *xItem)
{
    if(!xItem) return;
    if(!xItem->item()) return;
    this->removeItem(xItem->item());
    if(m_mapXItem.contains(xItem->itemId()))
    {
       m_mapXItem.remove(xItem->itemId());
    }
    disconnect(xItem,&XGraphicsItem::posChanged,this,&XGraphicsScene::onXItemPosChanged);
    disconnect(xItem,&XGraphicsItem::shapeChanged,this,&XGraphicsScene::onXItemShapeChanged);
    emit xItemRemove(xItem);
}

XGraphicsItem *XGraphicsScene::getXItemById(const QString &id)
{
    if(m_mapXItem.contains(id))
    {
        return m_mapXItem[id];
    }
    return nullptr;
}

QList<XGraphicsItem *> XGraphicsScene::getXItemsByType(const QString &type)
{
    QList<XGraphicsItem *> lst;
    foreach (auto xItem, m_mapXItem)
    {
        if(xItem->itemType()==type)
        {
            lst.append(xItem);
        }
    }

    return lst;
}


/****************************XLink字典****************************/

void XGraphicsScene::addXLink(XGraphicsConnectLink *xLink)
{
    if(!xLink) return;
    if(!m_mapXLink.contains(xLink->linkId()))
    {
       m_mapXLink.insert(xLink->linkId(),xLink);
       xLink->setParScene(this);
       xLink->setParent(this);
       this->addItem(xLink);
       connect(xLink,&XGraphicsConnectLink::xLinkError,this,&XGraphicsScene::onXLinkError);
       emit xLinkAdd(xLink);
    }
}

void XGraphicsScene::removeXLink(XGraphicsConnectLink *xLink)
{
     if(!xLink) return;
     this->removeItem(xLink);
     if(m_mapXLink.contains(xLink->linkId()))
     {
        m_mapXLink.remove(xLink->linkId());
     }
     disconnect(xLink,&XGraphicsConnectLink::xLinkError,this,&XGraphicsScene::onXLinkError);
     emit xLinkRemove(xLink);
}

XGraphicsConnectLink *XGraphicsScene::getXLinkById(const QString &id)
{
    if(m_mapXLink.contains(id))
    {
        return m_mapXLink[id];
    }
    return nullptr;
}

void XGraphicsScene::clearXItemAndXLink()
{
    //先移除XLink
    foreach (auto xLink, m_mapXLink)
    {
        this->removeXLink(xLink);
        xLink->deleteLater();
        xLink=nullptr;
    }
    //再移除XItem
    foreach (auto xItem, m_mapXItem)
    {
        this->removeXItem(xItem);
        xItem->deleteLater();
        xItem=nullptr;
    }
}


/****************************槽函数****************************/

void XGraphicsScene::onXItemPosChanged()
{
    auto obj=sender();
    auto xItem=qobject_cast<XGraphicsItem*>(obj);
    if(xItem)
    {
        emit xItemPosChanged(xItem);
    }
}

void XGraphicsScene::onXItemShapeChanged()
{
    auto obj=sender();
    auto xItem=qobject_cast<XGraphicsItem*>(obj);
    if(xItem)
    {
        emit xItemShapeChanged(xItem);
    }
}

void XGraphicsScene::onXLinkError()
{
    auto obj=sender();
    auto xLink=qobject_cast<XGraphicsConnectLink*>(obj);
    if(xLink)
    {
        removeXLink(xLink);
        xLink->deleteLater();
        xLink=nullptr;
    }
}


/****************************场景事件****************************/

//*[拖动]*
void XGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->source() == m_pView) {
        event->ignore();
        return QGraphicsScene::dragEnterEvent(event);
    }
    m_pTempDragXItem = nullptr;
    event->accept();
}

void XGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (m_pTempDragXItem == nullptr)
    {
       if(m_pXItemFactory==nullptr)//item工厂为空情况下转换mimedata
       {
           XGraphicsMimeData* mineData=(XGraphicsMimeData*)(event->mimeData());
           if(mineData==nullptr) return;
           m_pTempDragXItem=mineData->xItem();
           if(m_pTempDragXItem)
           {
               this->addXItem(m_pTempDragXItem);
           }
       }
       else //item工厂不为空
       {
          QString type = event->mimeData()->text();
          m_pTempDragXItem=m_pXItemFactory->getXGraphicsItem(type);
          if(m_pTempDragXItem)
          {
              this->addXItem(m_pTempDragXItem);
          }
       }
    }
    if (m_pTempDragXItem == nullptr)
        return;
    auto item=m_pTempDragXItem->item();
    if(item)
    {
        auto pos= event->scenePos().toPoint();
        item->setPos(pos);
    }
}

void XGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (m_pTempDragXItem)
    {
        this->removeXItem(m_pTempDragXItem);
        m_pTempDragXItem->deleteLater();
        m_pTempDragXItem = nullptr;
    }
}

void XGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->source() == m_pView) {
        event->ignore();
        return QGraphicsScene::dragEnterEvent(event);
    }
    if(m_pTempDragXItem)
    {
      //不在XItem字典中存在则进行删除,防止内存泄露
      if(!existPtrInXItems(m_pTempDragXItem))
      {
          m_pTempDragXItem->deleteLater();
      }
    }
    m_pTempDragXItem = nullptr;
    event->acceptProposedAction();
}

//*[鼠标]*
void XGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto pt=event->scenePos();
    if (event->button() == Qt::LeftButton)
    {
        m_bMouseLeftPressed=true;
    }
    else if (event->button() == Qt::RightButton)
    {
        m_bMouseRightPressed=true;
    }
    else
    {
        m_bMouseLeftPressed=false;
        m_bMouseRightPressed=false;
    }


    auto xItem=getXItemByPos(pt);
    if(xItem)
    {
        //[0.xItem事件]
        xItem->sceneMousePressEvent(event);
        //[1.画线]
        if(xItem->isInConnectArea(pt))
        {
            SConnectData data;
            if(xItem->getConnectData(pt,data))
            {
                //[进入划线模式]
                m_xLinkTemp=nullptr;
                getView()->setDragMode(QGraphicsView::NoDrag);
                if(m_pXLinkFactory!=nullptr)//存在工厂 使用工厂生成连接线
                {
                   m_xLinkTemp=m_pXLinkFactory->getXGraphicsLink();
                   if(m_xLinkTemp)
                   {
                       m_xLinkTemp->setFatherStartPos(data.pt);
                       m_xLinkTemp->setSonEndPos(data.pt);
                   }
                }

                if(m_xLinkTemp==nullptr)//工厂不存在情况下/工厂返回空则生成新的连接线
                {
                    m_xLinkTemp=new XGraphicsConnectLink(data.pt,data.pt);
                }
                m_xItemTempStartFather=xItem;
                m_strTempStartConnKey=data.key;
                m_xLinkTemp->setLinkState(false);//设置未连接成功
                addXLink(m_xLinkTemp);
                return;
            }
        }
    }



    QGraphicsScene::mousePressEvent(event);
    //[2.左键选择移动图元:绘制磁吸线]
    auto selectXItems=getSelectXItem();
    if(selectXItems.count()==1)//只有一个图元时才选择
    {
        auto xItem=selectXItems[0];
        m_pTempMagneticMoveXItem=xItem;
    }

}

void XGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    auto pt=event->scenePos();
    //[0.xItem事件]
    auto xItem=getXItemByPos(pt);
    if(xItem)
    {
        if(m_pTempMoveXItem) //之前移动到的图元
        {
            if(m_pTempMoveXItem!=xItem) //当前图元不是上一个移动到的图元
            {
                m_pTempMoveXItem->sceneMouseLeaveEvent(event);//设置鼠标离开事件
                m_pTempMoveXItem=xItem;//更新当前移动图元
                m_pTempMoveXItem->sceneMouseEnterEvent(event);//设置鼠标进入事件
            }
        }
        else
        {
            m_pTempMoveXItem=xItem;
            m_pTempMoveXItem->sceneMouseEnterEvent(event);//设置鼠标进入事件

        }
        m_pTempMoveXItem->sceneMouseMoveEvent(event);
    }
    else
    {
        if(m_pTempMoveXItem)
        {
            m_pTempMoveXItem->sceneMouseLeaveEvent(event);
        }
        m_pTempMoveXItem=nullptr;
    }
     //[1.画线]
    if(m_xLinkTemp)///正在绘制连接线则更新位置
    {
        m_xLinkTemp->setSonEndPos(pt);
    }


    //[2.左键选择移动图元:绘制磁吸线]
    if(m_pTempMagneticMoveXItem&&m_bMouseLeftPressed)
    {
        QGraphicsScene::mouseMoveEvent(event);
        drawMagneticLine(m_pTempMagneticMoveXItem,pt);
        emit m_pTempMagneticMoveXItem->posChanged();
        return;
    }

}

void XGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    emit mouseClicked(event);
    auto pt=event->scenePos();

    if (event->button() == Qt::LeftButton)
    {
        m_bMouseLeftPressed=false;
    }
    else if (event->button() == Qt::RightButton)
    {
        if(!getView()->draging())//非拖动情况下
        {
            emit sceneContextMenuRequested(pt.toPoint());
        }
        m_bMouseRightPressed=false;
    }
    else
    {
        m_bMouseLeftPressed=false;
        m_bMouseRightPressed=false;
    }


    //[0.xItem事件]
    auto xItem=getXItemByPos(pt);
    if(xItem)
    {
         xItem->sceneMouseReleaseEvent(event);     
         auto lstSelets= this->getSelectXItem();
         if(lstSelets.count()==1&&lstSelets[0]==xItem)
         {
             emit xItemSingleSelect(xItem);
         }
    }
    //[xLink事件]
    auto xLink=getXLinkByPos(pt);
    if(xLink)
    {
        auto lstSelets=this->getSelectXLink();
        if(lstSelets.count()==1&&lstSelets[0]==xLink)
        {
            emit xLinkSingleSelect(xLink);
        }
    }

     //[1.画线]
    if(m_xLinkTemp&&m_xItemTempStartFather)
    {
        auto xItemLink=getXItemByPos(pt);
        bool bConnectOK=false;
        if(xItemLink)
        {
            if(xItemLink&&xItemLink->isInConnectArea(pt))
            {         
                SConnectData data;
                if(xItemLink->getConnectData(pt,data))
                {                 
                    bool bCantConnectXItem=judgeCantConnectXItem(m_xItemTempStartFather,m_strTempStartConnKey,
                                                                 xItemLink,data.key);
                    if(!bCantConnectXItem)
                    {

                        bool bRetFather=false;
                        bool bRetSon=false;
                        bRetFather=m_xLinkTemp->setFatherXItemKey(m_xItemTempStartFather,m_strTempStartConnKey);
                        bRetSon=m_xLinkTemp->setSonXItemKey(xItemLink,data.key);
                        if(bRetFather&&bRetSon)
                        {
                            m_xLinkTemp->setLinkState(true);//设置连接成功
                            if((m_xLinkTemp->fatherXItem()==m_xLinkTemp->sonXItem())
                                    &&(m_xLinkTemp->fatherKey()==data.key))//起始到结束为同一个节点同一个连接点 则无法连接
                            {
                                bConnectOK=false;

                            }
                            else
                            {
                                bool bCantConnect=judgeCantConnectXLink(m_xLinkTemp);//判断是否不可以连接
                                if(!bCantConnect)
                                {
                                    bConnectOK=true;  //连接成功
                                    m_xLinkTemp->onXItemUpdate();//更新位置
                                    emit xLinkConnectSuccess(m_xLinkTemp);

                                    m_xLinkTemp=nullptr;
                                    m_xItemTempStartFather=nullptr;
                                    m_strTempStartConnKey="";

                                }
                            }
                        }
                        else //设置失败 不生成连接线
                        {
                            bConnectOK=false;
                        }

                    }

                }

            }

        }

        if(!bConnectOK)
        {
            removeXLink(m_xLinkTemp);
            m_xLinkTemp->deleteLater();
            m_xLinkTemp=nullptr;
            m_xItemTempStartFather=nullptr;
            m_strTempStartConnKey="";
        }

    }


    //[2.左键选择移动图元:绘制磁吸线]
    if(m_pTempMagneticMoveXItem)
    {
        m_pTempMagneticMoveXItem=nullptr;

        if (m_itemMagneticHLine) { removeItem(m_itemMagneticHLine); delete m_itemMagneticHLine; m_itemMagneticHLine = nullptr; }
        if (m_itemMagneticVLine) { removeItem(m_itemMagneticVLine); delete m_itemMagneticVLine; m_itemMagneticVLine = nullptr; }
    }

    ///更新线位置
    foreach (auto xlink, m_mapXLink)
    {
        xlink->onXItemUpdate();
    }


}

void XGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
    if(event->button()==Qt::LeftButton)
    {
        auto pt=event->scenePos();
        auto xItem=getXItemByPos(pt);
        if(xItem)
        {
            xItem->sceneMouseDoubleClickEvent(event);
            emit mouseDoubleClickXItem(xItem);
        }
        auto xLink=getXLinkByPos(pt);
        if(xLink)
        {
            emit mouseDoubleClickXLink(xLink);
        }
    }

}

//*[键盘]*
void XGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->clearSelection();
    }
    if (event->key() == Qt::Key_Delete)
    {
        auto items=selectedItems();
        auto xItems=filterQItemToXItem(items);
        auto xLinks=filterGItemToXLink(items);

        //先删除连线
        foreach (auto xLink, xLinks)
        {
            this->removeXLink(xLink);
            xLink->deleteLater();
            xLink=nullptr;
        }
        //再删除item
        foreach (auto xItem, xItems)
        {          
            if(m_pTempMoveXItem&&xItem==m_pTempMoveXItem)
            {
                m_pTempMoveXItem=nullptr;   //防止移动时删除时报错，m_pTempMoveXItem出现野指针。
            }
            if(m_pTempMagneticMoveXItem&&xItem==m_pTempMagneticMoveXItem)
            {
                m_pTempMagneticMoveXItem=nullptr;   //防止移动时删除时报错，m_pTempMagneticMoveXItem出现野指针。
            }
            this->removeXItem(xItem);
            xItem->deleteLater();
            xItem=nullptr;
        }

    }
    return QGraphicsScene::keyPressEvent(event);
}


/****************************公开工具接口****************************/

bool XGraphicsScene::existPtrInXItems(XGraphicsItem *xItem)
{
    foreach (auto ptr, m_mapXItem)
    {
        if(ptr==xItem)
        {
            return true;
        }
    }
    return false;
}

bool XGraphicsScene::existPtrInXLinks(XGraphicsConnectLink *xLink)
{
    foreach (auto ptr, m_mapXLink)
    {
        if(ptr==xLink)
        {
            return true;
        }
    }
    return false;
}

XGraphicsItem *XGraphicsScene::getXItemByPos(const QPointF &pt)
{
    XGraphicsItem* xItemTemp=nullptr;
    auto items=this->items(pt,Qt::IntersectsItemShape, Qt::DescendingOrder);
    foreach (auto item, items)
    {
        auto xItem=qItemtoXItem(item);
        if(xItem)
        {
            xItemTemp=xItem;
            break;
        }
    }
    return xItemTemp;
}

QList<XGraphicsItem *> XGraphicsScene::getSelectXItem()
{
    QList<XGraphicsItem*> lst;
    auto items=this->selectedItems();
    foreach (auto item, items)
    {
        auto xItem=qItemtoXItem(item);
        if(xItem)
        {
            lst.append(xItem);
        }
    }
    return lst;
}

XGraphicsConnectLink *XGraphicsScene::getXLinkByPos(const QPointF &pt)
{
    XGraphicsConnectLink* xLinkTemp=nullptr;
    auto items=this->items(pt,Qt::IntersectsItemShape, Qt::DescendingOrder);
    foreach (auto item, items)
    {
        auto xLink=qItemtoXLink(item);
        if(xLink)
        {
            xLinkTemp=xLink;
            break;
        }
    }
    return xLinkTemp;
}

QList<XGraphicsConnectLink *> XGraphicsScene::getSelectXLink()
{
    QList<XGraphicsConnectLink*> lst;
    auto items=this->selectedItems();
    foreach (auto item, items)
    {
        auto xLink=qItemtoXLink(item);
        if(xLink)
        {
            lst.append(xLink);
        }
    }
    return lst;
}


/****************************内部工具接口****************************/

void XGraphicsScene::drawMagneticLine(XGraphicsItem *xItem,const QPointF &pt)
{
    auto item= xItem->item();
    if(!item) return;
    {
        // 删除上次磁吸线 水平
        if (m_itemMagneticHLine) { removeItem(m_itemMagneticHLine); delete m_itemMagneticHLine; m_itemMagneticHLine = nullptr; }

        // [水平磁吸线]
        // 磁吸线判断区域 判断区域越小越好，最好所有在区域内的图元都在同一水平线上，这样相近的两个图元不会互相干扰
        QRectF rectMagareaH(QPointF(this->sceneRect().left(), pt.y() - 1), QSizeF(this->width(), 1));
        auto areaItemsH = items(rectMagareaH);
        // 去除掉自己
        if (areaItemsH.contains(item))
        {
            areaItemsH.removeOne(item);
        }
        // 去除垂直磁吸线
        if (areaItemsH.contains(m_itemMagneticVLine))
        {
            areaItemsH.removeOne(m_itemMagneticVLine);
        }
        //过滤非XGraphicsItem图元
        auto areaXItemsH=filterNoXItem(areaItemsH);
        // 判断区域内有无图元
        if (!areaXItemsH.isEmpty())
        {
            for (auto i : areaXItemsH)
            {
                // 根据鼠标y坐标和另一个图元判断，水平对齐
                float y = pt.y();
                float ny = i->sceneBoundingRect().center().y();
                if (y > ny - 25 && y < ny + 25)
                {

                    if (m_itemMagneticHLine) { removeItem(m_itemMagneticHLine); delete m_itemMagneticHLine; m_itemMagneticHLine = nullptr; }
                    QPointF ptTemp = QPointF(item->sceneBoundingRect().center().x(), ny) - item->boundingRect().center();
                    item->setPos(ptTemp);
                    //画线
                    m_itemMagneticHLine = new QGraphicsLineItem(QLineF(item->sceneBoundingRect().center(), i->sceneBoundingRect().center()));
                    m_itemMagneticHLine->setPen(m_config.penMagneticLine);
                    addItem(m_itemMagneticHLine);
                }
            }
        }

    }

    {
        // 删除上次磁吸线 垂直
        if (m_itemMagneticVLine) { removeItem(m_itemMagneticVLine); delete m_itemMagneticVLine; m_itemMagneticVLine = nullptr; }
        // [垂直磁吸线]
        // 磁吸线判断区域 判断区域越小越好，最好所有在区域内的图元都在同一水平线上，这样相近的两个图元不会互相干扰
        QRectF magareaV(QPointF(pt.x() - 1, this->sceneRect().top()), QSizeF(1, this->height()));
        auto areaItemsV = items(magareaV);
        // 去除掉自己
        if (areaItemsV.contains(item))
        {
            areaItemsV.removeOne(item);
        }
        // 去除水平磁吸线
        if (areaItemsV.contains(m_itemMagneticHLine))
        {
            areaItemsV.removeOne(m_itemMagneticHLine);
        }
        //过滤非XGraphicsItem图元
        auto areaXItemsV=filterNoXItem(areaItemsV);

        // 判断区域内有无图元
        if (!areaXItemsV.isEmpty())
        {
        for (auto i : areaXItemsV)
        {
            // 根据鼠标y坐标和另一个图元判断，水平对齐
            float x = pt.x();
            float nx = i->sceneBoundingRect().center().x();
            if (x > nx - 25 && x < nx + 25)
            {
                if (m_itemMagneticVLine) { removeItem(m_itemMagneticVLine); delete m_itemMagneticVLine; m_itemMagneticVLine = nullptr; }
                QPointF ptTemp = QPointF(nx, item->sceneBoundingRect().center().y()) - item->boundingRect().center();
                item->setPos(ptTemp);
                //画线
                m_itemMagneticVLine = new QGraphicsLineItem(QLineF(item->sceneBoundingRect().center(), i->sceneBoundingRect().center()));
                m_itemMagneticVLine->setPen(m_config.penMagneticLine);
                addItem(m_itemMagneticVLine);
            }
        }
    }
    }
}




