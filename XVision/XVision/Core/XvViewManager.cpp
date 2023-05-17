#include "XvViewManager.h"
#include <QMutexLocker>

#include "BaseWidget.h"
#include "XvSingleApplication.h"
#include "AppMainWindow.h"
#include "DockMainManager.h"
/*[Work]*/
#include "UiXvWorkManager.h"
#include "FrmVisionWork.h"
/*[Core]*/
#include "FrmVisionDisplay.h"
/*[Output]*/
#include "FrmLogShow.h"
#include "FrmThreadMonitor.h"
#include "FrmXvFuncResult.h"

XvViewManager::XvViewManager(QObject *parent)
    : QObject{parent}
{

}

XvViewManager::~XvViewManager()
{

}

XvSingleApplication *XvViewManager::app() const
{
    return m_app;
}

XvViewManager *XvViewManager::s_Instance = NULL;
XvViewManager *XvViewManager::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvViewManager();
    }
  }
  return s_Instance;
}

AppMainWindow *XvViewManager::appMainWindow() const
{
    return m_appMainWindow;
}

DockMainManager *XvViewManager::dockMainManager() const
{
    return m_dockMainManager;
}

UiXvWorkManager *XvViewManager::uiXvWorkManager() const
{
    return m_uiXvWorkManager;
}

UiXvDisplayManager *XvViewManager::uiXvDisplayManager() const
{
    return m_uiXvDisplayManager;
}
void XvViewManager::setApp(XvSingleApplication *app)
{
    if(app)
    {
        m_app=app;
    }
}

void XvViewManager::setAppMainWindow(AppMainWindow *mw)
{
    if(mw)
    {
        m_appMainWindow=mw;
    }
}

void XvViewManager::setDockMainManager(DockMainManager *dockMainMgr)
{
    if(dockMainMgr)
    {
        m_dockMainManager=dockMainMgr;
    }
}

void XvViewManager::setUiXvWorkManager(UiXvWorkManager *uiXvWorkManager)
{
    if(uiXvWorkManager)
    {
        m_uiXvWorkManager=uiXvWorkManager;
    }
}

void XvViewManager::setUiXvDisplayManager(UiXvDisplayManager *uiXvDisplayManager)
{
    if(uiXvDisplayManager)
    {
        m_uiXvDisplayManager=uiXvDisplayManager;
    }
}

void XvViewManager::init()
{
    ///初始化主界面Dock
    auto funcSetDock=[&](DockMainManager::EDockArea area,BaseWidget* wdg)
    {
       auto dock= m_dockMainManager->addDockWidget(area,wdg);
       dock->setFeature(ads::CDockWidget::DockWidgetClosable,false);
       dock->setFeature(ads::CDockWidget::DockWidgetFloatable,true);
       return dock;
    };

    if(m_dockMainManager)
    {
        funcSetDock(DockMainManager::Core,UiVisionDisplay);
        funcSetDock(DockMainManager::Work,UiVisionWork);
        auto dock= funcSetDock(DockMainManager::Output,UiLogShow);
        funcSetDock(DockMainManager::Output,UiThreadMonitor);
        funcSetDock(DockMainManager::Output,UiXvFuncResult);
        m_dockMainManager->setAreaCurrentDockWidget(DockMainManager::Output,dock);
        m_dockMainManager->restoreState();
    }
}




