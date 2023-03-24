#ifndef DOCKDEF_H
#define DOCKDEF_H

#include "DockManager.h"
#include "DockWidget.h"
#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "DockWidgetTab.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "DockSplitter.h"
#include <QStyle>
#include <QFile>
#include <QMenu>

using namespace ads;


static QAction* addMenuDockAction(QMenu* qMenu,ads::CDockWidget* pDock)
{
    if(qMenu==nullptr||pDock==nullptr)
    {
        return nullptr;
    }
    auto action=pDock->toggleViewAction();
    action->setObjectName("action"+pDock->objectName());
    action->setText(pDock->windowTitle());
    qMenu->addAction(action);
    return action;
}
static QMenu* addMenuDockMenu(QMenu* qMenu,ads::CDockWidget* pDock)
{
    if(qMenu==nullptr||pDock==nullptr)
    {
        return nullptr;
    }
    QMenu *dockMenu=new QMenu(qMenu);
    dockMenu->setObjectName("menu"+pDock->objectName());
    dockMenu->setTitle(pDock->windowTitle());
    qMenu->addMenu(dockMenu);
    return dockMenu;
}


#endif // DOCKDEF_H
