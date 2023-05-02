#include "XGraphicsEllipseItem.h"
#include <QGraphicsScene>
#include <QStaticText>
#include <QGraphicsSceneMouseEvent>
#include "XGraphicsConnectLink.h"


/*******************************/
//* [XGraphicsEllipseItemPrivate]
/*******************************/
class XGraphicsEllipseItemPrivate
{
    Q_DISABLE_COPY(XGraphicsEllipseItemPrivate)
    Q_DECLARE_PUBLIC(XGraphicsEllipseItem)

public:
    XGraphicsEllipseItemPrivate(XGraphicsEllipseItem *q):q_ptr(q)
    {
        itemEllipsePen.setColor(QColor(25, 150, 255));
        itemEllipsePen.setWidth(3);
        itemEllipseBrush=QBrush(QColor(Qt::white));

        selectEllipsePen.setColor(QColor(255, 150, 50));
        selectEllipsePen.setWidth(5);
        selectEllipseBrush=QBrush(QColor(Qt::white));

        selectBoundingEllipsePen.setColor(Qt::white);
        selectBoundingEllipsePen.setWidth(1);
        selectBoundingEllipsePen.setStyle(Qt::DashLine);

        connectEllipseSize=10;

    };
    virtual ~XGraphicsEllipseItemPrivate(){};

    XGraphicsEllipseItem              *const q_ptr;

    ///常规椭圆画笔
    QPen                               itemEllipsePen;
    ///常规椭圆笔刷
    QBrush                             itemEllipseBrush;

    ///选中时矩形画笔
    QPen                               selectEllipsePen;
    ///选中时矩形笔刷
    QBrush                             selectEllipseBrush;

    ///选中时边框画笔
    QPen                               selectBoundingEllipsePen;

    ///连接椭圆环尺寸
    double                             connectEllipseSize;
};



/***************************构造析构***************************/
XGraphicsEllipseItem::XGraphicsEllipseItem(QObject *parent)
  :XGraphicsItem{"","",parent},d_ptr(new XGraphicsEllipseItemPrivate(this))
{
     initItem();
}

XGraphicsEllipseItem::XGraphicsEllipseItem(QString type, QString id, QObject *parent)
    :XGraphicsItem{type,id,parent},d_ptr(new XGraphicsEllipseItemPrivate(this))
{
    initItem();
}

XGraphicsEllipseItem::~XGraphicsEllipseItem()
{

}

/***************************属性接口***************************/

QPen XGraphicsEllipseItem::itemEllipsePen() const
{
    Q_D(const XGraphicsEllipseItem);
    return d->itemEllipsePen;
}

void XGraphicsEllipseItem::setItemEllipsePen(const QPen &pen)
{
    Q_D(XGraphicsEllipseItem);
    d->itemEllipsePen=pen;
}

QBrush XGraphicsEllipseItem::itemEllipseBrush() const
{
    Q_D(const XGraphicsEllipseItem);
    return d->itemEllipseBrush;
}

void XGraphicsEllipseItem::setItemEllipseBrush(const QBrush &brush)
{
    Q_D(XGraphicsEllipseItem);
    d->itemEllipseBrush=brush;
}

QPen XGraphicsEllipseItem::selectEllipsePen() const
{
    Q_D(const XGraphicsEllipseItem);
    return d->selectEllipsePen;
}

void XGraphicsEllipseItem::setSelectEllipsePen(const QPen &pen)
{
    Q_D(XGraphicsEllipseItem);
    d->selectEllipsePen=pen;
}

QBrush XGraphicsEllipseItem::selectEllipseBrush() const
{
    Q_D(const XGraphicsEllipseItem);
    return d->selectEllipseBrush;
}

void XGraphicsEllipseItem::setSelectEllipseBrush(const QBrush &brush)
{
    Q_D(XGraphicsEllipseItem);
    d->selectEllipseBrush=brush;
}

QPen XGraphicsEllipseItem::selectBoundingEllipsePen() const
{
    Q_D(const XGraphicsEllipseItem);
    return d->selectBoundingEllipsePen;
}

void XGraphicsEllipseItem::setSelectBoundingEllipsePen(const QPen &pen)
{
    Q_D(XGraphicsEllipseItem);
    d->selectBoundingEllipsePen=pen;
}


double XGraphicsEllipseItem::connectEllipseSize() const
{
    Q_D(const XGraphicsEllipseItem);
    return d->connectEllipseSize;
}

void XGraphicsEllipseItem::setConnectEllipseSize(const double &size)
{
    Q_D(XGraphicsEllipseItem);
    d->connectEllipseSize=size;
}




/***************************内部接口***************************/

void XGraphicsEllipseItem::initItem()
{
    setPos(0,0);
    m_rWidth=80;
    m_rHeight=80;
    updateShape();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setAcceptHoverEvents(true);
    initConnectArea();
}

void XGraphicsEllipseItem::initConnectArea()
{
    m_connectEllipseRingArea=SConnectEllipseRing("Ring",m_ptCenter,m_rRadiusX,m_rRadiusY,connectEllipseSize());
}

void XGraphicsEllipseItem::drawItemText(QPainter *painter, const QString &text, const QRectF &rect)
{
    painter->save();
    painter->setFont(textFont());
    QFontMetrics fontMetrics = painter->fontMetrics();
    painter->setPen(textPen());
    painter->drawText(rect, Qt::AlignCenter | Qt::TextWrapAnywhere, text);
    painter->restore();
}

void XGraphicsEllipseItem::drawItemPix(QPainter *painter, SXItemPixData *data, const QRectF &rect)
{
    if(!data) return;
    if(!data->pixmap) return;
    if(data->pixmap.isNull()) return;
    if(!rect.isValid()) return;
    painter->save();

    QRectF rectShow=QRectF(rect.x(),rect.y(),rect.height(),rect.height());
    painter->setPen(data->getPen());
    painter->setBrush(data->getPen().brush());
    painter->drawRect(rectShow);

    painter->drawPixmap(rect.toRect(),data->pixmap);
    painter->restore();
}


/***************************XGraphicsItem接口***************************/

void XGraphicsEllipseItem::updateShape()
{
    m_ptCenter=this->pos();
    m_rRadiusX=m_rWidth/2;
    m_rRadiusY=m_rHeight/2;
    setRect({QPointF(-m_rRadiusX, -m_rRadiusY), QSizeF(m_rRadiusX*2, m_rRadiusY*2)});
    initConnectArea();
    emit shapeChanged();
}

QGraphicsItem *XGraphicsEllipseItem::item()
{
    return this;
}

bool XGraphicsEllipseItem::isInConnectArea(const QPointF &sPt)
{
    auto dataScene=sconnectDataMapToScene(m_connectEllipseRingArea.data);
    return dataScene.area.contains(sPt);
}

bool XGraphicsEllipseItem::hasConnectKey(const QString &key)
{
    return m_connectEllipseRingArea.data.key==key;
}

bool XGraphicsEllipseItem::getConnectData(const QString &key, SConnectData &connData)
{
    if(!hasConnectKey(key)) return false;
    connData=sconnectDataMapToScene( m_connectEllipseRingArea.data);
    return true;
}

bool XGraphicsEllipseItem::getConnectData(const QPointF &sPt, SConnectData &connData)
{
   auto dataScene=sconnectDataMapToScene( m_connectEllipseRingArea.data);
   if(dataScene.area.contains(sPt))
   {
       connData=dataScene;
       //计算交点
        QLineF line(dataScene.pt,sPt);
        connData.pt=getLineEllipseCross(dataScene.pt,-line.angle(),dataScene.pt,m_connectEllipseRingArea.rx,m_connectEllipseRingArea.ry);
        return true;
   }
   return false;
}

bool XGraphicsEllipseItem::getFatherConnectData(XGraphicsConnectLink *fatherLink, SConnectData &connData)
{
    if(!XGraphicsItem::getFatherConnectData(fatherLink,connData))
    {
        return false;
    }
    auto dataScene=sconnectDataMapToScene( m_connectEllipseRingArea.data);
    connData=dataScene;
    //计算交点
     QLineF line(dataScene.pt,fatherLink->fatherStartPos());
     QList<QPointF> lst;
     connData.pt=getLineEllipseCross(dataScene.pt,-line.angle(),dataScene.pt,m_connectEllipseRingArea.rx,m_connectEllipseRingArea.ry);
     return true;
}

bool XGraphicsEllipseItem::getSonConnectData(XGraphicsConnectLink *sonLink, SConnectData &connData)
{
    if(!XGraphicsItem::getSonConnectData(sonLink,connData))
    {
        return false;
    }
    auto dataScene=sconnectDataMapToScene( m_connectEllipseRingArea.data);
    connData=dataScene;
    //计算交点
     QLineF line(dataScene.pt,sonLink->sonEndPos());
     QList<QPointF> lst;
     connData.pt=getLineEllipseCross(dataScene.pt,-line.angle(),dataScene.pt,m_connectEllipseRingArea.rx,m_connectEllipseRingArea.ry);
     return true;
}

void XGraphicsEllipseItem::setItemToolTip()
{
    QString tip;
    if(!m_ItemText.isEmpty())
    {
        tip+=m_ItemText;
    }
    if(!m_ItemTip.isEmpty())
    {
        if(m_ItemText.isEmpty())
        {
            tip+=m_ItemTip;
        }
        else
        {
            tip+="\r\n"+m_ItemTip;
        }

    }
    this->setToolTip(tip);
}

void XGraphicsEllipseItem::setText(const QString &text)
{
    XGraphicsItem::setText(text);
    setItemToolTip();
}

void XGraphicsEllipseItem::setTip(const QString &tip)
{
    XGraphicsItem::setTip(tip);
    setItemToolTip();
}


/***************************QGraphicsItem接口***************************/

QRectF XGraphicsEllipseItem::boundingRect() const
{
    QRectF rect =this->rect();
    double size=connectEllipseSize()/2;
    rect.setRect(rect.x()-size,rect.y()-size,rect.width()+size*2,rect.height()+size*2);
    return rect;
}

void XGraphicsEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(XGraphicsEllipseItem);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter->save();
    if(isSelected())
    {
        painter->setPen(d->selectEllipsePen);
        painter->setBrush(d->selectEllipseBrush);
    }
    else
    {
        painter->setPen(d->itemEllipsePen);
        painter->setBrush(d->itemEllipseBrush);
    }
    if(m_bHighLight)
    {
        painter->setPen(highLightPen());
        painter->setBrush(highLightBrush());
    }
    painter->drawEllipse(m_ptCenter,m_rRadiusX,m_rRadiusY);

    painter->restore();

    if(isSelected())
    {
        painter->setPen(d->selectBoundingEllipsePen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }

    //根据长宽比判断绘制图文样式
    QRectF rectPix; //图片放中心
    QRectF rectText;//图片不存在，文本放中心
    double size;
    if(m_rRadiusX>m_rRadiusY)
    {
       size= m_rRadiusY;

    }
    else
    {
        size= m_rRadiusX;
    }
    if(!m_strShowPixKey.isEmpty())//需要显示图像,图片放中心
    {
        rectPix= QRectF((m_ptCenter-QPointF(size/2,size/2)),QSizeF(size,size));
        rectText= QRectF((m_ptCenter+QPointF(-size/2,size/2)),QSizeF(size,size/2));
    }
    else//不需要显示图像,文本放中心
    {
        rectPix=QRectF();
        rectText= QRectF((m_ptCenter-QPointF(size/2,size/2)),QSizeF(size,size));
    }
    m_ItemRectText=this->rect();

    if(!m_ItemText.isEmpty())
    {
        drawItemText(painter,m_ItemText,rectText);
    }

    if(!m_strShowPixKey.isEmpty())
    {
       if(m_mapPixData.contains(m_strShowPixKey))
        {
             auto data=m_mapPixData[m_strShowPixKey];
             drawItemPix(painter,data,rectPix);
        }

    }
    ///更新连接区域
    auto funcGetEllipseRing=[&](const SConnectEllipseRing &ring, double scale=1)
    {
        SConnectEllipseRing retRing;
        retRing.updateEllipseRing(ring.ptCenter,ring.rx,ring.ry,ring.thickness*scale);

        return retRing.data.area;
    };
    if (m_eShowConnectAreaType==EShowConnectAreaType::ShowFull)
    {
        painter->setPen(connectAreaPen());
        painter->setBrush(connectAreaBrush());

        if(m_connectEllipseRingArea.data.key==m_strShowFullKey)
        {
           painter->drawPath(funcGetEllipseRing(m_connectEllipseRingArea));
        }
        else
        {
            painter->drawPath(funcGetEllipseRing(m_connectEllipseRingArea,0.5));
        }


    }
    else if(m_eShowConnectAreaType==EShowConnectAreaType::ShowLittle)
    {
        painter->setPen(connectAreaPen());
        painter->setBrush(connectAreaBrush());
        painter->drawPath(funcGetEllipseRing(m_connectEllipseRingArea,0.5));
    }
}

QVariant XGraphicsEllipseItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange  &&  scene()) // 控件发生移动
    {
        QPointF newPos = value.toPointF(); //即将要移动的位置
        QRectF rect(0, 0, scene()->width(), scene()->height()); // 你要限制的区域
        if (!rect.contains(newPos)) // 是否在区域内
        {
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            emit posChanged();
            return newPos;
        }
        emit posChanged();
     }

    return QGraphicsEllipseItem::itemChange(change, value);
}











