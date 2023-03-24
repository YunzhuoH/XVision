#include "XvSingleApplication.h"
#include <XLogger>
#include "LangDef.h"
#include "AppMainWindow.h"
#include "DockMainManager.h"
#include "UiXvFlowManager.h"

#include "XvAppCoreManager.h"
#include "XvViewManager.h"
#include "XvUtils.h"

#ifdef QBREAKPAD_ENABLE
#include "QBreakpadHandler.h"
#endif

const SingleApplication::Options opts = SingleApplication::ExcludeAppPath | SingleApplication::ExcludeAppVersion | SingleApplication::SecondaryNotification;



XvSingleApplication::XvSingleApplication(int &argc, char **argv)
: SingleApplication(argc, argv, false, opts)
{

}

void XvSingleApplication::init()
{

#ifdef QBREAKPAD_ENABLE
    //设置Crash目录
    QBreakpadInstance.setDumpPath("Crash");
#endif

    //初始化多语言管理器
    XLang->init();
    //初始化日志管理器
    XLog->init();
    //记录日志
    Log_Event(getLang(App_RunStart,"软件开始运行"));
    //设置界面风格
    this->setStyleSheet(XvUtils::getStyleByPath(":/style/Light_Default.css"));
    //初始化核心管理器
    XvAppCoreMgr->init();

    //界面管理器设置初始化
    XvViewMgr->setDockMainManager(new DockMainManager(this));
    XvViewMgr->setUiXvFlowManager(new UiXvFlowManager(this));
    XvViewMgr->setAppMainWindow(new AppMainWindow(this));

    ///进行初始化
    XvViewMgr->init();
}

void XvSingleApplication::uninit()
{
    //反初始化核心管理器
    XvAppCoreMgr->uninit();
    //日志记录
    Log_Event(getLang(App_RunEnd,"软件运行结束"));
    //反初始化多语言管理器
    XLang->uninit();
}

int XvSingleApplication::run()
{
    //主界面最大化
    XvViewMgr->getMainWindow()->show();
    return this->exec();
}
