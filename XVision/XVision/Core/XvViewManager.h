#ifndef XVIEWMGR_H
#define XVIEWMGR_H

#include <QObject>

///界面管理器(单例)
/// 连接界面和其他管理器

#define XvViewMgr XvViewManager::getInstance()

class AppMainWindow;
class DockMainManager;
class UiXvFlowManager;

class XvViewManager : public QObject
{
    Q_OBJECT
    friend class XvSingleApplication;
public:
    ///获取单例
    static XvViewManager *getInstance();
private:
    explicit XvViewManager(QObject *parent = nullptr);
    ~XvViewManager();
    static XvViewManager* s_Instance;


public:
    ///获取主界面
    AppMainWindow* getMainWindow() const;
    ///获取主Dock管理器
    DockMainManager* getDockMainManager() const;
    ///获取流程Ui管理器
    UiXvFlowManager* getUiXvFlowManager() const;
    ///初始化
    void init();

protected:
    ///设置主界面
    void setAppMainWindow(AppMainWindow* mw);
    ///设置主界面Dock管理器
    void setDockMainManager(DockMainManager* dockMainMgr);
    ///设置流程Ui管理器
    void setUiXvFlowManager(UiXvFlowManager* uiXvFlowManager);

signals:

private:
    AppMainWindow*  m_appMainWindow=nullptr;
    DockMainManager* m_dockMainManager=nullptr;
    UiXvFlowManager* m_uiXvFlowManager=nullptr;
};

#endif // XVIEWMGR_H
