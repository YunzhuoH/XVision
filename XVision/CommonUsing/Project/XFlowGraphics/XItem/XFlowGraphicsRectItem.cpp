#include "XFlowGraphicsRectItem.h"
#include <QGraphicsScene>
#include <QStaticText>
#include <QGraphicsSceneMouseEvent>

/*******************************/
//* [XFlowGraphicsRectItemPrivate]
/*******************************/
class XFlowGraphicsRectItemPrivate
{
    Q_DISABLE_COPY(XFlowGraphicsRectItemPrivate)
    Q_DECLARE_PUBLIC(XFlowGraphicsRectItem)

public:
    XFlowGraphicsRectItemPrivate(XFlowGraphicsRectItem *q):q_ptr(q)
    {
        rectRounded=5;

        itemRectPen.setColor(QColor(25, 150, 255));
        itemRectPen.setWidth(3);
        itemRectBrush=QBrush(QColor(Qt::white));

        selectRectPen.setColor(QColor(255, 150, 50));
        selectRectPen.setWidth(5);
        selectRectBrush=QBrush(QColor(Qt::white));

        selectBoundingRectPen.setColor(Qt::white);
        selectBoundingRectPen.setWidth(1);
        selectBoundingRectPen.setStyle(Qt::DashLine);

        connectRectSize=20;

    };
    virtual ~XFlowGraphicsRectItemPrivate(){};

    XFlowGraphicsRectItem              *const q_ptr;

    ///矩形圆角大小
    double                          rectRounded;

    ///连接矩形尺寸
    double                          connectRectSize;

    ///常规矩形画笔
    QPen                            itemRectPen;
    ///常规矩形笔刷
    QBrush                          itemRectBrush;

    ///选中时矩形画笔
    QPen                            selectRectPen;
    ///选中时矩形笔刷
    QBrush                          selectRectBrush;

    ///选中时边框画笔
    QPen                            selectBoundingRectPen;

};


/***************************构造析构***************************/
XFlowGraphicsRectItem::XFlowGraphicsRectItem(QObject *parent)
    :XFlowGraphicsItem{"","",parent},d_ptr(new XFlowGraphicsRectItemPrivate(this))
{
    initItem();
}

XFlowGraphicsRectItem::XFlowGraphicsRectItem(QString type,QString id,QObject *parent)
    :XFlowGraphicsItem{type,id,parent},d_ptr(new XFlowGraphicsRectItemPrivate(this))
{
    initItem();
}

XFlowGraphicsRectItem::~XFlowGraphicsRectItem()
{

}
/***************************属性接口***************************/

double XFlowGraphicsRectItem::rectRounded() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->rectRounded;
}

void XFlowGraphicsRectItem::setRectRounded(const double &rounded)
{
    Q_D(XFlowGraphicsRectItem);
    d->rectRounded=rounded;
}

double XFlowGraphicsRectItem::connectRectSize() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->connectRectSize;
}

void XFlowGraphicsRectItem::setConnectRectSize(const double &size)
{
    Q_D(XFlowGraphicsRectItem);
    d->connectRectSize=size;
}



QPen XFlowGraphicsRectItem::itemRectPen() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->itemRectPen;
}

void XFlowGraphicsRectItem::setItemRectPen(const QPen &pen)
{
    Q_D(XFlowGraphicsRectItem);
    d->itemRectPen=pen;
}

QBrush XFlowGraphicsRectItem::itemRectBrush() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->itemRectBrush;
}

void XFlowGraphicsRectItem::setItemRectBrush(const QBrush &brush)
{
    Q_D(XFlowGraphicsRectItem);
    d->itemRectBrush=brush;
}


QPen XFlowGraphicsRectItem::selectRectPen() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->selectRectPen;
}

void XFlowGraphicsRectItem::setSelectRectPen(const QPen &pen)
{
    Q_D(XFlowGraphicsRectItem);
    d->selectRectPen=pen;
}



QBrush XFlowGraphicsRectItem::selectRectBrush() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->selectRectBrush;
}

void XFlowGraphicsRectItem::setSelectRectBrush(const QBrush &brush)
{
    Q_D(XFlowGraphicsRectItem);
    d->selectRectBrush=brush;
}


QPen XFlowGraphicsRectItem::selectBoundingRectPen() const
{
    Q_D(const XFlowGraphicsRectItem);
    return d->selectBoundingRectPen;
}

void XFlowGraphicsRectItem::setSelectBoundingRectPen(const QPen &pen)
{
    Q_D(XFlowGraphicsRectItem);
    d->selectBoundingRectPen=pen;
}



/***************************初始化***************************/
void XFlowGraphicsRectItem::initItem()
{
    setPos(0,0);
    m_rWidth=150;
    m_rHeight=50;
    updateShape();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setAcceptHoverEvents(true);
    initConnectArea();
}

void XFlowGraphicsRectItem::initConnectArea()
{
     m_mapConnectRectArea.clear();
     addConnectRect("Left",m_ptLeft);
     addConnectRect("Right",m_ptRight);
     addConnectRect("Top",m_ptTop);
     addConnectRect("Bottom",m_ptBottom);
}

void XFlowGraphicsRectItem::addConnectRect(const QString &key, const QPointF &pt)
{
    double rSize=connectRectSize();
    double rPos=rSize/2;
    QRectF rect = QRectF((pt - QPointF(rPos, rPos)), QSizeF(rSize, rSize));
    if(!m_mapConnectRectArea.contains(key))
    {

        m_mapConnectRectArea.insert(key,SConnectRect(key,pt,rect));
    }
}


/***************************更新***************************/
void XFlowGraphicsRectItem::updateShape()
{
    setRect({QPointF(-m_rWidth / 2, -m_rHeight / 2), QSizeF(m_rWidth, m_rHeight)});
    QRectF rect=this->boundingRect();
    m_ptCenter = pos();
    m_ptLeft=QPointF(rect.left(),0);
    m_ptRight=QPointF(rect.right(),0);
    m_ptTop=QPointF(0,rect.top());
    m_ptBottom=QPointF(0,rect.bottom());

    initConnectArea();
    emit shapeChanged();
}

/***************************重写父类接口***************************/

QGraphicsItem *XFlowGraphicsRectItem::item()
{
    return this;
}

bool XFlowGraphicsRectItem::isInConnectArea(const QPointF &sPt)
{
    foreach (auto data, m_mapConnectRectArea)
    {
        auto dataScene= sconnectDataMapToScene(data.data);
        if(dataScene.area.contains(sPt))
        {
            return true;
        }
    }
    return false;
}

bool XFlowGraphicsRectItem::hasConnectKey(const QString &key)
{
    return m_mapConnectRectArea.contains(key);
}

bool XFlowGraphicsRectItem::getConnectData(const QString &key, SConnectData &connData)
{
      if(m_mapConnectRectArea.contains(key))
      {
          connData= sconnectDataMapToScene(m_mapConnectRectArea[key].data);
          return true;
      }
      else
      {
          return false;
      }
}

bool XFlowGraphicsRectItem::getConnectData(const QPointF &sPt, SConnectData &connData)
{
    foreach (auto data, m_mapConnectRectArea)
    {
         auto dataScene= sconnectDataMapToScene(data.data);
         if(dataScene.area.contains(sPt))
         {
             connData=dataScene;
             return true;
         }
    }
    return false;
}



QRectF XFlowGraphicsRectItem::boundingRect() const
{
    double rSize=connectRectSize();
    double r=rSize/2;
    QRectF rect = QGraphicsRectItem::boundingRect();
    return rect.adjusted(r,r,-r,-r);
}

void XFlowGraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(XFlowGraphicsRectItem);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter->save();
    if(isSelected())
    {
        painter->setPen(d->selectRectPen);
        painter->setBrush(d->selectRectBrush);
    }
    else
    {
        painter->setPen(d->itemRectPen);
        painter->setBrush(d->itemRectBrush);
    }
    if(m_bHighLight)
    {
        painter->setPen(highLightPen());
        painter->setBrush(highLightBrush());
    }
    painter->drawRoundedRect(this->boundingRect(),d->rectRounded,d->rectRounded);
    painter->restore();

    if(isSelected())
    {
        painter->setPen(d->selectBoundingRectPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(QGraphicsRectItem::boundingRect());
    }


    double rLeftSize=0;
    if(!m_strShowPixKey.isEmpty())//需要显示图像
    {
        rLeftSize=this->boundingRect().height();
    }
    QRectF rectText = this->boundingRect();
    rectText.setRect(rectText.x()+rLeftSize,rectText.y(),rectText.width()-rLeftSize,rectText.height());
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
             drawItemPix(painter,data,PIX_OFFSET);
        }

    }
    auto funcGetLittleRect=[&](const QRectF &rect, double scale=0.5)
    {
        QPointF center=rect.center();
        double rSize=rect.width()*scale;
        double rPos=rSize/2;

        QRectF retRect = QRectF((center - QPointF(rPos, rPos)), QSizeF(rSize, rSize));
        return retRect;
    };
    if (m_eShowConnectAreaType==EShowConnectAreaType::ShowFull)
    {
        painter->setPen(connectAreaPen());
        painter->setBrush(connectAreaBrush());

        int nCount=m_mapConnectRectArea.count();

        foreach (auto data, m_mapConnectRectArea)
        {
            if(data.data.key==m_strShowFullKey)
            {

               painter->drawRect(data.rect);
            }
            else
            {
                painter->drawRect(funcGetLittleRect(data.rect));
            }

        }

    }
    else if(m_eShowConnectAreaType==EShowConnectAreaType::ShowLittle)
    {
        painter->setPen(connectAreaPen());
        painter->setBrush(connectAreaBrush());
        foreach (auto data, m_mapConnectRectArea)
        {
            painter->drawRect(funcGetLittleRect(data.rect));
        }
    }

}

/***************************内部辅助接口***************************/
void XFlowGraphicsRectItem::drawItemText(QPainter *painter,const QString &text,const QRectF &rect)
{
    painter->save();
    painter->setFont(textFont());
    QFontMetrics fontMetrics = painter->fontMetrics();
    painter->setPen(textPen());
    painter->drawText(rect, Qt::AlignCenter | Qt::TextWrapAnywhere, text);
    painter->restore();

}

void XFlowGraphicsRectItem::drawItemPix(QPainter *painter,  SXItemPixData* data,double widthOffset)
{
    Q_D(XFlowGraphicsRectItem);
    if(!data) return;
    if(!data->pixmap) return;
    if(data->pixmap.isNull()) return;
    painter->save();
    painter->setPen(data->getPen());
    painter->setBrush(data->getPen().brush());

    QRectF rect = this->boundingRect();
    auto boundWidth=d->itemRectPen.width()/2.0;
    QRectF rectShow=QRectF(rect.left()+boundWidth,rect.top()+boundWidth,rect.height()-boundWidth*2,rect.height()-boundWidth*2);
    painter->drawRoundedRect(rectShow,d->rectRounded-boundWidth,d->rectRounded-boundWidth);

    double width=rectShow.height()-widthOffset;
    QRectF rectResize=QRectF(rectShow.x()+widthOffset/2,rectShow.y()+widthOffset/2,width,width);
    painter->drawPixmap(rectResize.toRect(),data->pixmap);

    painter->restore();
}

/***************************限制位置***************************/

QVariant XFlowGraphicsRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
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

    return QGraphicsRectItem::itemChange(change, value);

}


/***************************重写父类接口***************************/
//*[工具接口]*
void XFlowGraphicsRectItem::setItemToolTip()
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
void XFlowGraphicsRectItem::setText(const QString &text)
{
    XFlowGraphicsItem::setText(text);
    setItemToolTip();
}

void XFlowGraphicsRectItem::setTip(const QString &tip)
{
    XFlowGraphicsItem::setTip(tip);
    setItemToolTip();
}







