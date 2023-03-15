#ifndef XGRAPHICSSCENE_H
#define XGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "XGraphicsView.h"
#include "XGraphicsDelegateFactory.h"
#include "XGraphicsItem.h"
#include "XGraphicsConnectLink.h"
#include "XGraphicsGlobal.h"

/*
*   定义:
*   Item/item/QItem/qItem:QGraphicsItem
*   XItem/xItem:XGraphicsItem
*   XLink/xLink:XGraphicsConnectLink
*
*/

#pragma region Scene结构体{

///场景风格
struct SXGraphicsSceneConfig
{
    SXGraphicsSceneConfig()
    {
        penMagneticLine=QPen();
        penMagneticLine.setBrush(QColor(Qt::white));
        penMagneticLine.setStyle(Qt::DashLine);
        penMagneticLine.setWidth(1);

    }
    ///磁吸线画笔
    QPen penMagneticLine;

};

#pragma endregion}

#pragma region Scene类{

///XScene场景类
class XGRAPHICS_PUBLIC XGraphicsScene: public QGraphicsScene
{
    Q_OBJECT
public:
    XGraphicsScene(QObject *parent = nullptr);
    ~XGraphicsScene();
public:
//*[常规公共接口]*
    ///获取View视图
    XGraphicsView* getView();
    ///场景配置
    SXGraphicsSceneConfig* config()
    {
        return &m_config;
    }

    ///设置Item委托生产工厂
    void setXItemDelegateFactory(XGraphicsItemDelegateFactory* factory);
    ///设置Link委托生产工厂
    void setXLinkDelegateFactory(XGraphicsLinkDelegateFactory* factory);
    ///设置显示矩形
    void setDisplayRect(const QRectF &rect);
     ///设置显示矩形
    inline void setDisplayRect(qreal x, qreal y, qreal w, qreal h)
    { setDisplayRect(QRectF(x, y, w, h)); }

    ///缩放到Item范围
    void zoomToItemRect();

//*[XItem字典]*
    ///添加Item
    void addXItem(XGraphicsItem* xItem);
    ///删除Item(不做指针删除处理)
    void removeXItem(XGraphicsItem* xItem);
    ///通过Id获取XItem
    XGraphicsItem* getXItemById(const QString &id);
    ///通过Type获取XItems
    QList<XGraphicsItem*> getXItemsByType(const QString &type);
    ///场景XItems
    QMap<QString,XGraphicsItem*> getXItems() const
    {
        return m_mapXItem;
    }
//*[XLink字典]*
    ///添加Link
    void addXLink(XGraphicsConnectLink* xLink);
    ///删除Link(不做指针删除处理)
    void removeXLink(XGraphicsConnectLink* xLink);
    ///通过Id获取Link
    XGraphicsConnectLink *getXLinkById(const QString &id);

    QMap<QString,XGraphicsConnectLink*> getXLinks() const
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
    void mouseDoubleClickXItem(XGraphicsItem* xItem);
    ///xItem添加信号
    void xItemAdd(XGraphicsItem* xItem);
    ///xItem删除信号
    void xItemRemove(XGraphicsItem* xItem);
    ///xItem位置变化
    void xItemPosChanged(XGraphicsItem* xItem);
    ///xItem形状变化
    void xItemShapeChanged(XGraphicsItem* xItem);
    ///xItem单击选择事件
    void xItemSingleSelect(XGraphicsItem* xItem);

//[xLink信号]
    ///判断两个XItem是否能进行连接  为true时不可连接
    bool judgeCantConnectXItem(XGraphicsItem* xItemFather,const QString &fatherKey,
                               XGraphicsItem* xItemSon,const QString &sonKey);
    ///判断连接后的XLink是否正确 为true时则存在错误 取消连接
    bool judgeCantConnectXLink(XGraphicsConnectLink *xLink);
    ///XLink连线成功事件
    void xLinkConnectSuccess(XGraphicsConnectLink *xLink);
    ///xLink鼠标双击信号
    void mouseDoubleClickXLink(XGraphicsConnectLink* xLink);
    ///xLink添加信号
    void xLinkAdd(XGraphicsConnectLink* xLink);
    ///xLink删除信号
    void xLinkRemove(XGraphicsConnectLink* xLink);
    ///xLink单击选择事件
    void xLinkSingleSelect(XGraphicsConnectLink* xLink);

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
    bool existPtrInXItems(XGraphicsItem* xItem);
    ///判断XLinks中是否存在该指针
    bool existPtrInXLinks(XGraphicsConnectLink* xLink);

    ///通过坐标获取XItem图元
    XGraphicsItem* getXItemByPos(const QPointF &pt);
    ///获取选择的XItem图元
    QList<XGraphicsItem*> getSelectXItem();

    ///通过坐标获取XLink
    XGraphicsConnectLink* getXLinkByPos(const QPointF &pt);

    ///获取选择的XLink图元
    QList<XGraphicsConnectLink*> getSelectXLink();
protected:
    //*[内部工具接口]*
    /// 绘制磁吸线
    inline void drawMagneticLine(XGraphicsItem *xItem,const QPointF &pt);



protected: //数据区域
//*[场景数据]*
    ///view视图类
    XGraphicsView *m_pView=nullptr;
    ///ITEM委托工厂
    XGraphicsItemDelegateFactory *m_pXItemFactory=nullptr;
    ///Link委托工厂
    XGraphicsLinkDelegateFactory *m_pXLinkFactory=nullptr;
    ///场景配置
    SXGraphicsSceneConfig m_config;
    ///场景图元XItem字典
    QMap<QString,XGraphicsItem*> m_mapXItem;
    ///场景连线XLink字典
    QMap<QString,XGraphicsConnectLink*> m_mapXLink;
//*[鼠标移动]*
    ///鼠标左键按下
    bool m_bMouseLeftPressed=false;
    ///鼠标右键按下
    bool m_bMouseRightPressed=false;
    ///临时拖拽图元
    XGraphicsItem* m_pTempDragXItem=nullptr;
    ///当前鼠标移动到的临时图元
    XGraphicsItem* m_pTempMoveXItem=nullptr;
//*[连线]*
    ///临时连线图元
    XGraphicsConnectLink* m_xLinkTemp=nullptr;
    ///临时连接开始XItem
    XGraphicsItem* m_xItemTempStartFather=nullptr;
    ///临时连接开始XItem连接Key
    QString  m_strTempStartConnKey="";
//*[磁吸线]*
    ///鼠标左键选择移动的磁吸线图元
    XGraphicsItem* m_pTempMagneticMoveXItem=nullptr;
    /// 水平磁吸线	垂直磁吸线
    QGraphicsLineItem *m_itemMagneticHLine=nullptr;
    QGraphicsLineItem *m_itemMagneticVLine=nullptr;

};

#pragma endregion}

#endif // XGRAPHICSSCENE_H
