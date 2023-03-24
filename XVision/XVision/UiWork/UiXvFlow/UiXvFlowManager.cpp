#include "UiXvFlowManager.h"

#include "XGraphicsScene.h"
#include "XvUtils.h"
#include "XGraphicsView.h"
#include "XvGraphicsFactory.h"
#include "XMatScrollBar.h"
#include "XMatToolButton.h"
#include <QLayout>
#include "LangDef.h"
#include "UiUtils.h"

UiXvFlowManager::UiXvFlowManager(QObject *parent)
    :QObject{parent}
{
    init();
}

UiXvFlowManager::~UiXvFlowManager()
{

}

XGraphicsScene *UiXvFlowManager::addFlowScene(const QString &id,const QString &name)
{
    if(m_mapFlowScene.contains(id))
    {
        return m_mapFlowScene[id];
    }

    auto funcCreateDock=[&](XGraphicsView* view,const QString &sceneId,const QString &sceneName)
    {
        ads::CDockWidget* dock = new ads::CDockWidget("dock_"+sceneId);
        dock->layout()->setContentsMargins(0,0,0,0);
        dock->layout()->setSpacing(0);
        dock->setWidget(view);
        dock->setWindowTitle(sceneName);
        dock->setFeature(ads::CDockWidget::DockWidgetClosable,false);
        dock->setFeature(ads::CDockWidget::DockWidgetFloatable,false);
        dock->setFeature(ads::CDockWidget::DockWidgetMovable,false);
        dock->tabWidget()->setToolTip(sceneName);
        dock->tabWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
        return dock;
    };

    if(id.isEmpty()) return nullptr;
    auto scene = new XGraphicsScene();
    scene->setObjectName("scene_"+id);
    scene->setDisplayRect(0,0,4000,4000);
    scene->getView()->centerOn(0,0);
    scene->getView()->zoomToRect(QRectF(0,0,500,500));
    scene->setXItemDelegateFactory(new XvGraphicsItemFactory(scene));
    scene->setSceneTag(id);
    auto bar=new XMatScrollBar(scene->getView());
    bar->setContextMenuPolicy(Qt::CustomContextMenu);
    bar->setHideOnMouseOut(false);
    scene->getView()->setVerticalScrollBar(bar);
    bar=new XMatScrollBar(scene->getView());
    bar->setContextMenuPolicy(Qt::CustomContextMenu);
    bar->setHideOnMouseOut(false);
    scene->getView()->setHorizontalScrollBar(bar);
    scene->getView()->verticalScrollBar()->setContextMenuPolicy(Qt::CustomContextMenu);
    scene->getView()->horizontalScrollBar()->setContextMenuPolicy(Qt::CustomContextMenu);

    auto dockNew=funcCreateDock(scene->getView(),id,name);
    if(m_dockFlowArea==nullptr)
    {
        Log_Critical("m_dockAreaFlow==nullptr");



    }
    else
    {
        auto dock=m_dockFlowArea->dockWidget(0);
        if(dock&&!dock->widget())//不存在widget进行设置，否则新建
        {
            dock->layout()->setContentsMargins(0,0,0,0);
            dock->layout()->setSpacing(0);
            dock->setWidget(scene->getView());
            dock->setWindowTitle(name);
            dock->setFeature(ads::CDockWidget::DockWidgetClosable,false);
            dock->setFeature(ads::CDockWidget::DockWidgetFloatable,false);
            dock->setFeature(ads::CDockWidget::DockWidgetMovable,false);
            dock->tabWidget()->setToolTip(name);
            dock->tabWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
        }
        else
        {
            auto dockNew=funcCreateDock(scene->getView(),id,name);
            m_dockFlowManager->addDockWidget(ads::DockWidgetArea::CenterDockWidgetArea, dockNew,m_dockFlowArea);
        }

    }
    m_mapFlowScene[id]=scene;
    return scene;
}

XGraphicsScene *UiXvFlowManager::getFlowScene(const QString &id)
{
    if(m_mapFlowScene.contains(id))
    {
        return m_mapFlowScene[id];
    }
    return nullptr;
}

void UiXvFlowManager::init()
{
    auto funcCreateDock=[&]()
    {
        ads::CDockWidget* dock = new ads::CDockWidget("NoFlow");
        dock->layout()->setContentsMargins(0,0,0,0);
        dock->layout()->setSpacing(0);
        dock->setFeature(ads::CDockWidget::DockWidgetClosable,false);
        dock->setFeature(ads::CDockWidget::DockWidgetFloatable,false);
        dock->setFeature(ads::CDockWidget::DockWidgetMovable,false);
        dock->tabWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
        return dock;
    };
    ///初始化FlowDock
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasTabsMenuButton, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetTitle, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetIcon, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::HideSingleCentralWidgetTitleBar, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewIsDynamic, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DragPreviewShowsContentPixmap, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true);
    m_dockFlowManager=new CDockManager();
    m_dockFlowManager->setObjectName("dockFlowManager");
    m_dockFlowManager->setStyleSheet(XvUtils::getStyleByPath(":/style/DockFlow_Default.css"));

    auto dock=funcCreateDock();
    m_dockFlowArea= m_dockFlowManager->addDockWidget(ads::CenterDockWidgetArea, dock);
    m_dockFlowArea->titleBar()->setContextMenuPolicy(Qt::CustomContextMenu);
    auto bar= m_dockFlowArea->titleBar();
    auto btnSize=bar->height();
    auto iconSize=btnSize-2;

    auto btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowProp");
    U_initSetButton(btn,getLang(App_UiCommon_FlowProp,"流程属性"),getLang(App_UiCommon_FlowProp,"流程属性"),
                    QIcon(":/images/Ui/UiCommonFlowProp.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowOnceRun");
    U_initSetButton(btn,getLang(App_UiCommon_FlowOnceRun,"流程单次运行"),getLang(App_UiCommon_FlowOnceRun,"流程单次运行"),
                    QIcon(":/images/Ui/UiCommonFlowOnceRun.svg"),iconSize,
                     QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowLoopRun");
    U_initSetButton(btn,getLang(App_UiCommon_FlowLoopRun,"流程重复运行"),getLang(App_UiCommon_FlowLoopRun,"流程重复运行"),
                    QIcon(":/images/Ui/UiCommonFlowLoopRun.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);


    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowStop");
    U_initSetButton(btn,getLang(App_UiCommon_FlowStop,"流程停止运行"),getLang(App_UiCommon_FlowStop,"流程停止运行"),
                    QIcon(":/images/Ui/UiCommonFlowStop.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    btn->setRippleColor(Qt::red);
    bar->insertWidget(-1, btn);




    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowDel");
    U_initSetButton(btn,getLang(App_UiCommon_FlowDel,"流程删除"),getLang(App_UiCommon_FlowDel,"流程删除"),
                    QIcon(":/images/Ui/UiCommonFlowDel.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);


    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowAdd");
    U_initSetButton(btn,getLang(App_UiCommon_FlowAdd,"流程添加"),getLang(App_UiCommon_FlowAdd,"流程添加"),
                    QIcon(":/images/Ui/UiCommonFlowAdd.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,[&]()
    {
        QString id=QString("F-%1").arg(rand());
        QString name=QString("Flow-%1").arg(rand());
        Log_Info(QString("添加流程:Id-%1 Name-%2").arg(id).arg(name));
        addFlowScene(id,name);
    });

    ///初始化Flow状态栏
    m_flowStatusBar=new QStatusBar();
    m_flowStatusBar->setObjectName("flowStatusBar");
    m_flowStatusBar->setMinimumHeight(25);
}
