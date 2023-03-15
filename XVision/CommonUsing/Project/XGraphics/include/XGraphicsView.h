#ifndef XGRAPHICSVIEW_H
#define XGRAPHICSVIEW_H

#include "XGraphicsGlobal.h"
#include <QGraphicsView>
#include <QObject>

#pragma region View结构体{

///视图风格
struct SXGraphicsViewConfig
{
    SXGraphicsViewConfig()
    {
        bShowGrid=true;
        colBackground=QColor(70,70,70);
        colBgGridSmall=QColor(95,95,95);
        colBgGridBig=QColor(30,30,30);
        nGridGap=20;
    }
    ///背景颜色
    QColor colBackground;

    ///是否显示网格
    bool bShowGrid;
    ///小型网格大小
    QColor colBgGridSmall;
    ///大型网格大小
    QColor colBgGridBig;
    ///网格间隔
    uint nGridGap;
};
#pragma endregion}

#pragma region View类{

//XView 视图类
class XGRAPHICS_PUBLIC XGraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    XGraphicsView(QGraphicsScene *parent = nullptr);
    ~XGraphicsView();
public:
//*[常规公共接口]*
    ///缩放到该矩形范围
    void zoomToRect(const QRectF &rect);
    ///设置缩放使能
    void setZoomAble(bool able);
    ///是否缩放使能
    bool zoomAble() const
    {
        return m_bZoomAble;
    }
    ///是否在拖动
    bool draging() const
    {
        return m_bDraging;
    }

    // QWidget interface
protected:
//*[视图事件]*
//*[鼠标]*
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    // QGraphicsView interface
protected:
//*[背景绘制]*
    void drawBackground(QPainter *painter, const QRectF &r) override;

protected:
//*[内部工具接口]*
    ///放大
    void zoomUp();
    ///缩小
    void zoomDown();
protected:
    ///缩放使能
    bool m_bZoomAble=true;
    ///是否正在拖动
    bool  m_bDraging = false;
    ///右键按下
    bool  m_bRightPress = false;
    ///左键按下
    bool  m_bLeftPress = false;

    ///按下位置
    QPoint	m_ptPressPos;
    ///移动位置
    QPoint	m_ptMovePos;

public:
    ///视图配置
    SXGraphicsViewConfig* config()
    {
        return &m_config;
    }
protected:
    ///视图配置
    SXGraphicsViewConfig m_config;

};

#pragma endregion}

#endif // XGRAPHICSVIEW_H
