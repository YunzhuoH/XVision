#ifndef XVDISPLAYSCENE_H
#define XVDISPLAYSCENE_H

#include "XvDisplayGlobal.h"
#include <QGraphicsScene>

class XvDisplayView;
class XvDisplayImageItem;
class XvDisplayBaseRoiItem;
class XvDisplayScenePrivate;
class XVDISPLAY_EXPORT XvDisplayScene: public QGraphicsScene
{
    Q_OBJECT

    friend class XvDisplayView;
public:
    explicit XvDisplayScene(XvDisplayView *parView = nullptr);
    ~XvDisplayScene();
public:
    ///获取视图
    XvDisplayView* getView() const { return m_parView;}
    ///获取图像显示图元
    XvDisplayImageItem* getDisplayImageItem() const { return m_displayImageItem; }
    ///获取显示的图像
    QPixmap getDisplayImage();
    ///获取显示图像尺寸
    QSize getDisplayImageSize() const;

public://Roi
    ///设置正在绘制Roi
    void setRoiDrawing(const bool &drawing);
    ///是否正在绘制Roi
    bool roiDrawing() const;
    ///获取Roi列表
    QList<XvDisplayBaseRoiItem*> getRois() const { return m_lstRoiItems; }
    ///添加Roi
    void addRoi(XvDisplayBaseRoiItem* roi);
    ///删除Roi
    bool removeRoi(XvDisplayBaseRoiItem* roi);
    ///删除Roi
    void clearRoi();
    ///获取选择的Roi
    QList<XvDisplayBaseRoiItem*> getSelectRois() const;
    ///设置ROI可见性
    void setRoiVisible(const bool &visible);

public slots:
    ///显示图像
    bool displayImage(const QImage &image,bool bAutoFit=false);
    ///清除图像
    void clearImage();
    ///显示文本
    void addDisplayText(const QString &text,const QPointF &pt=QPointF(0,0),const double &size=1,const QColor &color=QColor(Qt::green),const bool &clear=false);
    ///清除文本
    void clearDisplayText();
protected:
    ///设置显示图像图元
    void setDisplayImageItem(XvDisplayImageItem* imageItem);
    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    ///更新显示图像
    void sgUpdataDisplayImage(const QImage &image);
    ///清除图像信号
    void sgClearDisplayImage();
    ///鼠标点击信号
    void sgMousePress(QGraphicsSceneMouseEvent* event);
    void sgMouseRelease(QGraphicsSceneMouseEvent* event);
protected:
    ///父视图
    XvDisplayView* m_parView=nullptr;
    ///图像显示Item
    XvDisplayImageItem *m_displayImageItem=nullptr;
    ///Roi图元
    QList<XvDisplayBaseRoiItem*> m_lstRoiItems;

protected:
    const QScopedPointer<XvDisplayScenePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(XvDisplayScene)



};

#endif // XVDISPLAYSCENE_H
