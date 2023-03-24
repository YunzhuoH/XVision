#include "AppMainWindow.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QWidgetAction>
#include <QStatusBar>
#include <QToolBar>
#include <QSettings>

#include "XTitleBar.h"
#include "XMatToolButton.h"
#include "XMatMenuBar.h"
#include "XMatMenu.h"
#include "XMatHLine.h"
#include "XMatToolBar.h"

#include "XvCoreManager.h"
#include "XvPluginManager.h"
#include "XvFuncAssembly.h"


#include "XvSingleApplication.h"
#include "XvViewManager.h"
#include "XvAppCoreManager.h"
#include "DockMainManager.h"

#include "DockDef.h"
#include "LangDef.h"

#include "XvUtils.h"

#define APPMAINWINDOW_CONFIG_PATH "Config/AppMainWindow.ini"

/*******************************/
//* [AppMainWindowPrivate]
/*******************************/

class AppMainWindowPrivate
{
    Q_DISABLE_COPY(AppMainWindowPrivate)
    Q_DECLARE_PUBLIC(AppMainWindow)

public:
    AppMainWindowPrivate(AppMainWindow *q):q_ptr(q){};
    virtual ~AppMainWindowPrivate(){};
public:
    ///初始化主界面:
    /// 1.设置标题Action
    /// 2.加载工具栏
    /// 3.加载活动主界面
    void initFrm();

    ///添加工具栏活动
    bool addToolBarAction(QAction *act);
public:
    AppMainWindow              *const q_ptr;///主界面

protected:
    ///初始化主界面标题栏
    /// 便捷菜单栏↓        ↓快捷按钮
    /// |□□□□□         ■  -□X|
    void initMwTitleBar(XTitleBar* tb);


    ///初始化主界面ToolBar
    /// 工具栏布局:
    ///  固定工具按钮↓   扩展灵活按钮↓
    ///  ———————————————
    ///  |□□□□□            ■■■|
    ///  ———————————————
    /// 左侧:常用工具按钮
    /// 右侧:ToolBar灵活按钮
    void initMwToolBar(QFrame* fm);


    ///初始化主界面工作界面
    ///视觉流程配置Dock(左侧)
    ///结果显示/扩展窗口Dock(右侧)
    /// 信息输出窗口(底部)
    void initMwMainWdg(QFrame* fm);

    ///初始化主界面状态栏
    /// 软件系统信息添加
    void initMwStatusBar(AppMainWindow* mw);

    ///主界面显示事件
    void showEvent();
    ///主界面关闭事件
    void closeEvent();
private://主界面窗口控件
    XMatMenuBar* menuBarTitle=nullptr;///标题栏菜单
    XMatHLine* hlineTitle=nullptr;///标题栏隔离线

    QFrame* fmToolBar=nullptr; ///工具栏Frame
    XMatToolBar* rightToolBar=nullptr; ///工具栏Frame右侧灵活工具栏

    XMatHLine* hlineMain=nullptr;///工具栏/主界面隔离线

    QFrame* fmMain=nullptr; ///主界面:Docking浮动

    XMatHLine* hlineStatus=nullptr;///状态栏隔离线
    QStatusBar* statusBar=nullptr; ///状态栏


};

void AppMainWindowPrivate::initFrm()
{
    Q_Q(AppMainWindow);
    q->setWindowTitle("XVision");
    q->titleBar()->setObjectName("xTitleBar");
    q->setWindowIcon(QIcon(":/images/App/XVision.png"));
    q->setMinimumSize(1000,600);

    auto mw = q->centralWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout(mw);
    verticalLayout->setSpacing(0);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    hlineTitle=new XMatHLine(mw);
    hlineTitle->setObjectName("hlineTitle");
    hlineTitle->setLineStyle(Qt::SolidLine);
    hlineTitle->setMinimumHeight(1);
    hlineTitle->setMaximumHeight(1);
    verticalLayout->addWidget(hlineTitle);

    fmToolBar=new QFrame(mw);
    fmToolBar->setObjectName("fmToolBar");
    fmToolBar->setMinimumSize(QSize(0, 50));
    fmToolBar->setMaximumSize(QSize(16777215, 50));
    fmToolBar->setFrameShape(QFrame::StyledPanel);
    fmToolBar->setFrameShadow(QFrame::Raised);
    verticalLayout->addWidget(fmToolBar);

    hlineMain=new XMatHLine(mw);
    hlineMain->setObjectName("hlineMain");
    hlineMain->setLineStyle(Qt::SolidLine);
    hlineMain->setMinimumHeight(1);
    hlineMain->setMaximumHeight(1);
    verticalLayout->addWidget(hlineMain);


    fmMain = new QFrame(mw);
    fmMain->setObjectName("fmMain");
    fmMain->setFrameShape(QFrame::StyledPanel);
    fmMain->setFrameShadow(QFrame::Raised);
    verticalLayout->addWidget(fmMain);

    hlineStatus=new XMatHLine(mw);
    hlineStatus->setObjectName("hlineStatus");
    hlineStatus->setLineStyle(Qt::SolidLine);
    hlineStatus->setMinimumHeight(1);
    hlineStatus->setMaximumHeight(1);
    verticalLayout->addWidget(hlineStatus);
    ///主界面四大区域初始化
    initMwTitleBar(q->titleBar());
    initMwToolBar(fmToolBar);
    initMwMainWdg(fmMain);
    initMwStatusBar(q);
}

bool AppMainWindowPrivate::addToolBarAction(QAction *act)
{
    if(!act) return false;
    if(rightToolBar)
    {
        rightToolBar->addAction(act);
        return true;
    }
    else
    {
        return false;
    }
}
///xie.y : 后续根据需求修改菜单
///建议把菜单栏加到QMap,其他类可以添加QMenu/QAction
void AppMainWindowPrivate::initMwTitleBar(XTitleBar* tb)
{
    if(!tb) return;
    tb->setMinimumHeight(30);
    tb->setMinBtnSize(30,30);
    tb->setMaxBtnSize(30,30);
    ///标题栏菜单
    menuBarTitle=new XMatMenuBar(tb);
    menuBarTitle->setObjectName("menuBarTitle");
    tb->setMenuBar(menuBarTitle);

    //*[文件菜单]*
    auto menu=new XMatMenu("文件",menuBarTitle);
    auto act=menu->addAction("新建方案");
    act->setIcon(QIcon(":/images/App/XVision.png"));
    menu->addAction("打开方案");
    auto subMenu= menu->addMenu("最近打开方案");
    subMenu->addAction("方案1");
    subMenu->addAction("方案2");
    subMenu->addSeparator();
    subMenu->addAction("方案3");
    subMenu->addAction("方案4");
    menuBarTitle->addMenu(menu);

    //*[设置菜单]*
    menu=new XMatMenu("设置",menuBarTitle);
    menu->setAttribute(Qt::WA_Hover);
    menu->addAction("软件设置");
    menu->addAction("视觉设置");
    menuBarTitle->addMenu(menu);

    //*[工具菜单]*
    menu=new XMatMenu("工具",menuBarTitle);
    menu->addAction("软件工具");
    menu->addAction("视觉工具");
    menuBarTitle->addMenu(menu);

    //*[系统菜单]*
    menu=new XMatMenu("系统",menuBarTitle);
    menu->addAction("视觉管理器");
    menu->addAction("通讯管理器");
    menuBarTitle->addMenu(menu);
    //*[帮助菜单]*
    menu=new XMatMenu("帮助",menuBarTitle);
    menu->addAction("语言");
    menu->addAction("关于");
    menuBarTitle->addMenu(menu);


    ///标题栏右侧控件
    XMatToolButton* btn = new XMatToolButton(tb);
    btn->setMinimumSize(28,28);
    btn->setText("");
    QIcon icon(":/images/App/XVision.png");
    btn->setIcon(icon);
    btn->setIconSize(QSize(20,20));
    tb->rightLayout()->addWidget(btn);
}

void AppMainWindowPrivate::initMwToolBar(QFrame* fm)
{
    Q_Q(AppMainWindow);
    auto funcAddBtn=[&](QHBoxLayout *layout,QIcon icon,QString tip="",QString text="")
    {

        auto fmH=fm->minimumHeight()-2;
        XMatToolButton* btn = new XMatToolButton(fm);
        btn->setMinimumSize(QSize(fmH, fmH));
        btn->setText(text);
        btn->setIcon(icon);
        btn->setToolTip(tip);
        btn->setIconSize(QSize(25,25));
        layout->addWidget(btn);
        return btn;
    };
    if(!fm) return;
    QHBoxLayout *hLayout = new QHBoxLayout(fm);
    hLayout->setSpacing(0);
    hLayout->setObjectName("verticalLayout");
    hLayout->setContentsMargins(0, 0, 0, 0);
    fm->setLayout(hLayout);

    auto btn= funcAddBtn(hLayout,QIcon(":/images/App/XVision.png"),"按钮1","按钮1");
    btn= funcAddBtn(hLayout,QIcon(":/images/App/XVision.png"),"按钮2","按钮2");
    btn= funcAddBtn(hLayout,QIcon(":/images/App/XVision.png"),"按钮3","按钮3");

    hLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding ,QSizePolicy::Minimum));
    rightToolBar=new XMatToolBar(fm);
    rightToolBar->setObjectName("rightToolBar");
    hLayout->addWidget(rightToolBar);
}

void AppMainWindowPrivate::initMwMainWdg(QFrame* fm)
{
   if(!fm) return;
   QVBoxLayout *verticalLayout = new QVBoxLayout(fm);
   verticalLayout->setSpacing(0);
   verticalLayout->setObjectName("verticalLayout");
   verticalLayout->setContentsMargins(0, 0, 0, 0);


   auto dockMgr=XvViewMgr->getDockMainManager();
   if(dockMgr)
   {
       auto dockMain=dockMgr->dockMainManager();
       if(dockMain)
       {
           dockMain->setParent(fm);
           verticalLayout->addWidget(dockMain);
       }
       else
       {
          Log_Critical(getLang(App_MainDockIsNull,"MainDock为空"));
       }
   }


}

void AppMainWindowPrivate::initMwStatusBar(AppMainWindow* mw)
{
    if(!mw) return;
    statusBar= new QStatusBar(mw);
    statusBar->setObjectName("statusBar");
    statusBar->setMinimumHeight(25);
    mw->setStatusBar(statusBar);
}

void AppMainWindowPrivate::showEvent()
{
    Q_Q(AppMainWindow);
    QSettings Settings(APPMAINWINDOW_CONFIG_PATH, QSettings::IniFormat);
    q->restoreGeometry(Settings.value("AppMainWindow/Geometry").toByteArray());
}

///关闭事件:
/// 保存界面配置
void AppMainWindowPrivate::closeEvent()
{
    Q_Q(AppMainWindow);
    QSettings Settings(APPMAINWINDOW_CONFIG_PATH,QSettings::IniFormat);
    Settings.setValue("AppMainWindow/Geometry", q->saveGeometry());
}


/*******************************/
//* [AppMainWindow]
/*******************************/


AppMainWindow::AppMainWindow(XvSingleApplication *app,QWidget *parent) :
    XFramelessWidget(parent),
    m_app(app),
    d_ptr(new AppMainWindowPrivate(this))
{
    d_ptr->initFrm();
}

AppMainWindow::~AppMainWindow()
{

}

bool AppMainWindow::addToolBarAction(QAction *act)
{
    return d_ptr->addToolBarAction(act);
}

void AppMainWindow::showEvent(QShowEvent *event)
{
    d_ptr->showEvent();
    return XFramelessWidget::showEvent(event);
}

void AppMainWindow::closeEvent(QCloseEvent *event)
{
    d_ptr->closeEvent();
    return XFramelessWidget::closeEvent(event);
}

