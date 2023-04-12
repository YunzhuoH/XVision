#include "XGraphicsView.h"

#include <QApplication>
#include <QMouseEvent>
#include <QScrollBar>

/*******************************/
//* [XGraphicsViewPrivate]
/*******************************/
class XGraphicsViewPrivate
{
    Q_DISABLE_COPY(XGraphicsViewPrivate)
    Q_DECLARE_PUBLIC(XGraphicsView)

public:
    XGraphicsViewPrivate(XGraphicsView *q):q_ptr(q)
    {
        showGridBig=true;
        showGridSmall=true;
        backgroundColor=QColor(70,70,70);
        gridSmallColor=QColor(95,95,95);
        gridBigColor=QColor(30,30,30);
        gridGap=20;

        magneticLineColor=QColor(Qt::white);
        magneticLinePenStyle=Qt::DashLine;
        magneticLineWidth=1;
    };
    virtual ~XGraphicsViewPrivate(){};

    XGraphicsView              *const q_ptr;

    ///是否显示大网格
    bool                       showGridBig;
    ///是否显示小网格
    bool                       showGridSmall;

    ///背景颜色
    QColor                     backgroundColor;
    ///小型网格线颜色
    QColor                     gridSmallColor;
    ///大型网格线颜色
    QColor                     gridBigColor;
    ///网格间隔
    uint                       gridGap;

    ///磁吸线画笔
    QColor                      magneticLineColor;
    ///磁吸线画笔类型
    Qt::PenStyle                magneticLinePenStyle;
    ///磁吸线宽度
    int                         magneticLineWidth;
};

/****************************构建与析构****************************/
XGraphicsView::XGraphicsView(QGraphicsScene *parent)
    : QGraphicsView(parent),d_ptr(new XGraphicsViewPrivate(this))
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setRenderHints(QPainter::Antialiasing| QPainter::SmoothPixmapTransform);
    setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    setDragMode(QGraphicsView::RubberBandDrag); 
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setMouseTracking(true);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setBackgroundBrush(d_ptr->backgroundColor);
}

XGraphicsView::~XGraphicsView()
{

}

/****************************常规公共接口****************************/

void XGraphicsView::zoomToRect(const QRectF &rect)
{
    this->fitInView(rect, Qt::AspectRatioMode::KeepAspectRatio);
}

void XGraphicsView::setZoomAble(bool able)
{
    m_bZoomAble=able;
}
/****************************属性接口****************************/
bool XGraphicsView::showGridBig() const
{
    Q_D(const XGraphicsView);
    return d->showGridBig;
}

void XGraphicsView::setShowGridBig(const bool &show)
{
    Q_D(XGraphicsView);
    d->showGridBig=show;
}

bool XGraphicsView::showGridSmall() const
{
    Q_D(const XGraphicsView);
    return d->showGridSmall;
}

void XGraphicsView::setShowGridSmall(const bool &show)
{
    Q_D(XGraphicsView);
    d->showGridSmall=show;
}

QColor XGraphicsView::backgroundColor() const
{
    Q_D(const XGraphicsView);
    return d->backgroundColor;
}

void XGraphicsView::setBackgroundColor(const QColor &color)
{
    Q_D(XGraphicsView);
    d->backgroundColor=color;
    setBackgroundBrush(d->backgroundColor);
}

QColor XGraphicsView::gridSmallColor() const
{
    Q_D(const XGraphicsView);
    return d->gridSmallColor;
}

void XGraphicsView::setGridSmallColor(const QColor &color)
{
    Q_D(XGraphicsView);
    d->gridSmallColor=color;
}

QColor XGraphicsView::gridBigColor() const
{
    Q_D(const XGraphicsView);
    return d->gridBigColor;
}

void XGraphicsView::setGridBigColor(const QColor &color)
{
    Q_D(XGraphicsView);
    d->gridBigColor=color;
}

uint XGraphicsView::gridGap() const
{
    Q_D(const XGraphicsView);
    return d->gridGap;
}

void XGraphicsView::setGridGap(const uint &gap)
{
    Q_D(XGraphicsView);
    d->gridGap=gap;
}


QColor XGraphicsView::magneticLineColor() const
{
    Q_D(const XGraphicsView);
    return d->magneticLineColor;
}

void XGraphicsView::setMagneticLineColor(const QColor &color)
{
    Q_D(XGraphicsView);
    d->magneticLineColor=color;
}

Qt::PenStyle XGraphicsView::magneticLinePenStyle() const
{
    Q_D(const XGraphicsView);
    return d->magneticLinePenStyle;
}

void XGraphicsView::setMagneticLinePenStyle(const Qt::PenStyle &style)
{
    Q_D(XGraphicsView);
    d->magneticLinePenStyle=style;
}

int XGraphicsView::magneticLineWidth() const
{
    Q_D(const XGraphicsView);
    return d->magneticLineWidth;
}

void XGraphicsView::setMagneticLineWidth(const int &width)
{
    Q_D(XGraphicsView);
    d->magneticLineWidth=width;
}

/****************************内部工具接口****************************/

void XGraphicsView::zoomUp()
{

    QTransform t = transform();
    double const step   = 1.2;
    double  factor = 0;
    factor=std::pow(step, 1.0);

    auto temp=t.scale(factor,factor);
    auto rectUp= temp.mapRect(this->sceneRect());
    auto rectScene=this->sceneRect();
    if(rectUp.width()>rectScene.width()*4)
    {
        return;
    }
    else
    {
        scale(factor, factor);
    }

}

void XGraphicsView::zoomDown()
{
    QTransform t = transform();
    double const step   = 1.2;
    double  factor = 0;
    factor = std::pow(step, -1.0);

    auto temp=t.scale(factor,factor);
    auto rectDown= temp.mapRect(this->sceneRect());
    auto rectScene=this->sceneRect();
    if(rectDown.width()<rectScene.width()/4)
    {
        return;
    }
    else
    {
       scale(factor, factor);
    }
}

/****************************视图事件****************************/

void XGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);    
        viewport()->setCursor(Qt::ArrowCursor);
        m_bRightPress = true;
        m_bLeftPress=false;
    }
    else
    {
        setDragMode(QGraphicsView::RubberBandDrag);
        viewport()->setCursor(Qt::ArrowCursor);
        m_bRightPress = false;
        m_bLeftPress=true;
    }
    m_ptPressPos = event->pos();
    QGraphicsView::mousePressEvent(event);
}

void XGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    QApplication::restoreOverrideCursor();
    m_bRightPress = false;
    m_bLeftPress=false;
    m_bDraging=false;
    setDragMode(QGraphicsView::NoDrag);

}

void XGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
    if (m_bRightPress)
    {
        viewport()->setCursor(Qt::OpenHandCursor);
        m_bDraging = true;
        QPointF disPointF = event->pos() - m_ptPressPos;
        m_ptPressPos = event->pos();
        QScrollBar *hBar = horizontalScrollBar();
        QScrollBar *vBar = verticalScrollBar();
        hBar->setValue(hBar->value() + (isRightToLeft() ? disPointF.rx() : -disPointF.rx()));
        vBar->setValue(vBar->value() - disPointF.ry());
    }
    m_ptMovePos = event->pos();
    QGraphicsView::mouseMoveEvent(event);
}

void XGraphicsView::wheelEvent(QWheelEvent *event)
{   
    QPoint delta = event->angleDelta();

    if (delta.y() == 0)
    {
      event->ignore();
      return;
    }
    double d = delta.y() / std::abs(delta.y());

    if(!m_bZoomAble) return;
    if (d > 0.0)
    {
        zoomUp();
    }
    else
    {
       zoomDown();
    }

}



void XGraphicsView::drawBackground(QPainter *painter, const QRectF &r)
{
    Q_D(XGraphicsView);
    QGraphicsView::drawBackground(painter, r);
    if(!d->showGridBig&&!d->showGridSmall) return;
    auto drawGrid =
       [&](double gridStep)
       {
         auto   windowRect = rect();
         QPointF tl = mapToScene(windowRect.topLeft());
         QPointF br = mapToScene(windowRect.bottomRight());

         double left   = std::floor(tl.x() / gridStep - 0.5);
         double right  = std::floor(br.x() / gridStep + 1.0);
         double bottom = std::floor(tl.y() / gridStep - 0.5);
         double top    = std::floor (br.y() / gridStep + 1.0);

         for (int xi = int(left); xi <= int(right); ++xi)
         {
           QLineF line(xi * gridStep, bottom * gridStep,
                       xi * gridStep, top * gridStep );

           painter->drawLine(line);
         }

         for (int yi = int(bottom); yi <= int(top); ++yi)
         {
           QLineF line(left * gridStep, yi * gridStep,
                       right * gridStep, yi * gridStep );

           painter->drawLine(line);
         }
       };


     QBrush bBrush = backgroundBrush();

     if(d->showGridSmall)
     {
        QPen pSmall(d->gridSmallColor, 0.5,Qt::DashLine);
        painter->setPen(pSmall);
        drawGrid(d->gridGap);
     }
     if(d->showGridBig)
     {
        QPen pBig(d->gridBigColor, 0.8);
        painter->setPen(pBig);
        drawGrid(d->gridGap*10);
     }

}



