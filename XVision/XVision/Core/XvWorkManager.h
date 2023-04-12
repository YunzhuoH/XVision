#ifndef XVWORKMANAGER_H
#define XVWORKMANAGER_H

#include <QObject>
#include "XvCoreManager.h"
#define XvWorkMgr XvWorkManager::getInstance()

namespace XvCore
{
class XvFunc;
class XvFlow;
class XvProject;
}

class XGraphicsScene;
class XGraphicsItem;
class XvWorkManagerPrivate;
///工作管理器 管理视觉方案/流程/算子
class XvWorkManager:public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(XvWorkManager)
public:
    ///获取单例
    static XvWorkManager *getInstance();
protected:
    const QScopedPointer<XvWorkManagerPrivate> d_ptr;
private:
    explicit XvWorkManager(QObject *parent = nullptr);
    ~XvWorkManager();
    static XvWorkManager* s_Instance;




public: //初始化接口
    ///初始化
    void init();
    ///反初始化
    void uninit();
    ///初始化工作
    /// 加载默认项目，并新建流程
    void onInitWork();
protected://内部工具接口


///常规接口
public://公共接口
//[核心管理器]
    ///获取算子核心管理器
    XvCore::XvCoreManager* getXvCoreMgr() const;
 //[项目]
    ///获取项目
    XvCore::XvProject* getXvProjevt() const;
    ///创建项目
    XvCore::XvProject* createNewProject(const QString &name);
 //[流程]
    ///通过ID获取流程
    XvCore::XvFlow*  getXvFlow(const QString &id) const;

    ///流程创建
    XvCore::XvFlow* createXvFlow(const QString &name="Flow");
    ///流程删除
    bool removeXvFlow(const QString &id);

    ///流程单次运行
    bool onceRunXvFlow(const QString &id);
    ///流程重复运行
    bool loopRunXvFlow(const QString &id);
    ///流程停止运行
    bool stopRunXvFlow(const QString &id);

/***********************{槽接口:项目Project-流程Flow-算子Func---<关联>---图元XItem-场景Scene-工作界面管理器UiXvWorkManager]***********************/

protected slots:
 //[项目]
    ///项目更新响应槽
    void onUpdateXvProject(XvCore::XvProject* project);
    ///项目销毁响应槽
    void onXvProjectDestroyed(QObject* obj);
//[流程]:流程创建和删除由UiXvWorkMgr调用
    ///流程创建完成响应槽
    void onXvFlowCreated(XvCore::XvFlow* flow);
    ///流程开始删除响应槽
    void onRemoveXvFlowStart(XvCore::XvFlow* flow);
    ///流程完成删除响应槽
    void onRemoveXvFlowEnd(const QString &flowId);

//[算子]:算子创建和删除有两种方式:1.由Scene信号主动发起(UiXvWorkMgr已连接) 2.外部调用XvFlow添加删除
    ///算子添加响应槽
    void onXvFuncCreated(XvCore::XvFunc* func);
    ///算子开始删除响应槽
    void onRemoveXvFuncStart(XvCore::XvFunc* func);
    ///算子完成删除响应槽
    void onRemoveXvFuncEnd(const QString &funcId);

};

#endif // XVWORKMANAGER_H
