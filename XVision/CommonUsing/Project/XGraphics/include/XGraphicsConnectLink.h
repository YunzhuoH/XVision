#ifndef XGRAPHICSCONNECTLINK_H
#define XGRAPHICSCONNECTLINK_H

#include <QtCore>
#include <QGraphicsitem>
#include <QPainter>
#include "XGraphicsGlobal.h"

#pragma region ConnectLink结构体{
///XLink配置
struct SXLinkConfig
{
    SXLinkConfig()
    {
        penLinkingCircle=QPen(QColor(Qt::white));
        brushLinkingCircle=QBrush(QColor(50, 125, 255));
        rLinkingCircleRadius=4;


        penLinking=QColor(25, 150, 255);
        penLinking.setWidth(3);
        penLinking.setStyle(Qt::SolidLine);

        penLinked=QColor(25, 150, 255);
        penLinked.setWidth(3);
        penLinked.setStyle(Qt::SolidLine);

        penLinkSelected=QColor(255, 150, 50);
        penLinkSelected.setWidth(5);
        penLinkSelected.setStyle(Qt::SolidLine);


        penSelectBoundingRect.setColor(QColor(255, 255, 255));
        penSelectBoundingRect.setWidth(1);
        penSelectBoundingRect.setStyle(Qt::DashLine);

        rArrowSize=15;

        penHighLight.setColor(QColor(255,242,0));
        penHighLight.setWidth(3);
        penHighLight.setStyle(Qt::SolidLine);

        penText = QPen();
        penText.setColor(QColor(255, 255, 255));
        penText.setWidth(1);
        fontText = QFont("YouYuan", 12, 2);
        fontText.setBold(false);
    }
    ///连接拖动圆形画笔
    QPen penLinkingCircle;
    ///连接拖动圆形笔刷
    QBrush brushLinkingCircle;
    ///连接拖动圆半径
    double rLinkingCircleRadius=4;


    ///正在连线画笔
    QPen penLinking;

    ///连线完毕画笔
    QPen penLinked;

    ///连线被选择时
    QPen penLinkSelected;

    ///选中时边框画笔
    QPen penSelectBoundingRect;

    ///末端箭头大小
    double rArrowSize=15;

    ///连线高亮时的画笔
    QPen penHighLight;

    ///Link文本画笔
    QPen penText;
    ///Link文本字体
    QFont fontText;
};
#pragma endregion}


#pragma region ConnectLink类{

class XGraphicsScene;
class XGraphicsItem;
///连线边框大小
#define LINK_BOUNDING_SIZE 20
class XGRAPHICS_PUBLIC XGraphicsConnectLink:public QObject,public QGraphicsLineItem
{
    Q_OBJECT
    friend XGraphicsScene;
    friend XGraphicsItem;
public:
    XGraphicsConnectLink(QObject *parent = nullptr);
    XGraphicsConnectLink(QPointF ptStart,QPointF ptEnd,QObject *parent = nullptr);
    XGraphicsConnectLink(XGraphicsItem *xItemFather,const QString &fatherKey,
                         XGraphicsItem *xItemSon,const QString &sonKey,
                         QObject *parent = nullptr);
    ~XGraphicsConnectLink();
protected:
    void initConnectLink();

signals:
//*[信号]*
    ///连接错误
    void xLinkError();
public slots:
    ///父(开始)XItem/子(结束)Item更新；
    void onXItemUpdate();
protected slots:
//*[槽函数]*

    ///父(开始)XItem销毁
    void onFatherXItemDestroyed();
    ///子(结束)XItem销毁
    void onSonXItemDestroyed();

    ///父(开始)Item位置/形状更新
    void onFatherXItemUpdate();
    ///子(结束)Item位置/形状改更新
    void onSonXItemUpdate();

    ///更新线段
    void updateXLink();

    // QGraphicsItem interface
public:    
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    //*[内部调用接口]*
    ///更新箭头
    void updateArrow();
    ///绘制文本
    void drawLinkText(QPainter *painter,const QString &text);
/***************************XLink形状外观***************************/
public:
    ///连接线长度
    virtual double linkLength();
/***************************XLink数据***************************/
public:
//*[父场景]*
    ///设置父场景
    void setParScene(XGraphicsScene* parScene);
    ///获取父场景
    XGraphicsScene* parScene() const
    {
        return m_parScene;
    }
//*[XLink数据]*
    ///设置父(开始)连接点 (并关联销毁/位置改变/形状改变信号)
    virtual bool setFatherXItemKey(XGraphicsItem* xItem,const QString &key);
    ///设置子(结束)连接点 (并关联销毁/位置改变/形状改变信号)
    virtual bool setSonXItemKey(XGraphicsItem* xItem,const QString &key);

    ///连线Id
    virtual QString linkId() const
    {
        return m_LinkId;
    }
    ///连线文本
    virtual QString text() const
    {
        return m_LinkText;
    }
    ///设置文本
    virtual void setText(const QString &text)
    {
        m_LinkText=text;
    }
    ///返回文本显示矩形(link坐标)
    virtual QRectF textRect() const
    {
        return m_LinkRectText;
    }
    ///父(开始)位置
    virtual QPointF fatherStartPos() const
    {
        return m_ptFatherStart;
    }
    ///子(结束)位置
    virtual QPointF sonEndPos() const
    {
        return m_ptSonEnd;
    }
    ///设置父(开始)位置(item存在不可设置)
    virtual bool setFatherStartPos(const QPointF &pt);
    ///设置子(结束)位置(item存在不可设置)
    virtual bool setSonEndPos(const QPointF &pt);

    ///父(开始)Item
    virtual XGraphicsItem* fatherXItem() const
    {
        return m_fatherXItem;
    }
    ///子(结束)Item
    virtual XGraphicsItem* sonXItem() const
    {
        return m_sonXItem;
    }

    ///父(开始)key
    virtual QString fatherKey() const
    {
        return m_fatherConnKey;
    }
    ///子(结束)Key
    virtual QString sonKey() const
    {
        return m_sonConnKey;
    }


    ///设置父(开始)key
    virtual bool setFatherKey(const QString &key);

    ///设置子(结束)Key
    virtual bool setSonKey(const QString &key);

    ///设置连线状态:正在连线(未完成false)/连线完毕(true)
    virtual void setLinkState(bool isLinked);

    ///连线状态
    virtual bool linkState() const
    {
        return m_bLinked;
    }

    ///设置Link高亮显示
    virtual void setHighlight(bool highlight,bool bUpdate=true);
    ///Link高亮显示
    virtual bool highlight() const
    {
        return m_bHighlight;
    }

    ///item配置
    SXLinkConfig* linkConfig()
    {
        return &m_LinkConfig;
    }
protected:
//*[XLink数据]*
    ///节点父Scene
    XGraphicsScene* m_parScene;

    ///连接配置
    SXLinkConfig m_LinkConfig;

    ///连线Id
    QString m_LinkId;

    ///连线文本
    QString m_LinkText;
    ///连线文本显示框
    QRectF m_LinkRectText;

    ///父(开始)位置
    QPointF m_ptFatherStart;
    ///子(结束)位置
    QPointF m_ptSonEnd;

    ///连接线父(开始)Item
    XGraphicsItem* m_fatherXItem=nullptr;
    ///父(开始)连接点Key
    QString m_fatherConnKey;


    ///连接线子(结束)Item
    XGraphicsItem* m_sonXItem=nullptr;
    ///子(结束)连接点Key
    QString m_sonConnKey;

    ///连线是否完毕
    bool m_bLinked=false;

//*[XLink形状]*
    ///末端箭头
    QPolygonF m_polyArrowHead;
    ///高亮显示
    bool m_bHighlight=false;

};

#pragma endregion}

#endif // XGRAPHICSCONNECTLINK_H
