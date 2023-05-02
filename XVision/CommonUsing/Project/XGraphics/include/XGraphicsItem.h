#ifndef XGRAPHICSITEM_H
#define XGRAPHICSITEM_H

#include <QtCore>
#include <QGraphicsitem>
#include <QPainter>
#include "XGraphicsGlobal.h"


///XItem图像显示数据
struct SXItemPixData
{
public:
    SXItemPixData()
    {
        strKey="";
    }
    SXItemPixData(const QString &_strKey,const QPixmap &_pixmap, QMap<QString,QPen> _mapPenShowRect= QMap<QString,QPen>())
        :strKey(_strKey),pixmap(_pixmap),
          mapPenShowRect(_mapPenShowRect)
    {

    }
    ~SXItemPixData()
    {

    }
    void switchPenKey(const QString &key)
    {
        if(mapPenShowRect.contains(key)||key.isEmpty())
        {
            curPenKey=key;
        }
    }
    QString penKey() const
    {
        return curPenKey;
    }
    QPen getPen() const
    {
        if(mapPenShowRect.contains(curPenKey))
        {
            return mapPenShowRect[curPenKey];
        }
        else
        {
            return QPen();
        }
    }
public:
    ///图像Key
    QString strKey;
    ///显示的图像
    QPixmap pixmap;
    ///矩形框画笔字典<QString:Key QPen:画笔>
    QMap<QString,QPen> mapPenShowRect;

protected:
    QString curPenKey="";
};


#pragma region XItem类{

class XGraphicsScene;//场景类
class XGraphicsConnectLink;//XLink连线类

class XGraphicsItemPrivate;
///XItem基类
class XGRAPHICS_PUBLIC XGraphicsItem:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPen connectAreaPen READ connectAreaPen WRITE setConnectAreaPen)
    Q_PROPERTY(QBrush connectAreaBrush READ connectAreaBrush WRITE setConnectAreaBrush)
    Q_PROPERTY(QPen textPen READ textPen WRITE setTextPen)
    Q_PROPERTY(QFont textFont READ textFont WRITE setTextFont)
    Q_PROPERTY(QPen highLightPen READ highLightPen WRITE setHighLightPen)
    Q_PROPERTY(QBrush highLightBrush READ highLightBrush WRITE setHighLightBrush)

    friend class XGraphicsScene;//友元XGraphicsScene
    friend class XGraphicsConnectLink; //友元XGraphicsConnectLink
public:
    XGraphicsItem(QString type="",QString id="",QObject *parent = nullptr);
    virtual ~XGraphicsItem();
public:
//*[常规公共接口]*
    ///转换为GItem图元
    virtual QGraphicsItem* item()=0;
public:
 //*[属性接口]*
    ///连接区域边框画笔
    QPen connectAreaPen() const;
    ///设置连接区域边框画笔
    void setConnectAreaPen(const QPen &pen);

    ///连接区域内部笔刷
    QBrush connectAreaBrush() const;
    ///设置连接区域内部笔刷
    void setConnectAreaBrush(const QBrush &brush);

    ///Item文本画笔
    QPen textPen() const;
    ///设置Item文本画笔
    void setTextPen(const QPen &pen);

    ///Item文本字体
    QFont textFont() const;
    ///设置Item文本字体
    void setTextFont(const QFont &font);

    ///高亮时画笔
    QPen highLightPen() const;
    ///设置高亮时画笔
    void setHighLightPen(const QPen &pen);

    ///高亮时笔刷
    QBrush highLightBrush() const;
    ///设置高亮时笔刷
    void setHighLightBrush(const QBrush &brush);
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
    virtual void setHighLight(bool highLight,bool bUpdate=true);
    ///Item高亮显示
    virtual bool highLight() const
    {
        return m_bHighLight;
    }
protected:
    ///Item长宽
    double    m_rWidth,m_rHeight;
    ///Item高亮显示
    bool m_bHighLight=false;

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
    ///获取附带数据
    virtual QVariant itemTag() const
    {
        return m_ItemTag;
    }
    ///设置附带数据
    virtual void setItemTag(const QVariant& tag);


    ///获取QObject指针Tag
    QObject* itemQPtrTag() const
    {
        return m_ItemQPtrTag;
    }
    ///设置QObject指针Tag
    void setItemQPtrTag(QObject* qptrTag);



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
    virtual bool switchShowPixKey(const QString &pixKey,const QString &penKey,bool bUpdate=true);

protected:
    ///节点父Scene
    XGraphicsScene* m_parScene;
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
    QVariant m_ItemTag;
    ///Item跟随QObject指针
    QObject* m_ItemQPtrTag;
protected:
    const QScopedPointer<XGraphicsItemPrivate> d_ptr;
private:
     Q_DECLARE_PRIVATE(XGraphicsItem)
};

#pragma endregion}

#endif // XGRAPHICSITEM_H
