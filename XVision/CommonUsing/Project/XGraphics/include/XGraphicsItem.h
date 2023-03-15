#ifndef XGRAPHICSITEM_H
#define XGRAPHICSITEM_H

#include <QtCore>
#include <QGraphicsitem>
#include <QPainter>
#include "XGraphicsGlobal.h"

#pragma region XItem 结构体{

///XItem通用配置
struct SXCommonItemConfig
{
    SXCommonItemConfig()
    {
        penConnectArea=QPen(QColor(30,30,30));
        brushConnectArea=QBrush(QColor(100,130,250));

        penText = QPen();
        penText.setColor(QColor(75, 75, 75));
        penText.setWidth(1);
        fontText = QFont("YouYuan", 12, 2);
        fontText.setBold(true);

        penHighlight.setColor(QColor(255,242,0));
        penHighlight.setWidth(5);
        brushHighlight=QBrush(QColor(Qt::white));
    }

    ///连接区域边框画笔
    QPen penConnectArea;
    ///连接区域内部笔刷
    QBrush brushConnectArea;

    ///Item文本画笔
    QPen penText;
    ///Item文本字体
    QFont fontText;

    ///高亮时画笔
    QPen penHighlight;
    ///高亮时笔刷
    QBrush brushHighlight;

};
///XItem图像显示数据
struct SXItemPixData
{
    SXItemPixData()
    {
        strKey="";
        bShowRect=false;
        brushShowRect=QBrush(Qt::NoBrush);
    }
    SXItemPixData(const QString &_strKey,const QPixmap &_pixmap,
                  bool _bShowRect=false,
                  QPen _penShowRect=QPen(),
                  QBrush _brushShowRect=QBrush(Qt::NoBrush))
        :strKey(_strKey),pixmap(_pixmap),
          bShowRect(_bShowRect),penShowRect(_penShowRect),brushShowRect(_brushShowRect)
    {

    }
    ~SXItemPixData()
    {

    }
    ///图像Key
    QString strKey;
    ///显示的图像
    QPixmap pixmap;

    ///显示图像框
    bool bShowRect;
    ///矩形框画笔
    QPen penShowRect;
    ///笔刷
    QBrush brushShowRect;

};

#pragma endregion}

#pragma region XItem类{

class XGraphicsScene;//场景类
class XGraphicsConnectLink;//XLink连线类

///XItem基类
class XGRAPHICS_PUBLIC XGraphicsItem:public QObject
{
    Q_OBJECT
    friend class XGraphicsScene;//友元XGraphicsScene
    friend class XGraphicsConnectLink; //友元XGraphicsConnectLink
public:
    XGraphicsItem(QString type="",QString id="",QObject *parent = nullptr);
    ~XGraphicsItem();
public:
//*[常规公共接口]*
    ///转换为GItem图元
    virtual QGraphicsItem* item()=0;
protected:
    ///初始化Item
    virtual void initItem()=0;
/***************************xItem事件/信号区***************************/
signals:
//*[XItem信号]*
    ///位置变化
    void posChanged();
    ///形状变化
    void shapeChanged();

protected:
//*[scene友元事件]*
    ///Scene鼠标进入事件
    virtual void sceneMouseEnterEvent(QGraphicsSceneMouseEvent* event);
    ///Scene鼠标离开事件
    virtual void sceneMouseLeaveEvent(QGraphicsSceneMouseEvent* event);
    ///Scene鼠标移动事件
    virtual void sceneMouseMoveEvent(QGraphicsSceneMouseEvent* event);

    ///Scene鼠标按下事件
    virtual void sceneMousePressEvent(QGraphicsSceneMouseEvent* event) {}
    ///Scene鼠标释放事件
    virtual void sceneMouseReleaseEvent(QGraphicsSceneMouseEvent* event){}
    ///Scene鼠标双击事件
    virtual void sceneMouseDoubleClickEvent(QGraphicsSceneMouseEvent* event){}




/***************************xItem形状外观信息***************************/
public:
//*[形状尺寸外观]*
    ///设置Item尺寸
    /// bUpdate:是否立即更新形状
    virtual void setSize(double width,double height,bool bUpdate=true);

    ///设置宽度,
    /// bUpdate:是否立即更新形状
    virtual void setWidth(double width,bool bUpdate=true);

    ///设置高度
    /// bUpdate:是否立即更新形状
    virtual void setHeight(double height,bool bUpdate=true);

    ///外接矩形宽度
    virtual double width() const
    {
        return m_rWidth;
    }
    ///外接矩形高度
    virtual double height() const
    {
        return m_rHeight;
    }

    ///更新形状
    virtual void updateShape()
    {
       return;
    }

    ///设置Item高亮显示
    virtual void setHighlight(bool highlight,bool bUpdate=true);
    ///Item高亮显示
    virtual bool highlight() const
    {
        return m_bHighlight;
    }
protected:
    ///Item长宽
    double    m_rWidth,m_rHeight;
    ///Item高亮显示
    bool m_bHighlight=false;

/***************************xItem连线模块***************************/
public:
//*[连接区域]*

    ///判断坐标点是否在连接区域内(需要子类实现)
    /// sPt:scene坐标
    virtual bool isInConnectArea(const QPointF &sPt)=0;
    ///是否存在连接Key (需要子类实现)
    virtual bool hasConnectKey(const QString &key)=0;
    ///根据连接键获取连接点数据(数据为scene坐标) (需要子类实现)
    /// 失败返回false
    virtual bool getConnectData(const QString &key,SConnectData &connData)=0;
    ///根据scene坐标点获取连接点数据(数据为scene坐标) (需要子类实现)
    /// sPt:scene坐标
    /// 失败返回false
    virtual bool getConnectData(const QPointF &sPt,SConnectData &connData)=0;



//*[连接对象]*
    ///通过Id获取父(连入)XLink
    virtual XGraphicsConnectLink* getFatherConnectLink(const QString &id) const;
    ///获取父(连入)XLink
    virtual QList<XGraphicsConnectLink*> getFatherConnectLinks() const;

    ///通过Id获取子(连出)XLink
    virtual XGraphicsConnectLink* getSonConnectLink(const QString &id) const;
     ///获取子(连入)XLink
    virtual QList<XGraphicsConnectLink*> getSonConnectLinks() const;

    ///XGraphicsConnectLink* FatherLink判断位置调用 (需要子类实现)
    virtual bool getFatherConnectData(XGraphicsConnectLink* fatherLink,SConnectData &connData);

    ///XGraphicsConnectLink* SonLink判断位置调用 (需要子类实现)
    virtual bool getSonConnectData(XGraphicsConnectLink* sonLink,SConnectData &connData);


//*[连接线调用接口]*
    ///添加连入XLink
    virtual bool addFatherConnect(XGraphicsConnectLink* xLink);
    ///添加连出XLink
    virtual bool addSonConnect(XGraphicsConnectLink* xLink);

    ///移除父(连入)XLink
    virtual bool removeFatherConnect(XGraphicsConnectLink* xLink);
    ///移除子(连出)XLink
    virtual bool removeSonConnect(XGraphicsConnectLink* xLink);

    ///存在父连接Xlink被选择
    virtual bool hasFatherConnectSelected();
    ///存在子连接Xlink被选择
    virtual bool hasSonConnectSelected();

protected:
    ///连接区域显示模式
    enum EShowConnectAreaType
    {
        ///不显示
        NoShow,
        ///连接矩形缩小显示
        ShowLittle,
        ///连接矩形完全显示
        ShowFull,
    };

//*[内部调用接口]*
    ///初始化连接区域 (需要子类实现)
    virtual void initConnectArea() {};
    ///SConnectData转换成scene坐标
    virtual SConnectData sconnectDataMapToScene(const SConnectData &data);
    ///设置连接矩形显示
    virtual void setShowConnectArea(EShowConnectAreaType eType,bool bUpdate=true);

protected:

//*[连接区域显示状态]*
    ///连接点矩形显示模式
    EShowConnectAreaType  m_eShowConnectAreaType=EShowConnectAreaType::NoShow;
    ///当前移动到的连接点Key，进行放大显示
    QString m_strShowFullKey="";


    ///该Item的父(连接进来的)的XLink字典
    QMap<QString,XGraphicsConnectLink*> m_mapThisFatherConnect;
    ///该Item的子(连接出去的)的XLink字典
    QMap<QString,XGraphicsConnectLink*> m_mapThisSonConnect;



/***************************xItem数据区***************************/
public:
//[item属性]
    ///Item类型
    QString itemType() const
    {
        return m_ItemType;
    }
    ///ItemID
    QString itemId() const
    {
        return m_ItemId;
    }
    void setItemId(const QString& id)
    {
        m_ItemId=id;
    }
    ///设置父场景
    void setParScene(XGraphicsScene* parScene);
    ///获取父场景
    XGraphicsScene* parScene() const
    {
        return m_parScene;
    }
//[item附带数据]
    ///设置数据
    virtual void addTagData(QString key,const QVariant &data);
    ///获取数据
    virtual QVariant tagData(const QString &key) const
    {
        if(m_mapTagData.contains(key))
        {
            return m_mapTagData[key];
        }
        return QVariant();
    }
    virtual void clearTagData()
    {
        m_mapTagData.clear();
    }


//[item文本]
    ///Item文本
    virtual QString text() const
    {
        return m_ItemText;
    }
    ///设置文本
    virtual void setText(const QString &text)
    {
        m_ItemText=text;
    }
    ///返回文本显示矩形(item坐标)
    virtual QRectF textRect() const
    {
        return m_ItemRectText;
    }
    ///Item提示文本
    virtual QString tip() const
    {
        return m_ItemTip;
    }
    ///设置提示文本
    virtual void setTip(const QString &tip)
    {
        m_ItemTip=tip;
    }
//[item图像]
    ///添加图像数据
    virtual void addPixData(SXItemPixData *data);

    ///通过key获取Item图像
    virtual SXItemPixData* pixdata(const QString &key) const
    {
        if(m_mapPixData.contains(key))
        {
            return m_mapPixData[key];
        }
        return nullptr;
    }
    ///获取Item图像字典
    virtual  QMap<QString,SXItemPixData*> pixdata() const
    {
        return m_mapPixData;
    }
    ///清除图像
    virtual void clearPixmap()
    {
        m_mapPixData.clear();
    }
    ///获取当前图像显示Key
    virtual QString showPixKey() const
    {
        return m_strShowPixKey;
    }
    ///切换图像显示
    virtual bool switchShowPixKey(const QString &key,bool bUpdate=true);
//[item配置]
    ///item配置
    SXCommonItemConfig* itemConfig()
    {
        return &m_ItemConfig;
    }
protected:
    ///节点父Scene
    XGraphicsScene* m_parScene;
    ///通用配置
    SXCommonItemConfig m_ItemConfig;

    ///Item类型
    QString m_ItemType;
    ///ItemID
    QString m_ItemId;
    ///Item文本
    QString m_ItemText;
    ///Item文本显示框
    QRectF m_ItemRectText;
    ///Item提示
    QString m_ItemTip;

    ///当前显示的图像(为空不显示)
    QString m_strShowPixKey;
    ///Item图像字典
    QMap<QString,SXItemPixData*> m_mapPixData;

    ///Item跟随数据
    QMap<QString,QVariant> m_mapTagData;

};

#pragma endregion}

#endif // XGRAPHICSITEM_H
