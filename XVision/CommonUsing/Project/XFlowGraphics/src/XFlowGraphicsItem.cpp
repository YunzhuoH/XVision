#include "XFlowGraphicsItem.h"
#include "XFlowGraphicsScene.h"
#include "XFlowGraphicsConnectLink.h"
#include <QGraphicsSceneMouseEvent>
#include <QUuid>

/*******************************/
//* [XFlowGraphicsItemPrivate]
/*******************************/
class XFlowGraphicsItemPrivate
{
    Q_DISABLE_COPY(XFlowGraphicsItemPrivate)
    Q_DECLARE_PUBLIC(XFlowGraphicsItem)

public:
    XFlowGraphicsItemPrivate(XFlowGraphicsItem *q):q_ptr(q)
    {
        connectAreaPen=QPen(QColor(30,30,30));
        connectAreaBrush=QBrush(QColor(100,130,250));

        textPen = QPen();
        textPen.setColor(QColor(75, 75, 75));
        textPen.setWidth(1);
        textFont = QFont("YouYuan", 12, 2);
        textFont.setBold(true);

        highLightPen.setColor(QColor(255,242,0));
        highLightPen.setWidth(5);
        highLightBrush=QBrush(QColor(Qt::white));

    };
    virtual ~XFlowGraphicsItemPrivate(){};

    XFlowGraphicsItem              *const q_ptr;

    ///连接区域边框画笔
    QPen                        connectAreaPen;
    ///连接区域内部笔刷
    QBrush                      connectAreaBrush;

    ///Item文本画笔
    QPen                        textPen;
    ///Item文本字体
    QFont                       textFont;

    ///高亮时画笔
    QPen                        highLightPen;
    ///高亮时笔刷
    QBrush                      highLightBrush;

};



/****************************构建与析构****************************/

XFlowGraphicsItem::XFlowGraphicsItem(QString type,QString id,QObject *parent)
    :QObject{parent},m_ItemType(type),d_ptr(new XFlowGraphicsItemPrivate(this))
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
        auto scene=qobject_cast<XFlowGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }

    m_mapPixData.clear();
    m_mapThisFatherConnect.clear();
    m_mapThisSonConnect.clear();
}

XFlowGraphicsItem::~XFlowGraphicsItem()
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

/****************************属性接口****************************/
QPen XFlowGraphicsItem::connectAreaPen() const
{
    Q_D(const XFlowGraphicsItem);
    return d->connectAreaPen;
}

void XFlowGraphicsItem::setConnectAreaPen(const QPen &pen)
{
    Q_D(XFlowGraphicsItem);
    d->connectAreaPen=pen;
}

QBrush XFlowGraphicsItem::connectAreaBrush() const
{
    Q_D(const XFlowGraphicsItem);
    return d->connectAreaBrush;
}

void XFlowGraphicsItem::setConnectAreaBrush(const QBrush &brush)
{
    Q_D(XFlowGraphicsItem);
    d->connectAreaBrush=brush;
}


QPen XFlowGraphicsItem::textPen() const
{
    Q_D(const XFlowGraphicsItem);
    return d->textPen;
}

void XFlowGraphicsItem::setTextPen(const QPen &pen)
{
    Q_D(XFlowGraphicsItem);
    d->textPen=pen;
}


QFont XFlowGraphicsItem::textFont() const
{
    Q_D(const XFlowGraphicsItem);
    return d->textFont;
}

void XFlowGraphicsItem::setTextFont(const QFont &font)
{
    Q_D(XFlowGraphicsItem);
    d->textFont=font;
}


QPen XFlowGraphicsItem::highLightPen() const
{
    Q_D(const XFlowGraphicsItem);
    return d->highLightPen;
}

void XFlowGraphicsItem::setHighLightPen(const QPen &pen)
{
    Q_D(XFlowGraphicsItem);
    d->highLightPen=pen;
}


QBrush XFlowGraphicsItem::highLightBrush() const
{
    Q_D(const XFlowGraphicsItem);
    return d->highLightBrush;
}

void XFlowGraphicsItem::setHighLightBrush(const QBrush &pen)
{
    Q_D(XFlowGraphicsItem);
    d->highLightBrush=pen;
}


/***************************Scene事件接口***************************/

void XFlowGraphicsItem::sceneMouseEnterEvent(QGraphicsSceneMouseEvent *event)
{
    m_strShowFullKey="";
    setShowConnectArea(EShowConnectAreaType::ShowLittle);
}

void XFlowGraphicsItem::sceneMouseLeaveEvent(QGraphicsSceneMouseEvent *event)
{
    m_strShowFullKey="";
    setShowConnectArea(EShowConnectAreaType::NoShow);
}

void XFlowGraphicsItem::sceneMouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
void XFlowGraphicsItem::setSize(double width, double height, bool bUpdate)
{
    setWidth(width,false);
    setHeight(height,false);
    if(bUpdate)
    {
        this->updateShape();
    }
}

void XFlowGraphicsItem::setWidth(double width, bool bUpdate)
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

void XFlowGraphicsItem::setHeight(double height, bool bUpdate)
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

void XFlowGraphicsItem::setHighLight(bool highLight,bool bUpdate)
{
    m_bHighLight=highLight;
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

XFlowGraphicsConnectLink *XFlowGraphicsItem::getFatherConnectLink(const QString &id) const
{
    if(m_mapThisFatherConnect.contains(id))
    {
        return m_mapThisFatherConnect[id];
    }
    return nullptr;
}

QList<XFlowGraphicsConnectLink*> XFlowGraphicsItem::getFatherConnectLinks() const
{
    QList<XFlowGraphicsConnectLink*> lst;
    foreach (auto xLink, m_mapThisFatherConnect)
    {
        lst.append(xLink);
    }
    return lst;
}

XFlowGraphicsConnectLink *XFlowGraphicsItem::getSonConnectLink(const QString &id) const
{
    if(m_mapThisSonConnect.contains(id))
    {
        return m_mapThisSonConnect[id];
    }
    return nullptr;
}

QList<XFlowGraphicsConnectLink *> XFlowGraphicsItem::getSonConnectLinks() const
{
    QList<XFlowGraphicsConnectLink*> lst;
    foreach (auto xLink, m_mapThisSonConnect)
    {
        lst.append(xLink);
    }
    return lst;
}

bool XFlowGraphicsItem::getFatherConnectData(XFlowGraphicsConnectLink *fatherLink, SConnectData &connData)
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

bool XFlowGraphicsItem::getSonConnectData(XFlowGraphicsConnectLink *sonLink, SConnectData &connData)
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

//*[连接线调用接口]* XFlowGraphicsConnectLink:连线

bool XFlowGraphicsItem::addFatherConnect(XFlowGraphicsConnectLink *xLink)
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

bool XFlowGraphicsItem::addSonConnect(XFlowGraphicsConnectLink *xLink)
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

bool XFlowGraphicsItem::removeFatherConnect(XFlowGraphicsConnectLink *xLink)
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

bool XFlowGraphicsItem::removeSonConnect(XFlowGraphicsConnectLink *xLink)
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

bool XFlowGraphicsItem::hasFatherConnectSelected()
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

bool XFlowGraphicsItem::hasSonConnectSelected()
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

SConnectData XFlowGraphicsItem::sconnectDataMapToScene(const SConnectData &data)
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

void XFlowGraphicsItem::setShowConnectArea(EShowConnectAreaType eType, bool bUpdate)
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
void XFlowGraphicsItem::setParScene(XFlowGraphicsScene *parScene)
{
    m_parScene=parScene;
}


//[item附带数据]
void XFlowGraphicsItem::setItemTag(const QVariant &tag)
{
    m_ItemTag=tag;
}

void XFlowGraphicsItem::setItemQPtrTag(QObject *qptrTag)
{
    m_ItemQPtrTag=qptrTag;
}

void XFlowGraphicsItem::addPixData(SXItemPixData *data)
{
    if(!data) return;

    if(!m_mapPixData.contains(data->strKey))
    {
        m_mapPixData.insert(data->strKey,data);
    }
}

bool XFlowGraphicsItem::switchShowPixKey(const QString &pixKey,const QString &penKey, bool bUpdate)
{
    if(m_mapPixData.contains(pixKey)||pixKey=="")
    {
        m_strShowPixKey=pixKey;
        auto pixData=m_mapPixData[pixKey];
        pixData->switchPenKey(penKey);
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

