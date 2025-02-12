﻿#include "XvSingleApplication.h"

#include <QElapsedTimer>

#include "LangDef.h"
#include "AppMainWindow.h"
#include "DockMainManager.h"
#include "UiXvWorkManager.h"
#include "UiXvDisplayManager.h"

#include "XvWorkManager.h"
#include "XvViewManager.h"
#include "XvUtils.h"

#ifdef QBREAKPAD_ENABLE
#include "QBreakpadHandler.h"
#endif

const SingleApplication::Options opts = SingleApplication::ExcludeAppPath | SingleApplication::ExcludeAppVersion | SingleApplication::SecondaryNotification;


/**************************************************************/
//* [UXvSingleApplicationPrivate]
/**************************************************************/
class XvSingleApplicationPrivate
{
    Q_DISABLE_COPY(XvSingleApplicationPrivate)
    Q_DECLARE_PUBLIC(XvSingleApplication)

public:
    XvSingleApplicationPrivate(XvSingleApplication *q):q_ptr(q)
    {
        runElapsedTimer=new QElapsedTimer;
    };
    ~XvSingleApplicationPrivate()
    {
        delete runElapsedTimer;
        runElapsedTimer=nullptr;
    };

public:
    XvSingleApplication              *const q_ptr;
    QElapsedTimer*                  runElapsedTimer=nullptr;//运行计时器

};

/**************************************************************/
//* [XvSingleApplication]
/**************************************************************/

XvSingleApplication::XvSingleApplication(int &argc, char **argv)
: SingleApplication(argc, argv, false, opts),d_ptr(new XvSingleApplicationPrivate(this)),
  m_bInitFinish(false),  m_bIsRunning(false)
{

}

XvSingleApplication::~XvSingleApplication()
{

}

void XvSingleApplication::init()
{
    Q_D(XvSingleApplication);
    m_bInitFinish=false;
    m_bIsRunning=true;
    setOrganizationName("XVision");
    setApplicationName("XVision");

#ifdef QBREAKPAD_ENABLE
    //设置Crash目录
    QBreakpadInstance.setDumpPath("Crash");
#endif
    d->runElapsedTimer->start();
    //初始化多语言管理器
    XLang->init();

    //初始化日志管理器
    XLog->init();
    XLog->setSignalLogPattern("[%H:%M:%S.%e] %v");

    //记录日志
    Log_Event(getLang(App_Common_RunStart,"软件开始运行"));

    //设置界面风格
    this->setStyleSheet(XvUtils::getStyleByPath(":/style/Light_Default.css"));

    //初始化工作管理器
    XvWorkMgr->init();

    //界面管理器设置初始化
    XvViewMgr->setApp(this);
    XvViewMgr->setDockMainManager(new DockMainManager(this));
    XvViewMgr->setUiXvWorkManager(new UiXvWorkManager(this));
    XvViewMgr->setUiXvDisplayManager(new UiXvDisplayManager(this));
    XvViewMgr->setAppMainWindow(new AppMainWindow(this));
    ///进行初始化
    XvViewMgr->init();

    m_bInitFinish=true;
    Log_Info(getLang(App_Common_InitFinish,"系统初始化完成"));
}



void XvSingleApplication::uninit()
{
    //反初始化工作管理器
    XvWorkMgr->uninit();
    //日志记录
    Log_Event(getLang(App_Common_RunEnd,"软件运行结束"));
    //反初始化多语言管理器
    XLang->uninit();

    m_bInitFinish=false;
    m_bIsRunning=false;
}

bool XvSingleApplication::isInit()
{
    return m_bInitFinish;
}

int XvSingleApplication::run()
{
    ///工作管理器初始项目
    XvWorkMgr->onInitWork();
    //主界面最大化
    XvViewMgr->appMainWindow()->showMaximized();
    return this->exec();
}

qint64 XvSingleApplication::getAppRunTime()
{
    Q_D(XvSingleApplication);
    return d->runElapsedTimer->elapsed();
}


