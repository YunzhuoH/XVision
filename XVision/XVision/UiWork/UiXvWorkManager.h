﻿#ifndef UIXVWORKMANAGER_H
#define UIXVWORKMANAGER_H


#include "DockDef.h"
#include <QStatusBar>

///UiWork管理器:视觉流程界面管理器
/// 关联XvWorkManager
///连接底层XvCore视觉工作流
/// 借鉴MVC/MVVM框架,该类实现对底层视觉类的(单向)绑定

namespace XvCore
{
class XvFunc;
class XvFlow;
class XvProject;
}
class QGraphicsSceneMouseEvent;
class XGraphicsScene;
class XGraphicsItem;
class XGraphicsConnectLink;
class UiXvWorkManagerPrivate;
class UiXvWorkManager:public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(UiXvWorkManager)
public:
    UiXvWorkManager(QObject* parent=nullptr);
    ~UiXvWorkManager();
protected:
    const QScopedPointer<UiXvWorkManagerPrivate> d_ptr;
public://公共常规接口
    ///获取流程Dock管理器
    CDockManager* dockFlowManager() const {return m_dockFlowManager;}
    ///获取流程状态栏
    QStatusBar* dockStatusBar() const {return m_flowStatusBar;}

protected: //初始化接口
    ///初始化
    void init();
    ///初始化Dock
    void initDock();
    ///初始化工具按钮
    void initToolBtn();

protected://内部工具接口
    ///获取当前Dock的流程ID
    bool getCurDockFlowId(QString &id);
    ///获取当前Dock的流程
    XvCore::XvFlow* getCurDockFlow();
    ///初始化流程场景:【界面】相关连接(绑定)
    void initFlowScene(XvCore::XvFlow *flow,XGraphicsScene* scene);
    ///反初始化流程场景:【界面】相关断连(解绑)
    void uninitFlowScene(XvCore::XvFlow *flow,XGraphicsScene* scene);
    ///初始化算子图元:【界面】相关连接(绑定)
    void initFuncXItem(XvCore::XvFunc *func,XGraphicsItem* xItem);
    ///反初始化算子图元:【界面】相关连接(解绑)
    void uninitFuncXItem(XvCore::XvFunc *func,XGraphicsItem* xItem);
public slots://公共调用槽
    ///通过id获取流程图场景
    XGraphicsScene* getFlowScene(const QString &flowId);
    ///通过流程新建则创建流程图场景(如果流程号存在则返回该流程对应的Scene)
    XGraphicsScene* createFlowScene(XvCore::XvFlow *flow);
    ///通过流程id名称移除流程图场景
    bool removeFlowScene(XvCore::XvFlow *flow);
    ///通过算子类型添加图元
    /// role:算子标识符
    /// flowId：流程号
    bool addXItemByFuncRole(const QString &role,const QString &flowId,const QPointF &pos=QPoint(0,0));

    ///通过算子ID和流程ID删除图元
    /// funcId:算子ID
    /// flowId：流程ID
    bool removeXItemByFuncId(const QString &funcId,const QString &flowId);

protected slots://Ui界面内部调用槽

 /*-----DockTitleBar-按钮右键菜单-响应槽函数(流程相关)-----*/
 //*[流程界面操作]*
    ///Flow-DockTab请求菜单
    void onFlowDockTabMenuRequested(const QPoint &pos);
//*[流程常规操作]*
    ///流程显示属性
    void flowShowProp();
    ///流程重命名
    void flowRename();
    ///流程名称修改响应槽函数:对应修改流程标题框显示
    void onFlowNameChanged(XvCore::XvFlow *flow);
    ///流程添加
    void flowAdd();
    ///流程删除
    void flowRemove();
//*[流程运行操作]*
    ///流程单次运行
    void flowOnceRun();
    ///流程重复运行
    void flowLoopRun();
    ///流程停止运行
    void flowStopRun();
    ///流程开始运行响应槽函数
    void onFlowRunStart();
    ///流程运行结束响应槽函数
    void onFlowRunEnd();
    ///流程运行停止响应槽
    void onFlowRunStop();
 /*-----Scene信号+右键菜单-响应槽函数(算子相关)-----*/
 //*[Scene常规操作]*
    ///Scene-场景请求菜单
    void onFlowSceneMenuRequested(const QPoint &pos);
    ///Flow-场景 鼠标点击事件
    void onFlowSceneMouseClicked(QGraphicsSceneMouseEvent* event);
    ///Flow-场景 XItem单独选择事件
    void onFlowSceneXItemSingleSelect(XGraphicsItem* item);
    ///Flow-场景 XItem双击事件
    void onFlowSceneMouseDoubleClickXItem(XGraphicsItem* item);
    ///Flow-场景 XLink单独选择事件
    void onFlowSceneXLinkSingleSelect(XGraphicsConnectLink* link);

//*[Scene算子操作]*
    ///Flow-场景流程XItem添加(界面主动添加)
    void onFlowSceneXItemAdd(XGraphicsItem* xItem);
    ///Flow-场景流程XItem开始删除[判断是否可以删除XvFunc](界面主动删除)
    bool onFlowSceneXItemRemoveStart(XGraphicsItem* xItem);
//*[算子操作]*
    ///算子显示
    void funcShow(XGraphicsItem* item);
    ///算子重命名
    void funcRename();

 //*[算子XItem]*
private:
    CDockManager* m_dockFlowManager = nullptr;//dock管理器
    CDockAreaWidget* m_dockFlowArea=nullptr;//流程区域
    QStatusBar* m_flowStatusBar=nullptr;//流程状态栏显示流程信息
    ///流程号:流程图
    QMap<QString,XGraphicsScene*> m_mapFlowScene;

};

#endif // UIXVWORKMANAGER_H