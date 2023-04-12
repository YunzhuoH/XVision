#ifndef DOCKMAINMANAGER_H
#define DOCKMAINMANAGER_H

#include <QObject>
#include <QMap>
#include "DockDef.h"


class DockMainManager:public QObject
{
    Q_OBJECT
public:
    enum EDockArea
    {
        Core=0,//核心主区域
        Work=1,//工作区域
        Output=2,//输出区域
    };
    DockMainManager(QObject* parent=nullptr);
    ~DockMainManager();
    ///获取dock管理器
    CDockManager* dockMainManager() const {return m_DockMainManager;}

    ///添加DockWidget窗口
    CDockWidget* addDockWidget(const EDockArea &area,QWidget* widget);

    ///设置区域当前索引
    void setAreaCurrentIndex(const EDockArea &area,int idx);
    ///设置区域当前dock
    void setAreaCurrentDockWidget(const EDockArea &area,CDockWidget *dock);

    ///更新布局
    void restoreState();
protected:
    void init();
private:
    CDockManager* m_DockMainManager = nullptr;//dock管理器
    QMap<EDockArea, ads::CDockAreaWidget*> m_mapDockAreaWidget;

};

#endif // DOCKMAINMANAGER_H
