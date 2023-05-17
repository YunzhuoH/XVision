/********************************************************
*XvDisplayView:图像显示View
********************************************************/
#ifndef XVDISPLAYVIEW_H
#define XVDISPLAYVIEW_H

#include "XvDisplayGlobal.h"
#include <QGraphicsView>

#define ViewMaxZoomCoeff_Default 50
#define ViewMinZoomCoeff_Default 0.01


class XvDisplayScene;
class XvDisplayImageItem;
class XvDisplayViewPrivate;
class XVDISPLAY_EXPORT XvDisplayView: public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(int backgroundPixmapSize READ backgroundPixmapSize WRITE setBackgroundPixmapSize)
    Q_PROPERTY(QColor backgroundFillColor READ backgroundFillColor WRITE setBackgroundFillColor)
    Q_PROPERTY(QColor backgroundGridColor READ backgroundGridColor WRITE setBackgroundGridColor)
    Q_PROPERTY(bool resizeToFif READ resizeToFif WRITE setResizeToFif)
    Q_PROPERTY(bool doubleClickToFit READ doubleClickToFit WRITE setDoubleClickToFit)
    Q_PROPERTY(double maxZoomCoeff READ maxZoomCoeff WRITE setMaxZoomCoeff)
    Q_PROPERTY(double minZoomCoeff READ minZoomCoeff WRITE setMinZoomCoeff)

    friend class XvDisplayScene;
public:
    explicit XvDisplayView(QWidget *parent = 0);
    ~XvDisplayView();
protected://初始化接口
    ///初始化
    void init();
    //属性接口
public:
    ///背景格子大小
    int backgroundPixmapSize() const;
    ///设置背景格子大小
    void setBackgroundPixmapSize(const int &size);
    ///背景格子填充色
    QColor backgroundFillColor() const;
    ///设置背景格子填充色
    void setBackgroundFillColor(const QColor &color);
    ///背景格子网格色
    QColor backgroundGridColor() const;
    ///设置背景格子网格色
    void setBackgroundGridColor(const QColor &color);

    ///是否重置尺寸缩放至合适大小
    bool resizeToFif() const;
    ///设置是否重置尺寸缩放至合适大小
    void setResizeToFif(const bool &enable);
    ///是否双击缩放至合适大小
    bool doubleClickToFit() const;
    ///设置是否双击缩放至合适大小
    void setDoubleClickToFit(const bool &enable);

    ///最大缩放系数
    double maxZoomCoeff() const;
    ///设置最大缩放系数
    void setMaxZoomCoeff(const double &coeff);

    ///最小缩放系数
    double minZoomCoeff() const;
    ///设置最小缩放系数
    void setMinZoomCoeff(const double &coeff);
    // 公共接口
public:
    ///获取场景
    XvDisplayScene* getScene() const { return m_scene;}

public slots:
    ///更新缩放合适大小
    void updateDisplayFit();
    ///缩放到合适显示大小
    void zoomToDisplayFit();

    ///缩小
    void zoomDown();
    ///放大
    void zoomUp();

    // 内部接口
protected:
    ///进行缩放
    void zoomByValue(const double &val);
    // QGraphicsView interface
protected:
//*[视图事件]*
//*[鼠标]*
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
//*[尺寸改变]*
    void resizeEvent(QResizeEvent *event) override;
//*[背景绘制]*
    void drawBackground(QPainter *painter, const QRectF &r) override;

protected: //view控件状态
    ///当前缩放值
    double m_rZoomValue=1;
    ///缩放至适合比例
    double m_rZoomFit=1;
    ///适合图像X坐标
    double m_rFitPixX=0;
    ///适合图像Y坐标
    double m_rFitPixY=0;

protected:
    ///显示的场景
    XvDisplayScene *m_scene=nullptr;
protected:
    const QScopedPointer<XvDisplayViewPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(XvDisplayView)

};

#endif // XVDISPLAYVIEW_H
