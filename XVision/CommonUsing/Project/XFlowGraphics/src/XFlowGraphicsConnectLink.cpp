#include "XFlowGraphicsConnectLink.h"
#include "XFlowGraphicsItem.h"
#include "XFlowGraphicsScene.h"
#include "XFlowGraphicsUtils.h"

#include <QUuid>
/*******************************/
//* [XFlowGraphicsConnectLinkPrivate]
/*******************************/
class XFlowGraphicsConnectLinkPrivate
{
    Q_DISABLE_COPY(XFlowGraphicsConnectLinkPrivate)
    Q_DECLARE_PUBLIC(XFlowGraphicsConnectLink)

public:
    XFlowGraphicsConnectLinkPrivate(XFlowGraphicsConnectLink *q):q_ptr(q)
    {
        linkingCirclePen=QPen(QColor(Qt::white));
        linkingCircleBrush=QBrush(QColor(50, 125, 255));
        linkingCircleRadius=4;


        linkingPen=QColor(25, 150, 255);
        linkingPen.setWidth(3);
        linkingPen.setStyle(Qt::SolidLine);

        linkedPen=QColor(25, 150, 255);
        linkedPen.setWidth(3);
        linkedPen.setStyle(Qt::SolidLine);

        linkSelectedPen=QColor(255, 150, 50);
        linkSelectedPen.setWidth(5);
        linkSelectedPen.setStyle(Qt::SolidLine);


        selectBoundingRectPen.setColor(QColor(255, 255, 255));
        selectBoundingRectPen.setWidth(1);
        selectBoundingRectPen.setStyle(Qt::DashLine);

        arrowSize=15;

        highLightPen.setColor(QColor(255,242,0));
        highLightPen.setWidth(3);
        highLightPen.setStyle(Qt::SolidLine);

        textPen = QPen();
        textPen.setColor(QColor(255, 255, 255));
        textPen.setWidth(1);
        textFont = QFont("YouYuan", 12, 2);
        textFont.setBold(false);
    };
    virtual ~XFlowGraphicsConnectLinkPrivate(){};

    XFlowGraphicsConnectLink                *const q_ptr;

    ///连接拖动圆形画笔
    QPen                                linkingCirclePen;
    ///连接拖动圆形笔刷
    QBrush                              linkingCircleBrush;
    ///连接拖动圆半径
    double                              linkingCircleRadius;


    ///正在连线画笔
    QPen                                linkingPen;

    ///连线完毕画笔
    QPen                                linkedPen;

    ///连线被选择时
    QPen                                linkSelectedPen;

    ///选中时边框画笔
    QPen                                selectBoundingRectPen;

    ///末端箭头大小
    double                              arrowSize=15;

    ///连线高亮时的画笔
    QPen                                highLightPen;

    ///Link文本画笔
    QPen                                textPen;
    ///Link文本字体
    QFont                               textFont;

};

/****************************构建与析构****************************/

XFlowGraphicsConnectLink::XFlowGraphicsConnectLink(QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),
    m_ptFatherStart(QPointF(0,0)),m_ptSonEnd(QPointF(0,0)),d_ptr(new XFlowGraphicsConnectLinkPrivate(this))
{
    if(parent)
    {
        auto scene=qobject_cast<XFlowGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }
    initConnectLink();
}

XFlowGraphicsConnectLink::XFlowGraphicsConnectLink(QPointF ptStart, QPointF ptEnd,QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),
      m_ptFatherStart(ptStart),m_ptSonEnd(ptEnd),d_ptr(new XFlowGraphicsConnectLinkPrivate(this))
{
    if(parent)
    {
        auto scene=qobject_cast<XFlowGraphicsScene*>(parent);
        if(scene)
        {
            m_parScene=scene;
        }
    }
    initConnectLink();
}

XFlowGraphicsConnectLink::XFlowGraphicsConnectLink(XFlowGraphicsItem *xItemFather, const QString &fatherKey,
                                           XFlowGraphicsItem *xItemSon, const QString &sonKey, QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),d_ptr(new XFlowGraphicsConnectLinkPrivate(this))
{
    if(parent)
    {
        auto scene=qobject_cast<XFlowGraphicsScene*>(parent);
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

XFlowGraphicsConnectLink::~XFlowGraphicsConnectLink()
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
/***************************属性接口***************************/

QPen XFlowGraphicsConnectLink::linkingCirclePen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->linkingCirclePen;
}

void XFlowGraphicsConnectLink::setLinkingCirclePen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->linkingCirclePen=pen;
}


QBrush XFlowGraphicsConnectLink::linkingCircleBrush() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->linkingCircleBrush;
}

void XFlowGraphicsConnectLink::setLinkingCircleBrush(const  QBrush &brush)
{
    Q_D(XFlowGraphicsConnectLink);
    d->linkingCircleBrush=brush;
}

double XFlowGraphicsConnectLink::linkingCircleRadius() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->linkingCircleRadius;
}

void XFlowGraphicsConnectLink::setLinkingCircleRadius(const double &radius)
{
    Q_D(XFlowGraphicsConnectLink);
    d->linkingCircleRadius=radius;
}

QPen XFlowGraphicsConnectLink::linkingPen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->linkingPen;
}

void XFlowGraphicsConnectLink::setLinkingPen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->linkingPen=pen;
}

QPen XFlowGraphicsConnectLink::linkedPen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->linkedPen;
}

void XFlowGraphicsConnectLink::setLinkedPen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->linkedPen=pen;
}

QPen XFlowGraphicsConnectLink::linkSelectedPen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->linkSelectedPen;
}

void XFlowGraphicsConnectLink::setLinkSelectedPen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->linkSelectedPen=pen;
}


QPen XFlowGraphicsConnectLink::selectBoundingRectPen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->selectBoundingRectPen;
}

void XFlowGraphicsConnectLink::setSelectBoundingRectPen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->selectBoundingRectPen=pen;
}

double XFlowGraphicsConnectLink::arrowSize() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->arrowSize;
}

void XFlowGraphicsConnectLink::setArrowSize(const double &size)
{
    Q_D(XFlowGraphicsConnectLink);
    d->arrowSize=size;
}

QPen XFlowGraphicsConnectLink::highLightPen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->highLightPen;
}

void XFlowGraphicsConnectLink::setHighLightPen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->highLightPen=pen;
}

QPen XFlowGraphicsConnectLink::textPen() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->textPen;
}

void XFlowGraphicsConnectLink::setTextPen(const QPen &pen)
{
    Q_D(XFlowGraphicsConnectLink);
    d->textPen=pen;
}

QFont XFlowGraphicsConnectLink::textFont() const
{
    Q_D(const XFlowGraphicsConnectLink);
    return d->textFont;
}

void XFlowGraphicsConnectLink::setTextFont(const QFont &font)
{
    Q_D(XFlowGraphicsConnectLink);
    d->textFont=font;
}


/***************************初始化接口***************************/
void XFlowGraphicsConnectLink::initConnectLink()
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    updateXLink();
}


/***************************槽函数***************************/

void XFlowGraphicsConnectLink::onXItemUpdate()
{
    onFatherXItemUpdate();
    onSonXItemUpdate();
}


void XFlowGraphicsConnectLink::onFatherXItemDestroyed()
{
    m_fatherXItem=nullptr;
    emit xLinkError();
}

void XFlowGraphicsConnectLink::onSonXItemDestroyed()
{
    m_sonXItem=nullptr;
    emit xLinkError();
}

void XFlowGraphicsConnectLink::onFatherXItemUpdate()
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

void XFlowGraphicsConnectLink::onSonXItemUpdate()
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
void XFlowGraphicsConnectLink::updateXLink()
{
    setLine(QLineF(m_ptSonEnd,m_ptFatherStart));
    updateArrow();
}

/***************************XLink数据***************************/

void XFlowGraphicsConnectLink::setParScene(XFlowGraphicsScene *parScene)
{
    m_parScene=parScene;
}


bool XFlowGraphicsConnectLink::setFatherXItemKey(XFlowGraphicsItem *xItem, const QString &key)
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
        disconnect(m_fatherXItem,&XFlowGraphicsItem::destroyed,this,&XFlowGraphicsConnectLink::onFatherXItemDestroyed);
        disconnect(m_fatherXItem,&XFlowGraphicsItem::posChanged,this,&XFlowGraphicsConnectLink::onFatherXItemUpdate);
        disconnect(m_fatherXItem,&XFlowGraphicsItem::shapeChanged,this,&XFlowGraphicsConnectLink::onFatherXItemUpdate);
        m_fatherXItem=nullptr;
    } 

    m_fatherXItem=xItem;
    m_fatherConnKey=key;
    m_ptFatherStart=data.pt;
    m_fatherXItem->addSonConnect(this);
    connect(m_fatherXItem,&XFlowGraphicsItem::destroyed,this,&XFlowGraphicsConnectLink::onFatherXItemDestroyed);
    connect(m_fatherXItem,&XFlowGraphicsItem::posChanged,this,&XFlowGraphicsConnectLink::onFatherXItemUpdate);
    connect(m_fatherXItem,&XFlowGraphicsItem::shapeChanged,this,&XFlowGraphicsConnectLink::onFatherXItemUpdate);
    updateXLink();
    return true;
}

bool XFlowGraphicsConnectLink::setSonXItemKey(XFlowGraphicsItem *xItem, const QString &key)
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
        disconnect(m_sonXItem,&XFlowGraphicsItem::destroyed,this,&XFlowGraphicsConnectLink::onSonXItemDestroyed);
        disconnect(m_sonXItem,&XFlowGraphicsItem::posChanged,this,&XFlowGraphicsConnectLink::onSonXItemUpdate);
        disconnect(m_sonXItem,&XFlowGraphicsItem::shapeChanged,this,&XFlowGraphicsConnectLink::onSonXItemUpdate);
        m_sonXItem=nullptr;
    }
    m_sonXItem=xItem;
    m_sonConnKey=key;
    m_ptSonEnd=data.pt;
    m_sonXItem->addFatherConnect(this);
    connect(m_sonXItem,&XFlowGraphicsItem::destroyed,this,&XFlowGraphicsConnectLink::onSonXItemDestroyed);
    connect(m_sonXItem,&XFlowGraphicsItem::posChanged,this,&XFlowGraphicsConnectLink::onSonXItemUpdate);
    connect(m_sonXItem,&XFlowGraphicsItem::shapeChanged,this,&XFlowGraphicsConnectLink::onSonXItemUpdate);
    updateXLink();
    return true;
}

bool XFlowGraphicsConnectLink::setFatherStartPos(const QPointF &pt)
{
   if(m_fatherXItem) return false;//存在起始Item不可设置
   m_ptFatherStart=pt;
   updateXLink();
   return true;
}

bool XFlowGraphicsConnectLink::setSonEndPos(const QPointF &pt)
{
    if(m_sonXItem) return false;//存在结束Item不可设置
    m_ptSonEnd=pt;
    updateXLink();
    return true;
}

bool XFlowGraphicsConnectLink::setFatherKey(const QString &key)
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

bool XFlowGraphicsConnectLink::setSonKey(const QString &key)
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

void XFlowGraphicsConnectLink::setLinkState(bool isLinked)
{
    m_bLinked=isLinked;
}

void XFlowGraphicsConnectLink::setHighLight(bool highLight, bool bUpdate)
{
    m_bHighLight=highLight;
    if(bUpdate)
    {
        this->update();
    }
}


/***************************重写父类接口***************************/

QRectF XFlowGraphicsConnectLink::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                          line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}


QPainterPath XFlowGraphicsConnectLink::shape() const
{
    QPainterPath path;
    QPainterPathStroker stroker;
    stroker.setWidth(30);
    path.moveTo(line().p1());
    path.lineTo(line().p2());
    return stroker.createStroke(path);
}

void XFlowGraphicsConnectLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(XFlowGraphicsConnectLink);

    painter->save();
    if(m_bLinked) //已经连接
    {

        if(isSelected())
        {
            painter->setPen(d->linkSelectedPen);
            painter->setBrush(d->linkSelectedPen.color());
        }
        else
        {
            painter->setPen(d->linkedPen);
            painter->setBrush(d->linkedPen.color());
        }
        if(m_bHighLight)
        {
            painter->setPen(d->highLightPen);
            painter->setBrush(d->highLightPen.color());
        }
        painter->drawLine(this->line());
        painter->drawPolygon(m_polyArrowHead);

        if(isSelected()) //选择状态绘制外框
        {

            painter->setPen(d->selectBoundingRectPen);
            painter->setBrush(Qt::NoBrush);
            double size=d->arrowSize/2.0;
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
       painter->setPen(d->linkingPen);
       painter->setBrush(d->linkingPen.color());
       painter->drawLine(this->line());
       painter->drawPolygon(m_polyArrowHead);
       painter->setPen(d->linkingCirclePen);
       painter->setBrush(d->linkingCircleBrush);
       double radius=d->linkingCircleRadius;
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
void XFlowGraphicsConnectLink::updateArrow()
{
    double angle = std::atan2(-line().dy(), line().dx());
    double arrowSize=this->arrowSize();
    const double coef=2.5;
    QPointF arrowP1 = m_ptSonEnd + QPointF(sin(angle + M_PI / coef) * arrowSize,
                                    cos(angle + M_PI / coef) * arrowSize);
    QPointF arrowP2 = m_ptSonEnd+ QPointF(sin(angle + M_PI - M_PI / coef) * arrowSize,
                                    cos(angle + M_PI - M_PI / coef) * arrowSize);

    m_polyArrowHead.clear();
    m_polyArrowHead <<m_ptSonEnd << arrowP1 << arrowP2;
}

void XFlowGraphicsConnectLink::drawLinkText(QPainter *painter, const QString &text)
{
    painter->save();
    painter->setFont(textFont());
    QFontMetrics fontMetrics = painter->fontMetrics();
    painter->setPen(textPen());
    QRect rect = fontMetrics.boundingRect(text);
    QPointF pos=line().center()-QPointF(rect.width()/2,rect.height()/2);
    rect.moveTo(pos.toPoint());
    painter->drawText(rect,text);
    painter->restore();
}

/***************************XLink形状外观***************************/

double XFlowGraphicsConnectLink::linkLength()
{
   return this->line().length();
}

