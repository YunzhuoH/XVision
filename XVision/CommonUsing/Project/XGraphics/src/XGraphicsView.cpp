#include "XGraphicsView.h"

#include <QApplication>
#include <QMouseEvent>
#include <QScrollBar>

/****************************构建与析构****************************/
XGraphicsView::XGraphicsView(QGraphicsScene *parent)
    : QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setRenderHint(QPainter::Antialiasing);
    setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    setDragMode(QGraphicsView::RubberBandDrag); 
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setMouseTracking(true);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
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

/****************************内部工具接口****************************/

void XGraphicsView::zoomUp()
{
    QTransform t = transform();
    double const step   = 1.2;
    double  factor = 0;
    factor=std::pow(step, 1.0);
    if (t.m11() > 2.5)
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
    if (t.m11() < 0.5)
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
    setBackgroundBrush(m_config.colBackground);
    QGraphicsView::drawBackground(painter, r);
    if(!m_config.bShowGrid) return;
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

     QPen pSmall(m_config.colBgGridSmall, 0.5,Qt::DashLine);
     painter->setPen(pSmall);
     drawGrid(m_config.nGridGap);

     QPen pBig(m_config.colBgGridBig, 0.8);

     painter->setPen(pBig);
     drawGrid(m_config.nGridGap*10);

}


