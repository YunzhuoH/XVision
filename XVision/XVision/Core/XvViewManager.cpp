#include "XvViewManager.h"
#include <QMutexLocker>

#include "BaseWidget.h"
#include "AppMainWindow.h"
#include "DockMainManager.h"
#include "UiXvFlowManager.h"
#include "FrmVisionWork.h"
#include "FrmVisionImage.h"
#include "FrmLogShow.h"

XvViewManager::XvViewManager(QObject *parent)
    : QObject{parent}
{

}

XvViewManager::~XvViewManager()
{

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

AppMainWindow *XvViewManager::getMainWindow() const
{
    return m_appMainWindow;
}

DockMainManager *XvViewManager::getDockMainManager() const
{
    return m_dockMainManager;
}

UiXvFlowManager *XvViewManager::getUiXvFlowManager() const
{
    return m_uiXvFlowManager;
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

void XvViewManager::setUiXvFlowManager(UiXvFlowManager *uiXvFlowManager)
{
    if(uiXvFlowManager)
    {
        m_uiXvFlowManager=uiXvFlowManager;
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

    };

    if(m_dockMainManager)
    {
        funcSetDock(DockMainManager::Core,UiVisionImage);
        funcSetDock(DockMainManager::Work,UiVisionWork);
        funcSetDock(DockMainManager::Output,UiLogShow);
        m_dockMainManager->restoreState();
    }
    if(m_uiXvFlowManager)
    {

    }

}



