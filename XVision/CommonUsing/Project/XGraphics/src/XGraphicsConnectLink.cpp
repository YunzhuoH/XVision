#include "XGraphicsConnectLink.h"
#include "XGraphicsItem.h"
#include "XGraphicsScene.h"
#include "XGraphicsUtils.h"

#include <QUuid>

/****************************构建与析构****************************/

XGraphicsConnectLink::XGraphicsConnectLink(QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),
    m_ptFatherStart(QPointF(0,0)),m_ptSonEnd(QPointF(0,0))
{
    if(parent)
    {
        auto scene=qobject_cast<XGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }
    initConnectLink();
}

XGraphicsConnectLink::XGraphicsConnectLink(QPointF ptStart, QPointF ptEnd,QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),
      m_ptFatherStart(ptStart),m_ptSonEnd(ptEnd)
{
    if(parent)
    {
        auto scene=qobject_cast<XGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }
    initConnectLink();
}

XGraphicsConnectLink::XGraphicsConnectLink(XGraphicsItem *xItemFather, const QString &fatherKey,
                                           XGraphicsItem *xItemSon, const QString &sonKey, QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128))
{
    if(parent)
    {
        auto scene=qobject_cast<XGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }

    if(!setFatherXItemKey(xItemFather,fatherKey))
    {
        m_ptFatherStart=QPointF(0,0);
    }
    if(!setSonXItemKey(xItemSon,sonKey))
    {
         m_ptSonEnd=QPointF(0,0);
    }
    initConnectLink();
}

XGraphicsConnectLink::~XGraphicsConnectLink()
{
    if(m_fatherXItem)
    {
        m_fatherXItem->removeSonConnect(this);
    }
    if(m_sonXItem)
    {
        m_sonXItem->removeFatherConnect(this);
    }
}

void XGraphicsConnectLink::initConnectLink()
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    updateXLink();
}


/***************************槽函数***************************/

void XGraphicsConnectLink::onXItemUpdate()
{
    onFatherXItemUpdate();
    onSonXItemUpdate();
}


void XGraphicsConnectLink::onFatherXItemDestroyed()
{
    m_fatherXItem=nullptr;
    emit xLinkError();
}

void XGraphicsConnectLink::onSonXItemDestroyed()
{
    m_sonXItem=nullptr;
    emit xLinkError();
}

void XGraphicsConnectLink::onFatherXItemUpdate()
{
    if(!m_fatherXItem) return;
    SConnectData data;
    if(!m_fatherXItem->getSonConnectData(this,data))
    {
        emit xLinkError();
    }
    m_ptFatherStart=data.pt;
    updateXLink();
}

void XGraphicsConnectLink::onSonXItemUpdate()
{
    if(!m_sonXItem) return;
    SConnectData data;
    if(!m_sonXItem->getFatherConnectData(this,data))
    {
        emit xLinkError();
    }
    m_ptSonEnd=data.pt;
    updateXLink();
}


/* ToDo:
 * 1.将当前直线优化为直角拐弯线，参考draw.io绘图软件的连接线；
 * 2.显示移动中点，拖动该点使线段移动;
 * 3.对当前经过的图元进行绕弯处理，防止重叠
*/
void XGraphicsConnectLink::updateXLink()
{
    setLine(QLineF(m_ptSonEnd,m_ptFatherStart));
    updateArrow();
}

/***************************XLink数据***************************/

void XGraphicsConnectLink::setParScene(XGraphicsScene *parScene)
{
    m_parScene=parScene;
}


bool XGraphicsConnectLink::setFatherXItemKey(XGraphicsItem *xItem, const QString &key)
{
    if(xItem==nullptr) return false;
    SConnectData data;
    if(!xItem->getConnectData(key,data))
    {
        return false;//设置失败
    }
    //设置成功 更新startItem
    if(m_fatherXItem)
    {
        m_fatherXItem->removeSonConnect(this);
        disconnect(m_fatherXItem,&XGraphicsItem::destroyed,this,&XGraphicsConnectLink::onFatherXItemDestroyed);
        disconnect(m_fatherXItem,&XGraphicsItem::posChanged,this,&XGraphicsConnectLink::onFatherXItemUpdate);
        disconnect(m_fatherXItem,&XGraphicsItem::shapeChanged,this,&XGraphicsConnectLink::onFatherXItemUpdate);
        m_fatherXItem=nullptr;
    } 

    m_fatherXItem=xItem;
    m_fatherConnKey=key;
    m_ptFatherStart=data.pt;
    m_fatherXItem->addSonConnect(this);
    connect(m_fatherXItem,&XGraphicsItem::destroyed,this,&XGraphicsConnectLink::onFatherXItemDestroyed);
    connect(m_fatherXItem,&XGraphicsItem::posChanged,this,&XGraphicsConnectLink::onFatherXItemUpdate);
    connect(m_fatherXItem,&XGraphicsItem::shapeChanged,this,&XGraphicsConnectLink::onFatherXItemUpdate);
    updateXLink();
    return true;
}

bool XGraphicsConnectLink::setSonXItemKey(XGraphicsItem *xItem, const QString &key)
{
    if(xItem==nullptr) return false;
    SConnectData data;
    if(!xItem->getConnectData(key,data))
    {
        return false;//设置失败
    }
    //设置成功 更新startItem
    if(m_sonXItem)
    {
        m_sonXItem->removeFatherConnect(this);
        disconnect(m_sonXItem,&XGraphicsItem::destroyed,this,&XGraphicsConnectLink::onSonXItemDestroyed);
        disconnect(m_sonXItem,&XGraphicsItem::posChanged,this,&XGraphicsConnectLink::onSonXItemUpdate);
        disconnect(m_sonXItem,&XGraphicsItem::shapeChanged,this,&XGraphicsConnectLink::onSonXItemUpdate);
        m_sonXItem=nullptr;
    }
    m_sonXItem=xItem;
    m_sonConnKey=key;
    m_ptSonEnd=data.pt;
    m_sonXItem->addFatherConnect(this);
    connect(m_sonXItem,&XGraphicsItem::destroyed,this,&XGraphicsConnectLink::onSonXItemDestroyed);
    connect(m_sonXItem,&XGraphicsItem::posChanged,this,&XGraphicsConnectLink::onSonXItemUpdate);
    connect(m_sonXItem,&XGraphicsItem::shapeChanged,this,&XGraphicsConnectLink::onSonXItemUpdate);
    updateXLink();
    return true;
}

bool XGraphicsConnectLink::setFatherStartPos(const QPointF &pt)
{
   if(m_fatherXItem) return false;//存在起始Item不可设置
   m_ptFatherStart=pt;
   updateXLink();
   return true;
}

bool XGraphicsConnectLink::setSonEndPos(const QPointF &pt)
{
    if(m_sonXItem) return false;//存在结束Item不可设置
    m_ptSonEnd=pt;
    updateXLink();
    return true;
}

bool XGraphicsConnectLink::setFatherKey(const QString &key)
{
    if(!m_fatherXItem) return false;//不存在开始Item不可设置
    if(!m_fatherXItem->hasConnectKey(key)) return false; //父Item中不存在该Key连接点 不可设置
    SConnectData data;
    if(!m_fatherXItem->getConnectData(key,data))
    {
        return false;//设置失败
    }
    m_fatherConnKey=key;
    m_ptFatherStart=data.pt;
    updateXLink();
    return true;
}

bool XGraphicsConnectLink::setSonKey(const QString &key)
{
    if(!m_sonXItem) return false;//不存在结束Item不可设置
    if(!m_sonXItem->hasConnectKey(key)) return false; //子Item中不存在该Key连接点 不可设置
    SConnectData data;
    if(!m_sonXItem->getConnectData(key,data))
    {
        return false;//设置失败
    }
    m_sonConnKey=key;
    m_ptSonEnd=data.pt;
    updateXLink();
    return true;
}

void XGraphicsConnectLink::setLinkState(bool isLinked)
{
    m_bLinked=isLinked;
}

void XGraphicsConnectLink::setHighlight(bool highlight, bool bUpdate)
{
    m_bHighlight=highlight;
    if(bUpdate)
    {
        this->update();
    }
}


/***************************重写父类接口***************************/

QRectF XGraphicsConnectLink::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                          line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}


QPainterPath XGraphicsConnectLink::shape() const
{
    QPainterPath path;
    QPainterPathStroker stroker;
    stroker.setWidth(30);
    path.moveTo(line().p1());
    path.lineTo(line().p2());
    return stroker.createStroke(path);
}

void XGraphicsConnectLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->save();
    if(m_bLinked) //已经连接
    {

        if(isSelected())
        {
            painter->setPen(m_LinkConfig.penLinkSelected);
            painter->setBrush(m_LinkConfig.penLinkSelected.color());
        }
        else
        {
            painter->setPen(m_LinkConfig.penLinked);
            painter->setBrush(m_LinkConfig.penLinked.color());
        }
        if(m_bHighlight)
        {
            painter->setPen(m_LinkConfig.penHighLight);
            painter->setBrush(m_LinkConfig.penHighLight.color());
        }
        painter->drawLine(this->line());
        painter->drawPolygon(m_polyArrowHead);

        if(isSelected()) //选择状态绘制外框
        {

            painter->setPen(m_LinkConfig.penSelectBoundingRect);
            painter->setBrush(Qt::NoBrush);
            double size=m_LinkConfig.rArrowSize/2.0;
            double angle = std::atan2(-line().dy(), line().dx());

            QPointF p1 = m_ptFatherStart + QPointF(sin(angle + M_PI) * size,cos(angle + M_PI) * size);
            QPointF p2 = m_ptFatherStart+ QPointF(sin(angle + M_PI - M_PI ) * size,cos(angle + M_PI - M_PI ) * size);
            QPointF p3 = m_ptSonEnd+ QPointF(sin(angle + M_PI - M_PI ) * size,cos(angle + M_PI - M_PI ) * size);
            QPointF p4 = m_ptSonEnd + QPointF(sin(angle + M_PI) * size,cos(angle + M_PI) * size);

            QPolygonF boundingRect;
            boundingRect.clear();
            boundingRect<<p1<<p2<<p3<<p4;
            painter->drawPolygon(boundingRect);
        }

    }
    else //未连接时
    {
       painter->setPen(m_LinkConfig.penLinking);
       painter->setBrush(m_LinkConfig.penLinking.color());
       painter->drawLine(this->line());
       painter->drawPolygon(m_polyArrowHead);
       painter->setPen(m_LinkConfig.penLinkingCircle);
       painter->setBrush(m_LinkConfig.brushLinkingCircle);
       double radius=m_LinkConfig.rLinkingCircleRadius;
       painter->drawEllipse(this->sonEndPos(),radius,radius);
    }


    double rectSize=line().length()/2;
    if(rectSize<100)
    {
        rectSize=100;
    }
    QRect rect(0,0,rectSize,rectSize/2);
    QPointF pos=line().center()-QPointF(rect.width()/2,rect.height()/2);
    rect.moveTo(pos.toPoint());
    m_LinkRectText=rect;

    if(!m_LinkText.isEmpty())
    {
        drawLinkText(painter,m_LinkText);
    }

    painter->restore();


}



/***************************内部调用接口***************************/
void XGraphicsConnectLink::updateArrow()
{
    double angle = std::atan2(-line().dy(), line().dx());
    double arrowSize=m_LinkConfig.rArrowSize;
    const double coef=2.5;
    QPointF arrowP1 = m_ptSonEnd + QPointF(sin(angle + M_PI / coef) * arrowSize,
                                    cos(angle + M_PI / coef) * arrowSize);
    QPointF arrowP2 = m_ptSonEnd+ QPointF(sin(angle + M_PI - M_PI / coef) * arrowSize,
                                    cos(angle + M_PI - M_PI / coef) * arrowSize);

    m_polyArrowHead.clear();
    m_polyArrowHead <<m_ptSonEnd << arrowP1 << arrowP2;
}

void XGraphicsConnectLink::drawLinkText(QPainter *painter, const QString &text)
{
    painter->save();
    painter->setFont(m_LinkConfig.fontText);
    QFontMetrics fontMetrics = painter->fontMetrics();
    painter->setPen(m_LinkConfig.penText);
    QRect rect = fontMetrics.boundingRect(text);
    QPointF pos=line().center()-QPointF(rect.width()/2,rect.height()/2);
    rect.moveTo(pos.toPoint());
    painter->drawText(rect,text);
    painter->restore();
}

/***************************XLink形状外观***************************/

double XGraphicsConnectLink::linkLength()
{
   return this->line().length();
}

