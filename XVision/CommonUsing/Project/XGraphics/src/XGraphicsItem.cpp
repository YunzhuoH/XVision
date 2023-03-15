#include "XGraphicsItem.h"
#include "XGraphicsScene.h"
#include "XGraphicsConnectLink.h"
#include <QGraphicsSceneMouseEvent>
#include <QUuid>

/****************************构建与析构****************************/

XGraphicsItem::XGraphicsItem(QString type,QString id,QObject *parent)
    :QObject{parent},m_ItemType(type)
{
    if(id.isEmpty())
    {
         m_ItemId=QUuid::createUuid().toString(QUuid::Id128);
    }
    else
    {
        m_ItemId=id;
    }
    if(parent)
    {
        auto scene=qobject_cast<XGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }

    m_mapTagData.clear();
    m_mapPixData.clear();
    m_mapThisFatherConnect.clear();
    m_mapThisSonConnect.clear();
}

XGraphicsItem::~XGraphicsItem()
{
    foreach (auto pixData, m_mapPixData)
    {
        if(pixData)
        {
            delete pixData;
            pixData=nullptr;
        }
    }
}

/***************************Scene事件接口***************************/

void XGraphicsItem::sceneMouseEnterEvent(QGraphicsSceneMouseEvent *event)
{
    m_strShowFullKey="";
    setShowConnectArea(EShowConnectAreaType::ShowLittle);
}

void XGraphicsItem::sceneMouseLeaveEvent(QGraphicsSceneMouseEvent *event)
{
    m_strShowFullKey="";
    setShowConnectArea(EShowConnectAreaType::NoShow);
}

void XGraphicsItem::sceneMouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pt=event->scenePos();
    SConnectData data;
    if(this->getConnectData(pt,data))
    {
        m_strShowFullKey=data.key;
        setShowConnectArea(EShowConnectAreaType::ShowFull);
    }
    else
    {
        m_strShowFullKey="";
        setShowConnectArea(EShowConnectAreaType::ShowLittle);
    }
}




/***************************xItem形状信息***************************/

//*[形状尺寸]*
void XGraphicsItem::setSize(double width, double height, bool bUpdate)
{
    setWidth(width,false);
    setHeight(height,false);
    if(bUpdate)
    {
        this->updateShape();
    }
}

void XGraphicsItem::setWidth(double width, bool bUpdate)
{
    if(width>0)
    {
        m_rWidth=width;
        if(bUpdate)
        {
            this->updateShape();
        }
    }
}

void XGraphicsItem::setHeight(double height, bool bUpdate)
{
    if(height>0)
    {
        m_rHeight=height;
        if(bUpdate)
        {
            this->updateShape();
        }
    }
}

void XGraphicsItem::setHighlight(bool highlight,bool bUpdate)
{
    m_bHighlight=highlight;
    if(bUpdate)
    {
        auto it=item();
        if(it)
        {
            it->update();
        }
    }
}



/***************************xItem连线模块***************************/

//*[连接对象]

XGraphicsConnectLink *XGraphicsItem::getFatherConnectLink(const QString &id) const
{
    if(m_mapThisFatherConnect.contains(id))
    {
        return m_mapThisFatherConnect[id];
    }
    return nullptr;
}

QList<XGraphicsConnectLink*> XGraphicsItem::getFatherConnectLinks() const
{
    QList<XGraphicsConnectLink*> lst;
    foreach (auto xLink, m_mapThisFatherConnect)
    {
        lst.append(xLink);
    }
    return lst;
}

XGraphicsConnectLink *XGraphicsItem::getSonConnectLink(const QString &id) const
{
    if(m_mapThisSonConnect.contains(id))
    {
        return m_mapThisSonConnect[id];
    }
    return nullptr;
}

QList<XGraphicsConnectLink *> XGraphicsItem::getSonConnectLinks() const
{
    QList<XGraphicsConnectLink*> lst;
    foreach (auto xLink, m_mapThisSonConnect)
    {
        lst.append(xLink);
    }
    return lst;
}

bool XGraphicsItem::getFatherConnectData(XGraphicsConnectLink *fatherLink, SConnectData &connData)
{
    if(!fatherLink) return false;
    if(fatherLink->sonXItem()==nullptr||fatherLink->sonXItem()!=this) return false;
    if(!m_mapThisFatherConnect.contains(fatherLink->linkId()))
    {
        return false;
    }
    QString key=fatherLink->sonKey();//指向子Item(本Item)的Key
    return getConnectData(key,connData);
}

bool XGraphicsItem::getSonConnectData(XGraphicsConnectLink *sonLink, SConnectData &connData)
{
    if(!sonLink) return false;
    if(sonLink->fatherXItem()==nullptr||sonLink->fatherXItem()!=this) return false;
    if(!m_mapThisSonConnect.contains(sonLink->linkId()))
    {
        return false;
    }
    QString key=sonLink->fatherKey();//指向父Item(本Item)的Key
    return getConnectData(key,connData);
}

//*[连接线调用接口]* XGraphicsConnectLink:连线

bool XGraphicsItem::addFatherConnect(XGraphicsConnectLink *xLink)
{
    if(!xLink) return false;
    auto xItem=xLink->sonXItem();//输入点为本节点
    if(!xItem) return false;
    if(xItem->itemId()!=this->itemId())
    {
        return false;
    }
    if(m_mapThisFatherConnect.contains(xLink->linkId()))
    {
        return false;
    }
    m_mapThisFatherConnect.insert(xLink->linkId(),xLink);
    return true;
}

bool XGraphicsItem::addSonConnect(XGraphicsConnectLink *xLink)
{
    if(!xLink) return false;
    auto xItem=xLink->fatherXItem();//输出点为本节点
    if(!xItem) return false;
    if(xItem->itemId()!=this->itemId())
    {
        return false;
    }
    if(m_mapThisSonConnect.contains(xLink->linkId()))
    {
        return false;
    }

    m_mapThisSonConnect.insert(xLink->linkId(),xLink);
    return true;
}

bool XGraphicsItem::removeFatherConnect(XGraphicsConnectLink *xLink)
{
    if(!xLink) return false;
    auto xItem=xLink->sonXItem();//输入点为本节点
    if(!xItem) return false;
    if(xItem->itemId()!=this->itemId())
    {
        return false;
    }
    if(!m_mapThisFatherConnect.contains(xLink->linkId()))
    {
        return false;
    }
    m_mapThisFatherConnect.remove(xLink->linkId());
    return true;
}

bool XGraphicsItem::removeSonConnect(XGraphicsConnectLink *xLink)
{
    if(!xLink) return false;
    auto xItem=xLink->fatherXItem();//输入点为本节点
    if(!xItem) return false;
    if(xItem->itemId()!=this->itemId())
    {
        return false;
    }
    if(!m_mapThisSonConnect.contains(xLink->linkId()))
    {
        return false;
    }
    m_mapThisSonConnect.remove(xLink->linkId());
    return true;
}

bool XGraphicsItem::hasFatherConnectSelected()
{
    foreach (auto xlink, m_mapThisFatherConnect)
    {
        if(xlink->isSelected())
        {
            return true;
        }
    }
    return false;
}

bool XGraphicsItem::hasSonConnectSelected()
{
    foreach (auto xlink, m_mapThisSonConnect)
    {
        if(xlink->isSelected())
        {
            return true;
        }
    }
    return false;
}


//*[内部调用接口]*

SConnectData XGraphicsItem::sconnectDataMapToScene(const SConnectData &data)
{
    SConnectData retData;
    retData.key=data.key;

    if(item())
    {
        retData.pt=item()->mapToScene(data.pt);
    }
    if(item())
    {
        retData.area=item()->mapToScene(data.area);
    }
    return retData;
}

void XGraphicsItem::setShowConnectArea(EShowConnectAreaType eType, bool bUpdate)
{
    if(m_eShowConnectAreaType!=eType)
    {
        m_eShowConnectAreaType=eType;
        if(bUpdate)
        {
            auto it=item();
            if(it)
            {
                it->update();
            }
        }
    }

}



/***************************xItem数据区***************************/

//[item属性]
void XGraphicsItem::setParScene(XGraphicsScene *parScene)
{
    m_parScene=parScene;
}

//[item附带数据]
void XGraphicsItem::addTagData(QString key, const QVariant &data)
{
    m_mapTagData.insert(key,data);
}

void XGraphicsItem::addPixData(SXItemPixData *data)
{
    if(!data) return;

    if(!m_mapPixData.contains(data->strKey))
    {
        m_mapPixData.insert(data->strKey,data);
    }
}

bool XGraphicsItem::switchShowPixKey(const QString &key, bool bUpdate)
{
    if(m_mapPixData.contains(key)||key=="")
    {
        m_strShowPixKey=key;
        if(bUpdate)
        {
            auto it=item();
            if(it)
            {
                it->update();
            }
        }
        return true;
    }

    return false;

}

