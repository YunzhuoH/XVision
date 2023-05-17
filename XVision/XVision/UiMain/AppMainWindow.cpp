#include "AppMainWindow.h"
//Qt
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QFrame>
#include <QWidgetAction>
#include <QStatusBar>
#include <QToolBar>
#include <QSettings>
#include <QDir>

//XWidget
#include "XTitleBar.h"
#include "XMatToolButton.h"
#include "XMatMenuBar.h"
#include "XMatMenu.h"
#include "XMatVLine.h"
#include "XMatHLine.h"
#include "XMatToolBar.h"
#include "XMessageBox.h"

//XvCore
#include "XvCoreManager.h"
#include "XvPluginManager.h"
#include "XvFuncAssembly.h"

//XVsion
#include "XvSingleApplication.h"
#include "XvViewManager.h"
#include "XvWorkManager.h"
#include "DockMainManager.h"
#include "DockDef.h"
#include "LangDef.h"
#include "UiUtils.h"

#include "FrmAbout.h"
//XvUtils
#include "XvUtils.h"

//XLanguage
#include <XLanguage>

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
    fmToolBar->setMinimumSize(QSize(0, 40));
    fmToolBar->setMaximumSize(QSize(16777215, 40));
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
    auto funcAddMenu=[&](QMenuBar* bar,const QString &text)
    {
        auto menu=new XMatMenu(text,bar);      
        bar->addMenu(menu);
        return menu;
    };
    auto funcAddAct=[&](QMenu *menu,const QString &text,const QString &objName,const QIcon &icon)
    {
        auto act=menu->addAction(text);
        act->setObjectName(objName);
        act->setIcon(icon);
        return act;
    };

    Q_Q(AppMainWindow);
    if(!tb) return;
    tb->setMinimumHeight(30);
    tb->setMinBtnSize(30,30);
    tb->setMaxBtnSize(30,30);
    ///标题栏菜单
    menuBarTitle=new XMatMenuBar(tb);
    menuBarTitle->setObjectName("menuBarTitle");
    tb->setMenuBar(menuBarTitle);



    //*[文件菜单]*
    auto menu=funcAddMenu(menuBarTitle,getLang(App_AppMainWindow_File,"文件"));
    auto act= funcAddAct(menu,getLang(App_AppMainWindow_NewProject,"新建项目"),"actNewProject",QIcon(":/images/Ui/AppMainWindowNewProject.svg"));
    QObject::connect(act,&QAction::triggered,q,&AppMainWindow::newProject);
    act= funcAddAct(menu,getLang(App_AppMainWindow_OpenProject,"打开项目"),"actOpenProject",QIcon(":/images/Ui/AppMainWindowOpenProject.svg"));
    QObject::connect(act,&QAction::triggered,q,&AppMainWindow::openProject);
    act= funcAddAct(menu,getLang(App_AppMainWindow_SaveProject,"保存项目"),"actSaveProject",QIcon(":/images/Ui/AppMainWindowSaveProject.svg"));
    QObject::connect(act,&QAction::triggered,q,&AppMainWindow::saveProject);


    //*[设置菜单]*
    menu=funcAddMenu(menuBarTitle,getLang(App_AppMainWindow_Setting,"设置"));
    act= funcAddAct(menu,getLang(App_AppMainWindow_ProjectSetting,"项目设置"),"actProjectSetting",QIcon(":/images/Ui/AppMainWindowProjectSetting.svg"));
    QObject::connect(act,&QAction::triggered,q,&AppMainWindow::projectSetting);
    act= funcAddAct(menu,getLang(App_AppMainWindow_SystemSetting,"系统设置"),"actSystemSetting",QIcon(":/images/Ui/AppMainWindowSystemSetting.svg"));
    QObject::connect(act,&QAction::triggered,q,&AppMainWindow::systemSetting);

    //*[系统菜单]*
    menu=funcAddMenu(menuBarTitle,getLang(App_AppMainWindow_System,"系统"));
//TODO
    //*[系统菜单]*
    menu=funcAddMenu(menuBarTitle,getLang(App_AppMainWindow_Tool,"工具"));
//TODO
    //*[帮助菜单]*
    menu=funcAddMenu(menuBarTitle,getLang(App_AppMainWindow_Help,"帮助"));
    auto subMenu=menu->addMenu(getLang(App_AppMainWindow_Language,"语言"));
    subMenu->setIcon(QIcon(":/images/Ui/AppMainWindowLanguage.svg"));
    auto langs=XLang->getLangTypes();
    auto curLang=XLang->getCurLangType();
    foreach (auto key, langs.keys())
    {
       auto act= subMenu->addAction(langs[key]);
       act->setCheckable(true);
       act->setData(key);
       QObject::connect(act,&QAction::triggered,q,[=]()
       {
           auto key=act->data().toString();
           auto bRet=  XLang->switchLang(key);
           if(!bRet)
           {
               XMessageBox::warning(getLang(App_UiCommon_Warning,"警告"),getLang(App_AppMainWindow_MsgSwitchLangError,"切换语言失败"),nullptr,
                                    U_getXMessageBoxButtonTexts({XMessageBox::StandardButton::Close}),XMessageBox::StandardButton::Close);
                return;
           }
           auto acts=subMenu->actions();
           foreach (auto a, acts)
           {
               a->setChecked(false);
           }
           act->setChecked(true);
           XMessageBox::information(getLang(App_UiCommon_Info,"信息"),getLang(App_AppMainWindow_MsgSwitchLangSuccess,"切换语言成功，请重启软件"),nullptr,
                                    U_getXMessageBoxButtonTexts({XMessageBox::StandardButton::Close}),XMessageBox::StandardButton::Close);
       });
    }
    foreach (auto a, subMenu->actions())
    {
        auto key=a->data().toString();
        if(key==curLang)
        {
            a->setChecked(true);
            break;
        }
    }

    act= funcAddAct(menu,getLang(App_AppMainWindow_HelpDoc,"帮助文档"),"actHelpDoc",QIcon(":/images/Ui/AppMainWindowHelpDoc.svg"));
    QObject::connect(act,&QAction::triggered,q,[](){
        QDesktopServices deskSer;
        QString dir=qApp->applicationDirPath()+"/Help";
        QDir qDir(dir);
        if(!qDir.exists())
        {
            qDir.mkdir(dir);
        }
        deskSer.openUrl(QUrl("file:///"+dir));
    });
    act= funcAddAct(menu,getLang(App_AppMainWindow_About,"关于"),"actAbout",QIcon(":/images/Ui/AppMainWindowAbout.svg"));
    QObject::connect(act,&QAction::triggered,q,&AppMainWindow::about);
}

void AppMainWindowPrivate::initMwToolBar(QFrame* fm)
{
    Q_Q(AppMainWindow);

    auto funcBtnTodo=[&](XMatToolButton* btn)
    {
        QObject::connect(btn,&XMatToolButton::clicked,q,[]()
        {
            Log_Critical("xie.y todo:此功能未完成");
        });
    };

    auto funcAddBtn=[&](QHBoxLayout *layout,const QString &text,const QString &objName,QIcon icon,const QString &tip="")
    {

        auto fmH=fm->minimumHeight()-2;
        XMatToolButton* btn = new XMatToolButton(fm);
        btn->setObjectName(objName);
        btn->setMinimumSize(QSize(fmH, fmH));
        btn->setText(text);
        btn->setIcon(icon);
        btn->setToolTip(tip);
        btn->setIconSize(QSize(25,25));
        layout->addWidget(btn);
        funcBtnTodo(btn);
        return btn;
    };
    auto funcAddVLine=[&](QHBoxLayout *layout,const QString &objName)
    {
       auto vline= new XMatVLine(fm);
       vline->setObjectName(objName);
       vline->setLineWidth(1);
       vline->setLineCurLen(5);
       layout->addWidget(vline);
       return vline;
    };

    if(!fm) return;
    QHBoxLayout *hLayout = new QHBoxLayout(fm);
    hLayout->setSpacing(0);
    hLayout->setObjectName("verticalLayout");
    hLayout->setContentsMargins(0, 0, 0, 0);
    fm->setLayout(hLayout);
//项目保存加载
    auto btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_SaveProject,"保存项目"),"btnSaveProject", QIcon(":/images/Ui/AppMainWindowSaveProject.svg"),getLang(App_AppMainWindow_SaveProject,"保存项目"));
    QObject::connect(btn,&QToolButton::clicked,q,&AppMainWindow::saveProject);    
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_OpenProject,"打开项目"),"btnOpenProject", QIcon(":/images/Ui/AppMainWindowOpenProject.svg"),getLang(App_AppMainWindow_OpenProject,"打开项目"));
    QObject::connect(btn,&QToolButton::clicked,q,&AppMainWindow::openProject);
    funcAddVLine(hLayout,"vLine1");
//项目操作
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_ProjectOnceRun,"项目单次运行"),"btnProjectOnceRun",
                    QIcon(":/images/Ui/AppMainWindowProjectOnceRun.svg"),getLang(App_AppMainWindow_ProjectOnceRun,"项目单次运行"));
    QObject::connect(btn,&QToolButton::clicked,q,&AppMainWindow::projectOnceRun);
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_ProjectLoopRun,"项目重复运行"),"btnProjectLoopRun",
                    QIcon(":/images/Ui/AppMainWindowProjectLoopRun.svg"),getLang(App_AppMainWindow_ProjectLoopRun,"项目重复运行"));
    QObject::connect(btn,&QToolButton::clicked,q,&AppMainWindow::projectLoopRun);
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_ProjectStop,"项目停止运行"),"btnProjectStop",
                    QIcon(":/images/Ui/AppMainWindowProjectStop.svg"),getLang(App_AppMainWindow_ProjectStop,"项目停止运行"));
    btn->setRippleColor(Qt::red);
    QObject::connect(btn,&QToolButton::clicked,q,&AppMainWindow::projectStop);

    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_ProjectSetting,"项目设置"),"btnProjectSetting",
                    QIcon(":/images/Ui/AppMainWindowProjectSetting.svg"),getLang(App_AppMainWindow_ProjectSetting,"项目设置"));

    funcAddVLine(hLayout,"vLine2");
//全局管理/变量监控/全局脚本
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_GlobalManager,"全局管理"),"btnGlobalManager",
                    QIcon(":/images/Ui/AppMainWindowGlobalManager.svg"),getLang(App_AppMainWindow_GlobalManager,"全局管理"));
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_GlobalScript,"全局脚本"),"btnGlobalScript",
                    QIcon(":/images/Ui/AppMainWindowGlobalScript.svg"),getLang(App_AppMainWindow_GlobalScript,"全局脚本"));
    btn= funcAddBtn(hLayout,getLang(App_AppMainWindow_VariantManager,"变量管理"),"btnVariantManager",
                    QIcon(":/images/Ui/AppMainWindowVariantManager.svg"),getLang(App_AppMainWindow_VariantManager,"变量管理"));

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


   auto dockMgr=XvViewMgr->dockMainManager();
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
    q->getApp()->quit();
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


//xie.y todo
//新建项目
void AppMainWindow::newProject()
{

}

void AppMainWindow::openProject()
{

}

void AppMainWindow::saveProject()
{

}

void AppMainWindow::projectOnceRun()
{

}

void AppMainWindow::projectLoopRun()
{

}

void AppMainWindow::projectStop()
{

}

void AppMainWindow::projectSetting()
{

}

void AppMainWindow::systemSetting()
{

}

void AppMainWindow::about()
{
    FrmAbout ab;
    ab.exec();
}
