#ifndef UIXVFLOWMANAGER_H
#define UIXVFLOWMANAGER_H


#include "DockDef.h"
#include <QStatusBar>

class XGraphicsScene;
class UiXvFlowManager:public QObject
{
    Q_OBJECT
public:
    UiXvFlowManager(QObject* parent=nullptr);
    ~UiXvFlowManager();

    ///获取流程Dock管理器
    CDockManager* dockFlowManager() const {return m_dockFlowManager;}
    ///获取流程状态栏
    QStatusBar* dockStatusBar() const {return m_flowStatusBar;}
    ///通过id创建流程图场景
    XGraphicsScene* addFlowScene(const QString &id,const QString &name);

    ///通过id获取流程图场景
    XGraphicsScene* getFlowScene(const QString &id);

protected:
    ///初始化
    void init();

private:
    CDockManager* m_dockFlowManager = nullptr;//dock管理器
    CDockAreaWidget* m_dockFlowArea=nullptr;//流程区域
    QStatusBar* m_flowStatusBar=nullptr;//流程状态栏显示流程信息
    QMap<QString,XGraphicsScene*> m_mapFlowScene;
};

#endif // UIXVFLOWMANAGER_H
