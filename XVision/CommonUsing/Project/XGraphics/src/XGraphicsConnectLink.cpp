#include "XGraphicsConnectLink.h"
#include "XGraphicsItem.h"
#include "XGraphicsScene.h"
#include "XGraphicsUtils.h"

#include <QUuid>
/*******************************/
//* [XGraphicsConnectLinkPrivate]
/*******************************/
class XGraphicsConnectLinkPrivate
{
    Q_DISABLE_COPY(XGraphicsConnectLinkPrivate)
    Q_DECLARE_PUBLIC(XGraphicsConnectLink)

public:
    XGraphicsConnectLinkPrivate(XGraphicsConnectLink *q):q_ptr(q)
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
    virtual ~XGraphicsConnectLinkPrivate(){};

    XGraphicsConnectLink                *const q_ptr;

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

XGraphicsConnectLink::XGraphicsConnectLink(QObject *parent)
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),
    m_ptFatherStart(QPointF(0,0)),m_ptSonEnd(QPointF(0,0)),d_ptr(new XGraphicsConnectLinkPrivate(this))
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
      m_ptFatherStart(ptStart),m_ptSonEnd(ptEnd),d_ptr(new XGraphicsConnectLinkPrivate(this))
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
    :QObject{parent},   m_LinkId(QUuid::createUuid().toString(QUuid::Id128)),d_ptr(new XGraphicsConnectLinkPrivate(this))
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
/***************************属性接口***************************/

QPen XGraphicsConnectLink::linkingCirclePen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->linkingCirclePen;
}

void XGraphicsConnectLink::setLinkingCirclePen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->linkingCirclePen=pen;
}


QBrush XGraphicsConnectLink::linkingCircleBrush() const
{
    Q_D(const XGraphicsConnectLink);
    return d->linkingCircleBrush;
}

void XGraphicsConnectLink::setLinkingCircleBrush(const  QBrush &brush)
{
    Q_D(XGraphicsConnectLink);
    d->linkingCircleBrush=brush;
}

double XGraphicsConnectLink::linkingCircleRadius() const
{
    Q_D(const XGraphicsConnectLink);
    return d->linkingCircleRadius;
}

void XGraphicsConnectLink::setLinkingCircleRadius(const double &radius)
{
    Q_D(XGraphicsConnectLink);
    d->linkingCircleRadius=radius;
}

QPen XGraphicsConnectLink::linkingPen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->linkingPen;
}

void XGraphicsConnectLink::setLinkingPen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->linkingPen=pen;
}

QPen XGraphicsConnectLink::linkedPen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->linkedPen;
}

void XGraphicsConnectLink::setLinkedPen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->linkedPen=pen;
}

QPen XGraphicsConnectLink::linkSelectedPen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->linkSelectedPen;
}

void XGraphicsConnectLink::setLinkSelectedPen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->linkSelectedPen=pen;
}


QPen XGraphicsConnectLink::selectBoundingRectPen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->selectBoundingRectPen;
}

void XGraphicsConnectLink::setSelectBoundingRectPen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->selectBoundingRectPen=pen;
}

double XGraphicsConnectLink::arrowSize() const
{
    Q_D(const XGraphicsConnectLink);
    return d->arrowSize;
}

void XGraphicsConnectLink::setArrowSize(const double &size)
{
    Q_D(XGraphicsConnectLink);
    d->arrowSize=size;
}

QPen XGraphicsConnectLink::highLightPen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->highLightPen;
}

void XGraphicsConnectLink::setHighLightPen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->highLightPen=pen;
}

QPen XGraphicsConnectLink::textPen() const
{
    Q_D(const XGraphicsConnectLink);
    return d->textPen;
}

void XGraphicsConnectLink::setTextPen(const QPen &pen)
{
    Q_D(XGraphicsConnectLink);
    d->textPen=pen;
}

QFont XGraphicsConnectLink::textFont() const
{
    Q_D(const XGraphicsConnectLink);
    return d->textFont;
}

void XGraphicsConnectLink::setTextFont(const QFont &font)
{
    Q_D(XGraphicsConnectLink);
    d->textFont=font;
}


/***************************初始化接口***************************/
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
    Q_D(XGraphicsConnectLink);

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
        if(m_bHighlight)
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
void XGraphicsConnectLink::updateArrow()
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

void XGraphicsConnectLink::drawLinkText(QPainter *painter, const QString &text)
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

double XGraphicsConnectLink::linkLength()
{
   return this->line().length();
}

