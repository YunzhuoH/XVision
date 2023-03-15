#include "AppMainWindow.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QWidgetAction>
#include <QStatusBar>
#include <QToolBar>
#include "XTitleBar.h"
#include "XMatToolButton.h"
#include "XMatMenuBar.h"
#include "XMatMenu.h"
#include "XMatHLine.h"


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
public:
    AppMainWindow              *const q_ptr;///主界面

protected:
    ///初始化主界面标题栏
    void initMwTitleBar(XTitleBar* tb);
    ///初始化主界面ToolBar
    void initMwToolBar(QFrame* fm);
    ///初始化主界面工作界面
    void initMwWorkWdg(QFrame* fm);
    ///初始化主界面状态栏
    void initMwStatusBar(AppMainWindow* mw);

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

    auto fmToolBar=new QFrame(mw);
    fmToolBar->setObjectName("toolBarMain");
    fmToolBar->setMinimumSize(QSize(0, 50));
    fmToolBar->setMaximumSize(QSize(16777215, 50));
    fmToolBar->setFrameShape(QFrame::StyledPanel);
    fmToolBar->setFrameShadow(QFrame::Raised);
    verticalLayout->addWidget(fmToolBar);


    QFrame *fmMain = new QFrame(mw);
    fmMain->setObjectName("fmMain");
    fmMain->setFrameShape(QFrame::StyledPanel);
    fmMain->setFrameShadow(QFrame::Raised);
    verticalLayout->addWidget(fmMain);
    auto hline=new XMatHLine(mw);
    hline->setObjectName("hLineMain");
    hline->setLineStyle(Qt::SolidLine);
    hline->setMinimumHeight(1);
    hline->setMaximumHeight(1);
    verticalLayout->addWidget(hline);
    ///主界面四大区域初始化
    initMwTitleBar(q->titleBar());
    initMwToolBar(fmToolBar);
    initMwWorkWdg(fmMain);
    initMwStatusBar(q);
}
//xie.y : 后续根据需求修改菜单
void AppMainWindowPrivate::initMwTitleBar(XTitleBar* tb)
{
    if(!tb) return;
    tb->setMinimumHeight(30);
    tb->setMinBtnSize(30,30);
    tb->setMaxBtnSize(30,30);
    ///标题栏菜单
    auto menuBar=new XMatMenuBar(tb);
    menuBar->setObjectName("menuBarMain");
    tb->setMenuBar(menuBar);

    //*[文件菜单]*
    auto menu=new XMatMenu("文件",menuBar);
    auto act=menu->addAction("新建方案");
    act->setIcon(QIcon(":/images/App/XVision.png"));
    menu->addAction("打开方案");
    auto subMenu= menu->addMenu("最近打开方案");
    subMenu->addAction("方案1");
    subMenu->addAction("方案2");
    subMenu->addSeparator();
    subMenu->addAction("方案3");
    subMenu->addAction("方案4");
    menuBar->addMenu(menu);

    //*[设置菜单]*
    menu=new XMatMenu("设置",menuBar);
    menu->setAttribute(Qt::WA_Hover);
    menu->addAction("软件设置");
    menu->addAction("视觉设置");
    menuBar->addMenu(menu);

    //*[工具菜单]*
    menu=new XMatMenu("工具",menuBar);
    menu->addAction("软件工具");
    menu->addAction("视觉工具");
    menuBar->addMenu(menu);

    //*[系统菜单]*
    menu=new XMatMenu("系统",menuBar);
    menu->addAction("视觉管理器");
    menu->addAction("通讯管理器");
    menuBar->addMenu(menu);
    //*[帮助菜单]*
    menu=new XMatMenu("帮助",menuBar);
    menu->addAction("语言");
    menu->addAction("关于");
    menuBar->addMenu(menu);


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
    hLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding ,QSizePolicy::Minimum));
    btn= funcAddBtn(hLayout,QIcon(":/images/App/XVision.png"),"按钮2","按钮2");
    btn= funcAddBtn(hLayout,QIcon(":/images/App/XVision.png"),"按钮3","按钮3");
}

void AppMainWindowPrivate::initMwWorkWdg(QFrame* fm)
{
   if(!fm) return;
   QVBoxLayout *verticalLayout = new QVBoxLayout(fm);
   verticalLayout->setSpacing(0);
   verticalLayout->setObjectName("verticalLayout");
   verticalLayout->setContentsMargins(0, 0, 0, 0);

}

void AppMainWindowPrivate::initMwStatusBar(AppMainWindow* mw)
{
    if(!mw) return;
    auto bar= new QStatusBar(mw);
    bar->setObjectName("sBarMain");
    bar->setMinimumHeight(25);
    mw->setStatusBar(bar);
}


/*******************************/
//* [AppMainWindow]
/*******************************/


AppMainWindow::AppMainWindow(QWidget *parent) :
    XFramelessWidget(parent),
    d_ptr(new AppMainWindowPrivate(this))
{
    d_ptr->initFrm();
}

AppMainWindow::~AppMainWindow()
{

}

