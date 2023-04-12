#include "DockMainManager.h"
#include "XvUtils.h"

#include <QLayout>
#include <QSettings>

#define DOCKMAIN_CONFIG_PATH "Config/DockMainManager.ini"

DockMainManager::DockMainManager(QObject *parent)
    :QObject{parent}
{
    init();
}

DockMainManager::~DockMainManager()
{
    QSettings Settings(DOCKMAIN_CONFIG_PATH,QSettings::IniFormat);
    Settings.setValue("DockMainManager/DockMainManager", m_DockMainManager->saveState());

}




CDockWidget* DockMainManager::addDockWidget(const EDockArea &area, QWidget *widget)
{
    auto funcCreateDock=[&](QWidget* wdg)
    {
        ads::CDockWidget* dock = new ads::CDockWidget("dock_"+wdg->objectName());
        dock->layout()->setContentsMargins(0,0,0,0);
        dock->layout()->setSpacing(0);
        dock->setWidget(wdg);
        dock->setWindowTitle(wdg->windowTitle());
        dock->setIcon(wdg->windowIcon());
        dock->setWindowIcon(wdg->windowIcon());
        dock->tabWidget()->setContextMenuPolicy(Qt::NoContextMenu);
        return dock;
    };

    if(!widget) return nullptr;
    if(!m_mapDockAreaWidget.contains(area)) return nullptr;

    auto dockArea=m_mapDockAreaWidget[area];
    auto dock=dockArea->dockWidget(0);
    if(dock&&!dock->widget())//不存在widget进行设置，否则新建
    {
        dock->setWidget(widget);
        dock->setWindowTitle(widget->windowTitle());
        dock->setWindowIcon(widget->windowIcon());
        dock->setIcon(widget->windowIcon());
        dock->tabWidget()->setContextMenuPolicy(Qt::NoContextMenu);
        return dock;
    }
    else
    {
        auto dockNew=funcCreateDock(widget);
        auto dockAreaNew= m_DockMainManager->addDockWidget(ads::DockWidgetArea::CenterDockWidgetArea, dockNew,dockArea);
        dockAreaNew->titleBar()->setContextMenuPolicy(Qt::NoContextMenu);
        return dockNew;
    }

    return nullptr;
}

void DockMainManager::setAreaCurrentIndex(const EDockArea &area, int idx)
{
    if(!m_mapDockAreaWidget.contains(area)) return;
    auto dockArea=m_mapDockAreaWidget[area];
    dockArea->setCurrentIndex(idx);
}

void DockMainManager::setAreaCurrentDockWidget(const EDockArea &area, CDockWidget *dock)
{
    if(!m_mapDockAreaWidget.contains(area)) return;
    auto dockArea=m_mapDockAreaWidget[area];
    dockArea->setCurrentDockWidget(dock);
}

void DockMainManager::restoreState()
{
    ///获取配置
    QSettings Settings(DOCKMAIN_CONFIG_PATH, QSettings::IniFormat);
    auto dockState= Settings.value("DockMainManager/DockMainManager");
    if(dockState.isNull())
    {
       QSettings setDefault(":/config/DockMainManagerDefault.ini",QSettings::IniFormat);
       dockState= setDefault.value("DockMainManager/DockMainManager");
    }
    m_DockMainManager->restoreState(dockState.toByteArray());
}

void DockMainManager::init()
{
    auto funcCreateDock=[&](QString title)
    {
        ads::CDockWidget* dock = new ads::CDockWidget(title);
        dock->layout()->setContentsMargins(0,0,0,0);
        dock->layout()->setSpacing(0);
        dock->setFeature(ads::CDockWidget::DockWidgetClosable, false);
        dock->setFeature(ads::CDockWidget::DockWidgetFloatable,false);
        dock->tabWidget()->setContextMenuPolicy(Qt::NoContextMenu);
        dock->setContextMenuPolicy(Qt::NoContextMenu);
        return dock;
    };
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasTabsMenuButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetTitle, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetIcon, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::HideSingleCentralWidgetTitleBar, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewIsDynamic, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewShowsContentPixmap, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true);
    m_DockMainManager=new CDockManager();
    m_DockMainManager->setContextMenuPolicy(Qt::NoContextMenu);
    m_mapDockAreaWidget.clear();


    auto dock=funcCreateDock("DockCore");
    auto dockArea= m_DockMainManager->addDockWidget(ads::CenterDockWidgetArea, dock);
    dockArea->titleBar()->setContextMenuPolicy(Qt::NoContextMenu);
    dockArea->setContextMenuPolicy(Qt::NoContextMenu);
    m_mapDockAreaWidget[EDockArea::Core]=dockArea;

    dock=funcCreateDock("DockOutput");
    dockArea= m_DockMainManager->addDockWidget(ads::BottomDockWidgetArea, dock,dockArea);
    dockArea->titleBar()->setContextMenuPolicy(Qt::NoContextMenu);
    dockArea->setContextMenuPolicy(Qt::NoContextMenu);
    m_mapDockAreaWidget[EDockArea::Output]=dockArea;


    dock=funcCreateDock("DockWork");
    dockArea= m_DockMainManager->addDockWidget(ads::LeftDockWidgetArea, dock);
    dockArea->titleBar()->setContextMenuPolicy(Qt::NoContextMenu);
    dockArea->setContextMenuPolicy(Qt::NoContextMenu);
    m_mapDockAreaWidget[EDockArea::Work]=dockArea;

    m_DockMainManager->setStyleSheet(XvUtils::getStyleByPath(":/style/DockMain_Default.css"));

}
