#ifndef XVIEWMGR_H
#define XVIEWMGR_H

#include <QObject>

///界面管理器(单例)
/// 连接界面和其他管理器

#define XvViewMgr XvViewManager::getInstance()

class XvSingleApplication;
class AppMainWindow;
class DockMainManager;
class UiXvWorkManager;
class UiXvDisplayManager;

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
    ///获取app
    XvSingleApplication *app() const;
    ///获取主界面
    AppMainWindow* appMainWindow() const;
    ///获取主Dock管理器
    DockMainManager* dockMainManager() const;
    ///获取流程Ui管理器
    UiXvWorkManager* uiXvWorkManager() const;
    ///获取显示Ui管理器
    UiXvDisplayManager* uiXvDisplayManager() const;
    ///初始化
    void init();

protected:
    ///设置App
    void setApp(XvSingleApplication* app);
    ///设置主界面
    void setAppMainWindow(AppMainWindow* mw);
    ///设置主界面Dock管理器
    void setDockMainManager(DockMainManager* dockMainMgr);
    ///设置流程Ui管理器
    void setUiXvWorkManager(UiXvWorkManager* uiXvWorkManager);
    ///设置显示Ui管理器
    void setUiXvDisplayManager(UiXvDisplayManager* uiXvDisplayManager);

signals:

private:
    XvSingleApplication* m_app=nullptr;
    AppMainWindow*  m_appMainWindow=nullptr;
    DockMainManager* m_dockMainManager=nullptr;
    UiXvWorkManager* m_uiXvWorkManager=nullptr;
    UiXvDisplayManager* m_uiXvDisplayManager=nullptr;
};

#endif // XVIEWMGR_H
