#ifndef XFLOWGRAPHICSSCENE_H
#define XFLOWGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "XFlowGraphicsGlobal.h"

/*
*   定义:
*   Item/item/QItem/qItem:QGraphicsItem
*   XItem/xItem:XFlowGraphicsItem
*   XLink/xLink:XFlowGraphicsConnectLink
*
*/


#pragma region Scene类{
class XFlowGraphicsView;
class XFlowGraphicsItemDelegateFactory;
class XFlowGraphicsLinkDelegateFactory;
class XFlowGraphicsItem;
class XFlowGraphicsConnectLink;
class XFlowGraphicsScenePrivate;
///XScene场景类
class XFLOWGRAPHICS_PUBLIC XFlowGraphicsScene: public QGraphicsScene
{
    Q_OBJECT

public:
    XFlowGraphicsScene(QObject *parent = nullptr);
    ~XFlowGraphicsScene();
public:
//*[常规公共接口]*
    ///场景Id
    QString sceneId() const
    {
        return m_SceneId;
    }
    ///场景Tag
    QVariant sceneTag() const
    {
        return m_SceneTag;
    }
    ///设置场景Tag
    void setSceneTag(const QVariant& tag)
    {
        m_SceneTag=tag;
    }

    ///场景QObject指针Tag
    QObject* sceneQPtrTag() const
    {
        return m_SceneQPtrTag;
    }
    ///设置场景QObject指针Tag
    void setSceneQPtrTag(QObject* qptrTag)
    {
        m_SceneQPtrTag=qptrTag;
    }

    ///获取View视图
    XFlowGraphicsView* getView();
    ///获取Item委托生产工厂
    XFlowGraphicsItemDelegateFactory* xItemDelegateFactory() const { return m_pXItemFactory;}
    ///设置Item委托生产工厂
    void setXItemDelegateFactory(XFlowGraphicsItemDelegateFactory* factory);

    ///获取Link委托生产工厂
    XFlowGraphicsLinkDelegateFactory* xLinkDelegateFactory() const { return m_pXLinkFactory;}

    ///设置Link委托生产工厂
    void setXLinkDelegateFactory(XFlowGraphicsLinkDelegateFactory* factory);


    ///设置显示矩形
    void setDisplayRect(const QRectF &rect);
     ///设置显示矩形
    inline void setDisplayRect(qreal x, qreal y, qreal w, qreal h)
    { setDisplayRect(QRectF(x, y, w, h)); }

    ///缩放到Item范围
    void zoomToItemRect();
public slots:
    ///设置场景使能
    void setEnabled(bool enable);
public:

//*[XItem字典]*
    ///添加Item
    void addXItem(XFlowGraphicsItem* xItem);
    ///删除Item(不做指针删除处理)
    bool removeXItem(XFlowGraphicsItem* xItem);
    ///通过Id获取XItem
    XFlowGraphicsItem* getXItemById(const QString &id);
    ///通过Type获取XItems
    QList<XFlowGraphicsItem*> getXItemsByType(const QString &type);
    ///场景XItems
    QMap<QString,XFlowGraphicsItem*> getXItems() const
    {
        return m_mapXItem;
    }
//*[XLink字典]*
    ///添加Link
    void addXLink(XFlowGraphicsConnectLink* xLink);
    ///删除Link(不做指针删除处理)
    void removeXLink(XFlowGraphicsConnectLink* xLink);
    ///通过Id获取Link
    XFlowGraphicsConnectLink *getXLinkById(const QString &id);

    QMap<QString,XFlowGraphicsConnectLink*> getXLinks() const
    {
         return m_mapXLink;
    }
//*[字典清除]*
    ///清除所有XItem和XLink图元
    void clearXItemAndXLink();
signals:
//*[scene信号]*
    ///鼠标点击事件
    void mouseClicked(QGraphicsSceneMouseEvent* evnet);
    ///Scene右键菜单信号(view右键单击(非拖动)情况下)
    void sceneContextMenuRequested(const QPoint &pos);
//*[xItem信号]*
    ///xItem鼠标双击信号
    void mouseDoubleClickXItem(XFlowGraphicsItem* xItem);
    ///xItem添加信号
    void xItemAdd(XFlowGraphicsItem* xItem);
    ///xItem删除完成信号 返回值:False可以进行删除 True不可删除
    bool xItemRemoveStart(XFlowGraphicsItem* xItem);
    ///xItem删除完成信号
    void xItemRemoveFinish(XFlowGraphicsItem* xItem);
    ///xItem位置变化
    void xItemPosChanged(XFlowGraphicsItem* xItem);
    ///xItem形状变化
    void xItemShapeChanged(XFlowGraphicsItem* xItem);
    ///xItem单击选择事件
    void xItemSingleSelect(XFlowGraphicsItem* xItem);

//[xLink信号]
    ///判断两个XItem是否能进行连接  为true时不可连接
    bool judgeCantConnectXItem(XFlowGraphicsItem* xItemFather,const QString &fatherKey,
                               XFlowGraphicsItem* xItemSon,const QString &sonKey);
    ///判断连接后的XLink是否正确 为true时则存在错误 取消连接
    bool judgeCantConnectXLink(XFlowGraphicsConnectLink *xLink);
    ///XLink连线成功事件
    void xLinkConnectSuccess(XFlowGraphicsConnectLink *xLink);
    ///xLink鼠标双击信号
    void mouseDoubleClickXLink(XFlowGraphicsConnectLink* xLink);
    ///xLink添加信号
    void xLinkAdd(XFlowGraphicsConnectLink* xLink);
    ///xLink删除信号
    void xLinkRemove(XFlowGraphicsConnectLink* xLink);
    ///xLink单击选择事件
    void xLinkSingleSelect(XFlowGraphicsConnectLink* xLink);

protected slots:
//*[槽函数]*
    ///xItem位置变化(中转槽函数)
    void onXItemPosChanged();
    ///xItem形状变化(中转槽函数)
    void onXItemShapeChanged();
    ///连线错误 进行删除
    void onXLinkError();


/// QGraphicsScene interface
protected:
//*[场景事件]*
//*[拖动]*
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
//*[鼠标]*
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
//*[键盘]*
    void keyPressEvent(QKeyEvent *event) override;


public:
    //*[公开工具接口]*
    ///判断XItems中是否存在该指针
    bool existPtrInXItems(XFlowGraphicsItem* xItem);
    ///判断XLinks中是否存在该指针
    bool existPtrInXLinks(XFlowGraphicsConnectLink* xLink);

    ///通过坐标获取XItem图元
    XFlowGraphicsItem* getXItemByPos(const QPointF &pt);
    ///获取选择的XItem图元
    QList<XFlowGraphicsItem*> getSelectXItem();

    ///通过坐标获取XLink
    XFlowGraphicsConnectLink* getXLinkByPos(const QPointF &pt);

    ///获取选择的XLink图元
    QList<XFlowGraphicsConnectLink*> getSelectXLink();
protected:
    //*[内部工具接口]*
    /// 绘制磁吸线
    inline void drawMagneticLine(XFlowGraphicsItem *xItem,const QPointF &pt);



protected: //数据区域
//*[场景属性]*
    ///场景Id
    QString m_SceneId;
    ///场景Tag
    QVariant m_SceneTag;
    ///场景QObject指针Tag
    QObject *m_SceneQPtrTag;
//*[场景数据]*
    ///view视图类
    XFlowGraphicsView *m_pView=nullptr;
    ///ITEM委托工厂
    XFlowGraphicsItemDelegateFactory *m_pXItemFactory=nullptr;
    ///Link委托工厂
    XFlowGraphicsLinkDelegateFactory *m_pXLinkFactory=nullptr;
    ///场景图元XItem字典
    QMap<QString,XFlowGraphicsItem*> m_mapXItem;
    ///场景连线XLink字典
    QMap<QString,XFlowGraphicsConnectLink*> m_mapXLink;
//*[鼠标移动]*
    ///鼠标左键按下
    bool m_bMouseLeftPressed=false;
    ///鼠标右键按下
    bool m_bMouseRightPressed=false;
    ///临时拖拽图元
    XFlowGraphicsItem* m_pTempDragXItem=nullptr;
    ///当前鼠标移动到的临时图元
    XFlowGraphicsItem* m_pTempMoveXItem=nullptr;
//*[连线]*
    ///临时连线图元
    XFlowGraphicsConnectLink* m_xLinkTemp=nullptr;
    ///临时连接开始XItem
    XFlowGraphicsItem* m_xItemTempStartFather=nullptr;
    ///临时连接开始XItem连接Key
    QString  m_strTempStartConnKey="";
//*[磁吸线]*
    ///鼠标左键选择移动的磁吸线图元
    XFlowGraphicsItem* m_pTempMagneticMoveXItem=nullptr;
    /// 水平磁吸线	垂直磁吸线
    QGraphicsLineItem *m_itemMagneticHLine=nullptr;
    QGraphicsLineItem *m_itemMagneticVLine=nullptr;

protected:
    const QScopedPointer<XFlowGraphicsScenePrivate> d_ptr;
private:
     Q_DECLARE_PRIVATE(XFlowGraphicsScene)

};

#pragma endregion}

#endif // XFLOWGRAPHICSSCENE_H
