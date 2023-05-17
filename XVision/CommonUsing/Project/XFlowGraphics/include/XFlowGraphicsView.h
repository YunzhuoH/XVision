#ifndef XFLOWGRAPHICSVIEW_H
#define XFLOWGRAPHICSVIEW_H

#include "XFlowGraphicsGlobal.h"
#include <QGraphicsView>
#include <QObject>

#pragma region View类{

class XFlowGraphicsViewPrivate;
///XView 视图类
class XFLOWGRAPHICS_PUBLIC XFlowGraphicsView: public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(bool showGridBig READ showGridBig WRITE setShowGridBig)
    Q_PROPERTY(bool showGridSmall READ showGridSmall WRITE setShowGridSmall)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor gridSmallColor READ gridSmallColor WRITE setGridSmallColor)
    Q_PROPERTY(QColor gridBigColor READ gridBigColor WRITE setGridBigColor)
    Q_PROPERTY(uint gridGap READ gridGap WRITE setGridGap)

    Q_PROPERTY(QColor magneticLineColor READ magneticLineColor WRITE setMagneticLineColor)
    Q_PROPERTY(Qt::PenStyle magneticLinePenStyle READ magneticLinePenStyle WRITE setMagneticLinePenStyle)
    Q_PROPERTY(int magneticLineWidth READ magneticLineWidth WRITE setMagneticLineWidth)
public:
    XFlowGraphicsView(QGraphicsScene *parent = nullptr);
    ~XFlowGraphicsView();
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
public:
 //*[属性接口]*
    ///是否显示大网格
    bool showGridBig() const;
    ///设置显示大网格
    void setShowGridBig(const bool &show);

    ///是否显示小网格
    bool showGridSmall() const;
    ///设置显示小网格
    void setShowGridSmall(const bool &show);

    ///背景颜色
    QColor backgroundColor() const;
    ///设置背景颜色
    void setBackgroundColor(const QColor &color);

    ///小网格线颜色
    QColor gridSmallColor() const;
    ///设置小网格线颜色
    void setGridSmallColor(const QColor &color);

    ///大网格线颜色
    QColor gridBigColor() const;
    ///设置大网格线颜色
    void setGridBigColor(const QColor &color);

    ///网格间隔
    uint gridGap() const;
    ///设置网格间隔
    void setGridGap(const uint &gap);

    //*[属性接口]*
    ///磁吸线画笔
    QColor magneticLineColor() const;
    ///设置磁吸线画笔
    void setMagneticLineColor(const QColor &color);

    ///磁吸线画笔类型
    Qt::PenStyle magneticLinePenStyle() const;
    ///设置磁吸线画笔类型
    void setMagneticLinePenStyle(const Qt::PenStyle &style);

    ///磁吸线宽度
    int magneticLineWidth() const;
    ///设置磁吸线宽度
    void setMagneticLineWidth(const int &width);

signals:
    void sgWheelEvent();
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

public:
//*[缩放工具接口]*
    ///当前缩放比例
    qreal zoomScale() const;
    ///原始缩放尺寸
    qreal zoomOriginalScaleSize() const;
    ///最大缩放比例
    qreal zoomMaxScaleSize() const;
    ///最小缩放比例
    qreal zoomMinScaleSize() const;
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

protected:
    const QScopedPointer<XFlowGraphicsViewPrivate> d_ptr;
private:
     Q_DECLARE_PRIVATE(XFlowGraphicsView)

};

#pragma endregion}

#endif // XFLOWGRAPHICSVIEW_H
