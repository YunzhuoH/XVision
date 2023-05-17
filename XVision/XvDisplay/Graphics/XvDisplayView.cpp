#include "XvDisplayView.h"
#include "XvDisplayScene.h"

#include <QWheelEvent>
#include <QScrollBar>

#include "XvDisplayImageItem.h"

/*******************************/
//* [XvDisplayViewPrivate]
/*******************************/
#define Background_Pix_Size 32
class XvDisplayViewPrivate
{
    Q_DISABLE_COPY(XvDisplayViewPrivate)
    Q_DECLARE_PUBLIC(XvDisplayView)

public:
    XvDisplayViewPrivate(XvDisplayView *q):q_ptr(q)
    {
        backgroundPixmapSize=Background_Pix_Size;
        backgroundFillColor=QColor(255,255,255);
        backgroundGridColor=QColor(100,100,100,100);
        resizeToFif=true;
        doubleClickToFit=true;

        maxZoomCoeff=ViewMaxZoomCoeff_Default;
        minZoomCoeff=ViewMinZoomCoeff_Default;
    };
    virtual ~XvDisplayViewPrivate(){};

public:
    void init();
    void updateBackground();
public:
    XvDisplayView              *const q_ptr;

    QPixmap                     backgroundPixmap;//背景图像
    int                         backgroundPixmapSize;//背景图像大小
    QColor                      backgroundFillColor;//背景图像填充色
    QColor                      backgroundGridColor;//背景图像网格色

    bool                        resizeToFif;//是否重置尺寸缩放至合适大小
    bool                        doubleClickToFit;//是否双击缩放至合适大小

    double                      maxZoomCoeff;//最大缩放系数
    double                      minZoomCoeff;//最大缩放系数
};

void XvDisplayViewPrivate::init()
{
    updateBackground();
}

void XvDisplayViewPrivate::updateBackground()
{
    int pixSizeHalf=backgroundPixmapSize/2;
    backgroundPixmap=QPixmap(backgroundPixmapSize, backgroundPixmapSize);
    backgroundPixmap.fill(backgroundFillColor);
    QPainter painter(&backgroundPixmap);
    painter.fillRect(0, 0, pixSizeHalf, pixSizeHalf, backgroundGridColor);
    painter.fillRect(pixSizeHalf, pixSizeHalf, pixSizeHalf, pixSizeHalf, backgroundGridColor);
    painter.end();
}

/*******************************/
//* [XvDisplayView]
/*******************************/

XvDisplayView::XvDisplayView(QWidget *parent)
 : QGraphicsView(parent),
   d_ptr(new XvDisplayViewPrivate(this)),
   m_scene(new XvDisplayScene(this))
{
    d_ptr->init();
    init();
}

XvDisplayView::~XvDisplayView()
{

}

void XvDisplayView::init()
{
    //设置View属性
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::RubberBandDrag);
    setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setMouseTracking(true);
    setCacheMode(QGraphicsView::CacheBackground);

    // 设置场景范围
    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);
}

int XvDisplayView::backgroundPixmapSize() const
{
    Q_D(const XvDisplayView);
    return d->backgroundPixmapSize;
}

void XvDisplayView::setBackgroundPixmapSize(const int &size)
{
    Q_D(XvDisplayView);
    d->backgroundPixmapSize=size;
    d->updateBackground();
}

QColor XvDisplayView::backgroundFillColor() const
{
    Q_D(const XvDisplayView);
    return d->backgroundFillColor;
}

void XvDisplayView::setBackgroundFillColor(const QColor &color)
{
    Q_D(XvDisplayView);
    d->backgroundFillColor=color;
    d->updateBackground();
}

QColor XvDisplayView::backgroundGridColor() const
{
    Q_D(const XvDisplayView);
    return d->backgroundGridColor;
}

void XvDisplayView::setBackgroundGridColor(const QColor &color)
{
    Q_D(XvDisplayView);
    d->backgroundGridColor=color;
    d->updateBackground();
}

bool XvDisplayView::resizeToFif() const
{
    Q_D(const XvDisplayView);
    return d->resizeToFif;
}

void XvDisplayView::setResizeToFif(const bool &enable)
{
    Q_D(XvDisplayView);
    d->resizeToFif=enable;
}

bool XvDisplayView::doubleClickToFit() const
{
    Q_D(const XvDisplayView);
    return d->doubleClickToFit;
}

void XvDisplayView::setDoubleClickToFit(const bool &enable)
{
    Q_D(XvDisplayView);
    d->doubleClickToFit=enable;
}

double XvDisplayView::maxZoomCoeff() const
{
    Q_D(const XvDisplayView);
    return d->maxZoomCoeff;
}

void XvDisplayView::setMaxZoomCoeff(const double &coeff)
{
    Q_D(XvDisplayView);
    d->maxZoomCoeff=coeff;
}

double XvDisplayView::minZoomCoeff() const
{
    Q_D(const XvDisplayView);
    return d->minZoomCoeff;
}

void XvDisplayView::setMinZoomCoeff(const double &coeff)
{
    Q_D(XvDisplayView);
    d->minZoomCoeff=coeff;
}


/****************************公共接口****************************/

void XvDisplayView::updateDisplayFit()
{
    int imageWidth=m_scene->getDisplayImageSize().width();
    int imageHeight=m_scene->getDisplayImageSize().height();
    if(this->width()<1||imageWidth<1)
    {
        return;
    }
    //图片自适应方法
    double winWidth=this->width();
    double winHeight=this->height();
    double ScaleWidth=(imageWidth+1)/winWidth;
    double ScaleHeight=(imageHeight+1)/winHeight;
    double row1,column1;
    double s=0;
    if(ScaleWidth>=ScaleHeight)
    {

        row1= -(1) * ((winHeight * ScaleWidth) -imageHeight) / 2;
        column1 = 0  ;
        s=1/ScaleWidth;
    }
    else
    {
        row1= 0;
        column1 = -(1.0) * ((winWidth * ScaleHeight) - imageWidth) / 2 ;
        s=1/ScaleHeight;
    }

    if(m_rZoomFit!=s||m_rFitPixX!=column1*s)
    {
        m_rZoomFit=s;
        m_rFitPixX=column1*s;
        m_rFitPixY=row1*s;
        zoomToDisplayFit();
    }
}

void XvDisplayView::zoomToDisplayFit()
{
    zoomByValue(m_rZoomFit);
    QScrollBar *pHbar =  this->horizontalScrollBar();
    pHbar->setSliderPosition(m_rFitPixX);
    QScrollBar *pVbar = this->verticalScrollBar();
    pVbar->setSliderPosition(m_rFitPixY);
}

void XvDisplayView::zoomDown()
{
    Q_D(XvDisplayView);
    if(m_rZoomValue <= d->minZoomCoeff)//最小缩小
    {
        return;
    }
    else
    {
        double tmp=m_rZoomValue;
        tmp*=0.9;//每次缩小10%
        zoomByValue(tmp);

        QScrollBar *pHbar =  this->horizontalScrollBar();
        pHbar->setSliderPosition(pHbar->sliderPosition());
        QScrollBar *pVbar = this->verticalScrollBar();
        pVbar->setSliderPosition(pVbar->sliderPosition());

    }
}

void XvDisplayView::zoomUp()
{
    Q_D(XvDisplayView);
    if(m_rZoomValue >= d->maxZoomCoeff)//最大放大
    {
        return;
    }
    else
    {
        double tmp=m_rZoomValue;
        tmp*=1.1;//每次放大10%
        zoomByValue(tmp);
        QScrollBar *pHbar =  this->horizontalScrollBar();
        pHbar->setSliderPosition(pHbar->sliderPosition());
        QScrollBar *pVbar = this->verticalScrollBar();
        pVbar->setSliderPosition(pVbar->sliderPosition());

    }
}
/****************************内部工具接口****************************/

void XvDisplayView::zoomByValue(const double &val)
{
    double tmp=val/m_rZoomValue;
    //绝对缩放
    m_rZoomValue*=tmp;
    //相对上一次缩放
    this->scale(tmp,tmp);
}

/****************************视图事件****************************/

void XvDisplayView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void XvDisplayView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void XvDisplayView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void XvDisplayView::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_D(XvDisplayView);
    if(d->doubleClickToFit)
    {
        zoomToDisplayFit();
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void XvDisplayView::wheelEvent(QWheelEvent *event)
{
    Q_D(XvDisplayView);
    int deltaY=event->angleDelta().y();
    if((deltaY > 0)&&(m_rZoomValue >= d->maxZoomCoeff))//最大放大
    {
        return;
    }
    else if((deltaY< 0)&&(m_rZoomValue <= d->minZoomCoeff))//最小缩小
    {
        return;
    }
    else
    {
        double tmp=m_rZoomValue;
        if(deltaY > 0)//鼠标滚轮向前滚动
        {
            tmp*=1.1;//每次放大10%
        }
        else
        {
            tmp*=0.9;//每次缩小10%
        }
        zoomByValue(tmp);

        qreal x=event->position().x()-this->width()/2;
        qreal y=event->position().y()-this->height()/2;
        //缩放时 鼠标位置跟随
        if(deltaY > 0)
        {
            QScrollBar *pHbar =  this->horizontalScrollBar();
            pHbar->setSliderPosition(pHbar->sliderPosition()+x*0.1);
            QScrollBar *pVbar = this->verticalScrollBar();
            pVbar->setSliderPosition(pVbar->sliderPosition()+y*0.1);
        }
        else
        {
            QScrollBar *pHbar =  this->horizontalScrollBar();
            pHbar->setSliderPosition(pHbar->sliderPosition()-x*0.1);
            QScrollBar *pVbar = this->verticalScrollBar();
            pVbar->setSliderPosition(pVbar->sliderPosition()-y*0.1);
        }

    }

}

void XvDisplayView::resizeEvent(QResizeEvent *event)
{
    Q_D(XvDisplayView);
    if(d->resizeToFif)
    {
        updateDisplayFit();
    }
    QGraphicsView::resizeEvent(event);
}

void XvDisplayView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_D(XvDisplayView);
    painter->drawTiledPixmap(rect,d->backgroundPixmap);
}




