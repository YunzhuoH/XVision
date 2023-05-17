#include "UiXvWorkManager.h"
//Qt
#include <QLayout>
#include <QGraphicsSceneMouseEvent>
//XFlowGraphics
#include "XFlowGraphicsScene.h"
#include "XFlowGraphicsView.h"
#include "XvGraphicsFactory.h"
#include "XFlowGraphicsItem.h"
#include "XFlowGraphicsConnectLink.h"
#include "XFlowGraphicsTextEdit.h"

//XWidget
#include "XMatLabel.h"
#include "XMatScrollBar.h"
#include "XMatSlider.h"
#include "XMatToolButton.h"
#include "XInputDialog.h"
#include "XMessageBox.h"

//XConcurrent
#include "XConcurrentManager.h"

//XVsion
#include "LangDef.h"
#include "UiUtils.h"
#include "XvUtils.h"
#include "XvWorkManager.h"
#include "FrmXvFlowConfig.h"

//XvCore
#include "XvFuncAssembly.h"
#include "XvFunc.h"
#include "XvFlow.h"
#include "XvProject.h"
#include "XvCoreDef.h"
#include "XvCoreHelper.h"

#define FlowId  "FlowId"

using namespace XvCore;
///静态工具内联函数:流程更新Tab的ToolTip
inline static void updateFlowToolTip(CDockWidgetTab* tab, XvFlow* flow)
{
    if(!tab||!flow)
    {
        return;
    }
    static QString strFlowId=getLang(App_UiXvWorkMgr_FlowId,"流程ID");
    static QString strFlowName=getLang(App_UiXvWorkMgr_FlowName,"流程名");
    static QString strFlowIdx=getLang(App_UiXvWorkMgr_FlowRunIdx,"当前运行序号");
    static QString strRunMsg=getLang(App_UiXvWorkMgr_FlowRunMsg,"运行信息");
    static QString strRunElapsed=getLang(App_UiXvWorkMgr_FlowRunElapsed,"运行耗时");


    auto runInfo=flow->getXvFuncRunInfo();
    QString tip;
    tip=QString(strFlowName+":%1\r\n"+
                strFlowId+":%2\r\n"+
                strFlowIdx+":%3\r\n"+
                strRunMsg+":%4\r\n"+
                strRunElapsed+":%5ms")
             .arg(flow->flowName())
             .arg(flow->flowId())
             .arg(runInfo.runIdx)
             .arg(runInfo.runMsg)
             .arg(runInfo.runElapsed);
    tab->setToolTip(tip);

}
///静态工具内联函数:算子更新XItem的ToolTip
inline static void updateFuncToolTip(XFlowGraphicsItem* xItem, XvFunc* func)
{
    if(!xItem||!func)
    {
        return;
    }
    static QMap<EXvFuncRunStatus,QString> map=XvCoreHelper::getXvFuncRunStatusLang();
    static QString strFuncId=getLang(App_UiXvWorkMgr_FuncId,"算子ID");
    static QString strRole=getLang(App_UiXvWorkMgr_FuncRole,"算子标识符");
    static QString strRunStatus=getLang(App_UiXvWorkMgr_FuncRunStatus,"运行结果");
    static QString strRunMsg=getLang(App_UiXvWorkMgr_FuncRunMsg,"运行信息");
    static QString strRunElapsed=getLang(App_UiXvWorkMgr_FuncRunElapsed,"运行耗时");

    auto runInfo=func->getXvFuncRunInfo();
    QString tip;
    tip=QString("Item-Id:%1\r\n"+
                strFuncId+":%2\r\n"+
                strRole+":%3\r\n"+
                strRunStatus+":%4\r\n"+
                strRunMsg+":%5\r\n"+
                strRunElapsed+":%6ms")
            .arg(xItem->itemId())
            .arg(func->funcId())
            .arg(func->funcRole())
            .arg(map[runInfo.runStatus])
            .arg(runInfo.runMsg)
            .arg(runInfo.runElapsed);
    xItem->setTip(tip);
}

/**************************************************************/
//* [UiXvWorkManagerPrivate]
/**************************************************************/
class UiXvWorkManagerPrivate
{
    Q_DISABLE_COPY(UiXvWorkManagerPrivate)
    Q_DECLARE_PUBLIC(UiXvWorkManager)

public:
    UiXvWorkManagerPrivate(UiXvWorkManager *q):q_ptr(q)
    {

    };
    ~UiXvWorkManagerPrivate(){};

public:
    UiXvWorkManager              *const q_ptr;


};


/**************************************************************/
//* [UiXvWorkManager]
/**************************************************************/

UiXvWorkManager::UiXvWorkManager(QObject *parent)
    :QObject{parent},d_ptr(new UiXvWorkManagerPrivate(this))
{
    init();
}

UiXvWorkManager::~UiXvWorkManager()
{

}


/*********[初始化接口]*********/

void UiXvWorkManager::init()
{
    initDock();
    initToolBtn();
    initStatusBar();
}

void UiXvWorkManager::initDock()
{
    auto funcCreateDock=[&]()
    {
        ads::CDockWidget* dock = new ads::CDockWidget("NoFlow");
        dock->layout()->setContentsMargins(0,0,0,0);
        dock->layout()->setSpacing(0);
        dock->setProperty(FlowId,"");
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
}

void UiXvWorkManager::initToolBtn()
{
    auto bar= m_dockFlowArea->titleBar();
    auto btnSize=bar->height();
    auto iconSize=btnSize-2;

    auto btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowConfig");
    U_initSetButton(btn,getLang(App_UiXvWorkMgr_FlowConfig,"流程配置"),getLang(App_UiXvWorkMgr_FlowConfig,"流程配置"),
                    QIcon(":/images/Ui/UiXvWorkManagerFlowConfig.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,&UiXvWorkManager::flowShowConfig);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowOnceRun");
    U_initSetButton(btn,getLang(App_UiXvWorkMgr_FlowOnceRun,"流程单次运行"),getLang(App_UiXvWorkMgr_FlowOnceRun,"流程单次运行"),
                    QIcon(":/images/Ui/UiXvWorkManagerFlowOnceRun.svg"),iconSize,
                     QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,&UiXvWorkManager::flowOnceRun);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowLoopRun");
    U_initSetButton(btn,getLang(App_UiXvWorkMgr_FlowLoopRun,"流程重复运行"),getLang(App_UiXvWorkMgr_FlowLoopRun,"流程重复运行"),
                    QIcon(":/images/Ui/UiXvWorkManagerFlowLoopRun.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,&UiXvWorkManager::flowLoopRun);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowStop");
    U_initSetButton(btn,getLang(App_UiXvWorkMgr_FlowStop,"流程停止运行"),getLang(App_UiXvWorkMgr_FlowStop,"流程停止运行"),
                    QIcon(":/images/Ui/UiXvWorkManagerFlowStop.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    btn->setRippleColor(Qt::red);
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,&UiXvWorkManager::flowStopRun);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowDel");
    U_initSetButton(btn,getLang(App_UiXvWorkMgr_FlowDel,"流程删除"),getLang(App_UiXvWorkMgr_FlowDel,"流程删除"),
                    QIcon(":/images/Ui/UiXvWorkManagerFlowDel.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,&UiXvWorkManager::flowRemove);

    btn=new XMatToolButton(bar);
    btn->setObjectName("btnFlowAdd");
    U_initSetButton(btn,getLang(App_UiXvWorkMgr_FlowAdd,"流程添加"),getLang(App_UiXvWorkMgr_FlowAdd,"流程添加"),
                    QIcon(":/images/Ui/UiXvWorkManagerFlowAdd.svg"),iconSize,
                    QSize(btnSize,btnSize), QSize(btnSize,btnSize)
                    );
    bar->insertWidget(-1, btn);
    connect(btn,&XMatToolButton::clicked,this,&UiXvWorkManager::flowAdd);
}

void UiXvWorkManager::initStatusBar()
{
    ///初始化Flow状态栏
    m_flowStatusBar=new QStatusBar();
    m_flowStatusBar->setObjectName("flowStatusBar");
    m_flowStatusBar->setMinimumHeight(25);
    ///添加滑动条
    auto wdgSlider=new QWidget(m_flowStatusBar);
    auto hLayoutSlider=new QHBoxLayout(wdgSlider);
    hLayoutSlider->setContentsMargins(0,0,0,0);
    auto lb=new XMatLabel(m_flowStatusBar);
    lb->setText(getLang(App_UiXvWorkMgr_FlowViewZoomScale,"缩放比例")+":");
    m_flowViewZoomSlider=new XMatSlider(m_flowStatusBar);
    m_flowViewZoomSlider->setObjectName("flowViewSlider");
    m_flowViewZoomSlider->setMinimumSize(100,25);
    m_flowViewZoomSlider->setMaximumHeight(25);
    m_flowViewZoomSlider->setPageStep(100);
    hLayoutSlider->addWidget(lb);
    hLayoutSlider->addWidget(m_flowViewZoomSlider);
      wdgSlider->setLayout(hLayoutSlider);
    m_flowStatusBar->addWidget(wdgSlider);

    connect(m_dockFlowArea,&CDockAreaWidget::currentChanged,this,[=]()
    {
        onFlowViewZoomSliderUpdate();
    });
    connect(m_flowViewZoomSlider,&XMatSlider::valueChanged,this,[=]()
    {
        auto scene=getCurDockFlowScene();
        if(scene)
        {
            auto view=scene->getView();
            if(view)
            {
              auto curVal=m_flowViewZoomSlider->value();
              auto oldVal=view->zoomScale()*100;
              if(curVal<=oldVal)
              {
                 view->zoomDown();
              }
              else
              {
                 view->zoomUp();
              }

            }
        }
    });


}


/*********[公共接口]*********/

XFlowGraphicsScene *UiXvWorkManager::getFlowScene(const QString &flowId)
{
    if(m_mapFlowScene.contains(flowId))
    {
        return m_mapFlowScene[flowId];
    }
    return nullptr;
}


XFlowGraphicsScene *UiXvWorkManager::createFlowScene(XvFlow *flow)
{
    if(flow==nullptr) return nullptr;

    if(m_mapFlowScene.contains(flow->flowId()))
    {
        return m_mapFlowScene[flow->flowId()];
    }

    auto funcCreateDock=[&](XFlowGraphicsView* view,XvFlow *flow)
    {
        ads::CDockWidget* dock = new ads::CDockWidget("dock_"+flow->flowId());
        dock->layout()->setContentsMargins(0,0,0,0);
        dock->layout()->setSpacing(0);
        dock->setWidget(view);
        dock->setProperty(FlowId,flow->flowId());
        view->setParent(dock);
        dock->setWindowTitle(flow->flowName());
        dock->setFeature(ads::CDockWidget::DockWidgetClosable,false);
        dock->setFeature(ads::CDockWidget::DockWidgetFloatable,false);
        dock->setFeature(ads::CDockWidget::DockWidgetMovable,false);
        dock->tabWidget()->setToolTip(flow->flowName());
        dock->tabWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(dock->tabWidget(),&ads::CDockWidget::customContextMenuRequested,this,&UiXvWorkManager::onFlowDockTabMenuRequested);
        updateFlowToolTip(dock->tabWidget(),flow);
        return dock;
    };

    if(flow->flowId().isEmpty()) return nullptr;
    auto scene = new XFlowGraphicsScene();
    scene->setObjectName("scene_"+flow->flowId());
    scene->setDisplayRect(0,0,4000,4000);
    scene->getView()->centerOn(0,0);
    scene->getView()->zoomToRect(QRectF(0,0,500,500));
    scene->setXItemDelegateFactory(new XvGraphicsItemFactory(scene));
    scene->setXLinkDelegateFactory(new XvGraphicsLinkFactory(scene));
    scene->setSceneTag(flow->flowId());
    scene->setSceneQPtrTag(flow);
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
    auto dockNew=funcCreateDock(scene->getView(),flow);
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
            scene->getView()->setParent(dock);
            dock->setProperty(FlowId,flow->flowId());
            dock->setWindowTitle(flow->flowName());
            dock->setFeature(ads::CDockWidget::DockWidgetClosable,false);
            dock->setFeature(ads::CDockWidget::DockWidgetFloatable,false);
            dock->setFeature(ads::CDockWidget::DockWidgetMovable,false);
            dock->tabWidget()->setToolTip(flow->flowName());
            dock->tabWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(dock->tabWidget(),&ads::CDockWidget::customContextMenuRequested,this,&UiXvWorkManager::onFlowDockTabMenuRequested);
            updateFlowToolTip(dock->tabWidget(),flow);
        }
        else
        {
            auto dockNew=funcCreateDock(scene->getView(),flow);
            m_dockFlowManager->addDockWidget(ads::DockWidgetArea::CenterDockWidgetArea, dockNew,m_dockFlowArea);      
        }

    }
    m_mapFlowScene.insert(flow->flowId(),scene);
    initFlowScene(flow,scene);
    onFlowViewZoomSliderUpdate();
    return scene;
}

bool UiXvWorkManager::removeFlowScene(XvFlow *flow)
{
    if(m_mapFlowScene.contains(flow->flowId()))
    {
       auto docks= m_dockFlowArea->dockWidgets();
       foreach (auto dock, docks)
       {
           if(!dock) continue;
           auto varId= dock->property(FlowId);
           if(varId.isValid())
           {
               auto id=varId.toString();
               if(id==flow->flowId())
               {
                   auto scene= m_mapFlowScene[flow->flowId()];
                   m_mapFlowScene.remove(flow->flowId());
                   if(scene==nullptr)
                   {
                       break;
                   }
                   disconnect(dock->tabWidget(),&ads::CDockWidget::customContextMenuRequested,this,&UiXvWorkManager::onFlowDockTabMenuRequested);
                   dock->closeDockWidget();
                   dock->deleteDockWidget();
                   uninitFlowScene(flow,scene);
                   scene->deleteLater();
                  return true;
               }

           }
       }
    }
    return false;
}

bool UiXvWorkManager::addXItemByFuncRole(const QString &role, const QString &flowId, const QPointF &pos)
{
    auto scene=getFlowScene(flowId);
    if(!scene) return false;
    auto factory=scene->xItemDelegateFactory();
    if(!factory) return false;
    auto xItem=factory->getXFlowGraphicsItem(role);
    if(!xItem) return false;
    xItem->item()->setPos(pos);
    scene->addXItem(xItem);
    return true;
}

bool UiXvWorkManager::removeXItemByFuncId(const QString &funcId, const QString &flowId)
{
    auto scene=getFlowScene(flowId);
    if(!scene) return false;
    auto xItems= scene->getXItems();
    foreach (auto xItem, xItems)
    {
        auto xItemFuncId=xItem->itemTag().toString();
        if(xItemFuncId==funcId)
        {
           return scene->removeXItem(xItem);
        }
    }
    return false;
}


/*********[内部工具接口]*********/

void UiXvWorkManager::initFlowScene(XvFlow *flow,XFlowGraphicsScene *scene)
{
    if(!flow||!scene) return;
    /*场景*/
    //常规
    connect(scene,&XFlowGraphicsScene::sceneContextMenuRequested,this,&UiXvWorkManager::onFlowSceneMenuRequested);
    connect(scene,&XFlowGraphicsScene::mouseClicked,this,&UiXvWorkManager::onFlowSceneMouseClicked);
    connect(scene,&XFlowGraphicsScene::xItemSingleSelect,this,&UiXvWorkManager::onFlowSceneXItemSingleSelect);
    connect(scene,&XFlowGraphicsScene::xLinkSingleSelect,this,&UiXvWorkManager::onFlowSceneXLinkSingleSelect);
    connect(scene,&XFlowGraphicsScene::mouseDoubleClickXItem,this,&UiXvWorkManager::onFlowSceneMouseDoubleClickXItem);
    connect(scene->getView(),&XFlowGraphicsView::sgWheelEvent,this,&UiXvWorkManager::onFlowViewZoomSliderUpdate);
    //算子
    connect(scene,&XFlowGraphicsScene::xItemAdd,this,&UiXvWorkManager::onFlowSceneXItemAdd);
    connect(scene,&XFlowGraphicsScene::xItemRemoveStart,this,&UiXvWorkManager::onFlowSceneXItemRemoveStart);
    connect(scene,&XFlowGraphicsScene::judgeCantConnectXItem,this,&UiXvWorkManager::onFlowSceneXItemConnectJudge);
    connect(scene,&XFlowGraphicsScene::xLinkRemove,this,&UiXvWorkManager::onFlowSceneConnectRemove);
    /*流程*/
    connect(flow,&XvFlow::sgFlowNameChanged,this,&UiXvWorkManager::onFlowNameChanged);
    connect(flow,&XvFlow::sgFlowRunStart,this,&UiXvWorkManager::onFlowRunStart);
    connect(flow,&XvFlow::sgFlowRunEnd,this,&UiXvWorkManager::onFlowRunEnd);
    connect(flow,&XvFlow::sgFlowRunStop,this,&UiXvWorkManager::onFlowRunStop);
}

void UiXvWorkManager::uninitFlowScene(XvFlow *flow,XFlowGraphicsScene *scene)
{
    if(!flow||!scene) return;
    /*场景*/
    //常规
    disconnect(scene,&XFlowGraphicsScene::sceneContextMenuRequested,this,&UiXvWorkManager::onFlowSceneMenuRequested);
    disconnect(scene,&XFlowGraphicsScene::mouseClicked,this,&UiXvWorkManager::onFlowSceneMouseClicked);
    disconnect(scene,&XFlowGraphicsScene::xItemSingleSelect,this,&UiXvWorkManager::onFlowSceneXItemSingleSelect);
    disconnect(scene,&XFlowGraphicsScene::xLinkSingleSelect,this,&UiXvWorkManager::onFlowSceneXLinkSingleSelect);
    disconnect(scene,&XFlowGraphicsScene::mouseDoubleClickXItem,this,&UiXvWorkManager::onFlowSceneMouseDoubleClickXItem);
    disconnect(scene->getView(),&XFlowGraphicsView::sgWheelEvent,this,&UiXvWorkManager::onFlowViewZoomSliderUpdate);
     //算子
    disconnect(scene,&XFlowGraphicsScene::xItemAdd,this,&UiXvWorkManager::onFlowSceneXItemAdd);
    connect(scene,&XFlowGraphicsScene::xItemRemoveStart,this,&UiXvWorkManager::onFlowSceneXItemRemoveStart);

    /*流程*/
    disconnect(flow,&XvFlow::sgFlowNameChanged,this,&UiXvWorkManager::onFlowNameChanged);
    disconnect(flow,&XvFlow::sgFlowRunStart,this,&UiXvWorkManager::onFlowRunStart);
    disconnect(flow,&XvFlow::sgFlowRunEnd,this,&UiXvWorkManager::onFlowRunEnd);
    disconnect(flow,&XvFlow::sgFlowRunStop,this,&UiXvWorkManager::onFlowRunStop);
}

void UiXvWorkManager::initFuncXItem(XvFunc *func, XFlowGraphicsItem *xItem)
{
    if(!func||!xItem) return;

    //算子
    connect(func,&XvFunc::sgFuncRunStart,this,[=]()
    {
        xItem->setHighLight(true);
        xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Running_Str);

    });

    connect(func,&XvFunc::sgFuncRunEnd,this,[=]()
    {      
        updateFuncToolTip(xItem,func);
        xItem->setHighLight(false);
        auto runInfo=func->getXvFuncRunInfo();
        switch (runInfo.runStatus)
        {
        case EXvFuncRunStatus::Init:
            xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Init_Str);
            break;
        case EXvFuncRunStatus::Running:
            xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Running_Str);
            break;
        case EXvFuncRunStatus::Ok:
            xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Ok_Str);
            break;
        case EXvFuncRunStatus::Fail:
        {
            xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Fail_Str);
            QString str=QString("%1.%2:%3").arg(func->parFlow()->flowName()).arg(func->funcName()).arg(func->getXvFuncRunMsg());
            Log_Warn(str);
        }
            break;
        case EXvFuncRunStatus::Error:
        {
            xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Error_Str);
            QString str=QString("%1.%2:%3").arg(func->parFlow()->flowName()).arg(func->funcName()).arg(func->getXvFuncRunMsg());
            Log_Error(str);
        }
            break;
        }


    });
}

void UiXvWorkManager::uninitFuncXItem(XvFunc *func, XFlowGraphicsItem *xItem)
{
   if(!func||!xItem) return;
}

bool UiXvWorkManager::getCurDockFlowId(QString &id)
{
    auto dock= m_dockFlowArea->currentDockWidget();
    if(!dock) return false;
    auto varId= dock->property(FlowId);
    if(varId.isValid())
    {
        id=varId.toString();
        return true;
    }
    else
    {
        return false;
    }
}

XvFlow *UiXvWorkManager::getCurDockFlow()
{
    QString flowId;
    bool bRet= getCurDockFlowId(flowId);
    if(!bRet) return nullptr;
    auto flow=XvWorkMgr->getXvFlow(flowId);
    return flow;
}

XFlowGraphicsScene *UiXvWorkManager::getCurDockFlowScene()
{
    QString flowId;
    bool bRet= getCurDockFlowId(flowId);
    if(!bRet) return nullptr;
    return getFlowScene(flowId);
}


/*********[DockTitleBar-按钮右键菜单-响应槽函数(流程相关)]*********/
 //*[流程界面操作]*
///功能:Dock标题右键菜单
void UiXvWorkManager::onFlowDockTabMenuRequested(const QPoint &pos)
{
    auto objDockTab=sender();
    if(objDockTab==nullptr) return;
    auto dockTab=qobject_cast<CDockWidgetTab*>(objDockTab);
    if(dockTab==nullptr) return;
    if(dockTab->dockWidget()!=m_dockFlowArea->currentDockWidget()) return;


    QMenu menu(dockTab);
    auto action=menu.addAction(getLang(App_UiXvWorkMgr_FlowRename,"流程重命名"),this,SLOT(flowRename()));
    action=menu.addAction(getLang(App_UiXvWorkMgr_FlowDel,"流程删除"),this,SLOT(flowRemove()));
    action=menu.addAction(getLang(App_UiXvWorkMgr_FlowConfig,"流程配置"),this,SLOT(flowShowConfig()));
    menu.exec(QCursor::pos());
}

//*[流程常规操作]*
void UiXvWorkManager::flowAdd()
{
    auto flowName= XInputDialog::getText(getLang(App_UiXvWorkMgr_FlowAdd,"流程添加"),getLang(App_UiXvWorkMgr_FlowName,"流程名")+":"
                                         ,getLang(App_UiCommon_Confirm,"确定"),getLang(App_UiCommon_Cancel,"取消"));
    if(!flowName.isEmpty())
    {
        XvWorkMgr->createXvFlow(flowName);
    }
}
void UiXvWorkManager::flowRemove()
{
    auto flow=getCurDockFlow();
    if(flow)
    {
        auto ret= XMessageBox::question(getLang(App_UiXvWorkMgr_FlowDel,"流程删除"),getLang(App_UiXvWorkMgr_FlowIsDel,"是否删除流程")+":"+flow->flowName(),nullptr,
                                        U_getXMessageBoxButtonTexts({XMessageBox::StandardButton::Yes,XMessageBox::StandardButton::No}));
        if(ret==XMessageBox::Yes)
        {
            XvWorkMgr->removeXvFlow(flow->flowId());
        }

    }
}
void UiXvWorkManager::flowRename()
{
    auto flow=getCurDockFlow();
    if(flow)
    {
        auto oldName=flow->flowName();
        auto flowName= XInputDialog::getText(getLang(App_UiXvWorkMgr_FlowRename,"流程重命名"),getLang(App_UiXvWorkMgr_FlowName,"流程名")
                                             ,getLang(App_UiCommon_Confirm,"确定"),getLang(App_UiCommon_Cancel,"取消"),nullptr,QLineEdit::Normal,oldName);
        if(!flowName.isEmpty())
        {
            flow->setFlowName(flowName);
            Log_Event(getLang(App_UiXvWorkMgr_FlowRename,"流程重命名")+":"+oldName+"->"+flowName);
        }
    }
}
void UiXvWorkManager::onFlowNameChanged(XvFlow *flow)
{
    if(flow==nullptr) return;
    if(m_mapFlowScene.contains(flow->flowId()))
    {
       auto scene= m_mapFlowScene[flow->flowId()];
       if(scene&&scene->getView())
       {
          auto par= scene->getView()->parentWidget();
          if(par)
          {
            auto dock=qobject_cast<CDockWidget*>(par);
            if(dock)
            {
               dock->setWindowTitle(flow->flowName());
            }
          }

       }
    }
}
//*[流程运行操作]*
void UiXvWorkManager::flowOnceRun()
{
    QString id;
    if(getCurDockFlowId(id))
    {
        XvWorkMgr->onceRunXvFlow(id);
    }
}
void UiXvWorkManager::flowLoopRun()
{
    QString id;
    if(getCurDockFlowId(id))
    {
        XvWorkMgr->loopRunXvFlow(id);
    }
}
void UiXvWorkManager::flowStopRun()
{
    QString id;
    if(getCurDockFlowId(id))
    {
        XvWorkMgr->stopRunXvFlow(id);
    }
}
///todo 设置流程运行响应 ——xie.y 20230403
void UiXvWorkManager::onFlowRunStart()
{
    auto obj=sender();
    if(!obj) return;
    auto flow=qobject_cast<XvFlow*>(obj);
    if(!flow) return;
    Log_Event(QString(getLang(App_UiXvWorkMgr_XvFlowRunStart,"流程<%1>开始运行")).arg(flow->flowName()));
    auto scene=getFlowScene(flow->flowId());
    if(!scene) return;
    scene->setEnabled(false);
    auto xItems=scene->getXItems();
    foreach (auto xItem, xItems)
    {
        xItem->switchShowPixKey(XvFuncName,XvFuncRunStatus_Init_Str);
    }

    auto par= scene->getView()->parent();
    if(par)
    {
        auto dock=qobject_cast<ads::CDockWidget*>(par);
        if(dock)
        {
            updateFlowToolTip(dock->tabWidget(),flow);
        }
    }

}

void UiXvWorkManager::onFlowRunEnd()
{
    auto obj=sender();
    if(!obj) return;
    auto flow=qobject_cast<XvFlow*>(obj);
    if(!flow) return;
    auto info=flow->getXvFuncRunInfo();
    QString str=
            QString(getLang(App_UiXvWorkMgr_XvFlowRunEnd,"流程<%1>运行结束")).arg(flow->flowName())+":"+
            QString(getLang(App_UiXvWorkMgr_FlowRunIdx,"当前运行序号")+"<%1>").arg(info.runIdx)+" "+
            QString(getLang(App_UiXvWorkMgr_FlowRunElapsed,"运行耗时")+"%1ms").arg(info.runElapsed)+" "+
            QString(getLang(App_UiXvWorkMgr_FlowRunMsg,"运行信息")+"<%1>").arg(info.runMsg);
    switch (info.runStatus)
    {
    case XvCore::EXvFlowRunStatus::Ok:
        Log_Info(str);
        break;
    case XvCore::EXvFlowRunStatus::Fail:
        Log_Warn(str);
        break;
    case XvCore::EXvFlowRunStatus::Error:
        Log_Error(str);
        break;
   default:
         Log_Event(str);
        break;
    }

    auto scene=getFlowScene(flow->flowId());
    if(!scene) return;
    scene->setEnabled(true);
    auto par= scene->getView()->parent();
    if(par)
    {
        auto dock=qobject_cast<ads::CDockWidget*>(par);
        if(dock)
        {
            updateFlowToolTip(dock->tabWidget(),flow);
        }
    }

}

void UiXvWorkManager::onFlowRunStop()
{
    auto obj=sender();
    if(!obj) return;
    auto flow=qobject_cast<XvFlow*>(obj);
    if(!flow) return;
    Log_Event(QString(getLang(App_UiXvWorkMgr_XvFlowRunStop,"流程<%1>运行停止")).arg(flow->flowName()));
    auto scene=getFlowScene(flow->flowId());
    if(!scene) return;
    scene->setEnabled(true);
}

void UiXvWorkManager::flowShowConfig()
{
    auto flow=getCurDockFlow();
    if(!flow) return;
    FrmXvFlowConfig *frm=new FrmXvFlowConfig(flow);
    frm->show();
}


/*********[Scene信号+右键菜单-响应槽函数(算子相关)]*********/
//*[Scene常规操作]*
///xie.y todo↓
///功能:场景右键菜单
void UiXvWorkManager::onFlowSceneMenuRequested(const QPoint &pos)
{
    Q_D(const UiXvWorkManager);
    auto pt=QCursor::pos();
    auto objScene=sender();
    if(objScene==nullptr) return;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(scene==nullptr) return;
    auto item=scene->getXItemByPos(pos);
    auto link=scene->getXLinkByPos(pos);
     /*[算子区域]*/
    if(item)
    {
        QMenu menu(scene->getView());
        /*[重命名]*/
        auto action=menu.addAction(getLang(App_UiXvWorkMgr_FuncRename,"算子重命名"),this,SLOT(funcRename()));
        QVariant varPtr=QVariant::fromValue<XFlowGraphicsItem*>(item);
        action->setData(varPtr);
        /*[显示界面]*/
        action=menu.addAction(getLang(App_UiXvWorkMgr_FuncShow,"显示界面"),this,[=]()
        {
            funcShow(item);
        });
        action=menu.addAction(getLang(App_UiXvWorkMgr_FuncRun,"运行算子"),this,[=]()
        {
            funcRun(item);
        });
        action=menu.addAction("测试",this,[=]()//XIE.Y TEST
        {
            if(!item) return;
            auto qPtr=  item->itemQPtrTag();
            if(!qPtr) return;
            auto func=qobject_cast<XvFunc*>(qPtr);
            if(!func) return;

            auto selItems=scene->getSelectXItem();
            if(selItems.count()==0)
            {
                return;
            }
            auto selItem=selItems[0];
            qPtr=  selItem->itemQPtrTag();
            if(!qPtr) return;
            auto funcSel=qobject_cast<XvFunc*>(qPtr);
            if(!funcSel) return;
            qDebug()<<"选择的算子是否存在后代为当前所指的算子:"<<funcSel->existDescendantFunc(func);
            qDebug()<<"当前所指的算子是否存在祖先为选择的算子:"<<func->existAncestorFunc(funcSel);
        });

        menu.exec(pt);
    }
    /*[连线区域]*/
    if(link)
    {
     //xie.y todo
        QMenu menu(scene->getView());
        /*[删除连线]*/
        auto action=menu.addAction(getLang(App_UiXvWorkMgr_FuncLinkDel,"删除连线"),this,[&]()
        {
            scene->removeXLink(link);
        }
        );
        menu.exec(pt);
    }
    /*[空白区域]*/
    if(!item&&!link)
    {
        QMenu menu(scene->getView());
        /*[缩放]*/
        auto action=menu.addAction(getLang(App_UiXvWorkMgr_SceneZoomToFit,"缩放到合适范围"),this,[&]()
        {
            scene->zoomToItemRect();
            onFlowViewZoomSliderUpdate();
        }
        );
        action=menu.addAction(getLang(App_UiXvWorkMgr_FlowOnceRun,"流程单次运行"),this,[&]()
        {
            flowOnceRun();
        }
        );
        action=menu.addAction(getLang(App_UiXvWorkMgr_FlowLoopRun,"流程重复运行"),this,[&]()
        {
            flowLoopRun();
        }
        );
        /*[添加算子]*/
        auto addMenu=menu.addMenu(getLang(App_UiXvWorkMgr_SceneAddXvFunc,"添加算子"));
        auto xvFuncAsm=XvWorkMgr->getXvCoreMgr()->getXvFuncAsm();
        auto lstTInfo=xvFuncAsm->getXvFuncTypeInfos();
        foreach (auto tInfo, lstTInfo)
        {
           if(tInfo.type==EXvFuncType::Null)
           {
               continue;
           }
           auto lstFInfo=xvFuncAsm->getXvFuncInfos(tInfo.type);
           if(lstFInfo.count()==0)
           {
               continue;
           }
           auto menu= addMenu->addMenu(tInfo.icon,tInfo.name);
           foreach (auto fInfo, lstFInfo)
           {
               menu->addAction(fInfo.icon,fInfo.name,this,[=]()
               {
                   auto role= fInfo.role;
                   auto factory= scene->xItemDelegateFactory();
                   if(factory)
                   {
                     auto xItem= factory->getXFlowGraphicsItem(role);
                     if(xItem)
                     {
                         xItem->item()->setPos(pos);
                         scene->addXItem(xItem);
                     }

                   }
               });
           }
        }
        menu.exec(pt);
    }
}
///功能:单击重置高亮
/// 发送单击XvFunc信号
void UiXvWorkManager::onFlowSceneMouseClicked(QGraphicsSceneMouseEvent *event)
{
    auto objScene=sender();
    if(objScene==nullptr) return;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(scene==nullptr) return;
    if(event->button()==Qt::LeftButton)
    {
     foreach (auto link, scene->getXLinks())
     {
         if(link)
         link->setHighLight(false,false);
     }
     foreach (auto item, scene->getXItems())
     {
         if(item)
         item->setHighLight(false,false);
     }
    }
    if(event->button()==Qt::LeftButton)
    {
        auto item=scene->getXItemByPos(event->scenePos());
        if(!item)
        {
            emit this->sgFlowSceneMouseClickWithXvFunc(nullptr);
        }
        else
        {
            auto qPtr=  item->itemQPtrTag();
            if(!qPtr) return;
            auto func=qobject_cast<XvFunc*>(qPtr);
            emit this->sgFlowSceneMouseClickWithXvFunc(func);
        }

    }
}
///功能:单击XItem时显示连接的XItems
void UiXvWorkManager::onFlowSceneXItemSingleSelect(XFlowGraphicsItem *item)
{
    auto objScene=sender();
    if(objScene==nullptr) return;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(scene==nullptr) return;
    if(item)
    {
      auto sons=  item->getSonConnectLinks();
      auto fathers=item->getFatherConnectLinks();
      foreach (auto son,sons)
      {
          auto linkPen= son->highLightPen();
          linkPen.setColor(QColor(255,255,0));
          son->setHighLightPen(linkPen);


          auto pen=son->sonXItem()->highLightPen();
          pen.setColor(QColor(255,255,0));
          son->sonXItem()->setHighLightPen(pen);

          son->setHighLight(true,false);
          son->sonXItem()->setHighLight(true,false);
      }
      foreach (auto father,fathers)
      {
          auto linkPen= father->highLightPen();
          linkPen.setColor(QColor(255,128,64));
         father->setHighLightPen(linkPen);

          auto pen=father->fatherXItem()->highLightPen();
          pen.setColor(QColor(255,255,0));
          father->fatherXItem()->setHighLightPen(pen);

          father->setHighLight(true,false);
          father->fatherXItem()->setHighLight(true,false);
      }

      scene->getView()->viewport()->update();

    }
}
///功能:双击时显示算子界面
void UiXvWorkManager::onFlowSceneMouseDoubleClickXItem(XFlowGraphicsItem *item)
{
    funcShow(item);
}
///功能:单击XLink时显示连接的XItems
void UiXvWorkManager::onFlowSceneXLinkSingleSelect(XFlowGraphicsConnectLink *link)
{
    auto objScene=sender();
    if(objScene==nullptr) return;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(scene==nullptr) return;
    if(link)
    {
        link->sonXItem()->setHighLight(true);
        link->fatherXItem()->setHighLight(true);
    }
}

void UiXvWorkManager::onFlowSceneXItemAdd(XFlowGraphicsItem *xItem)
{
    auto objScene=sender();
    if(!objScene) return;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(!scene) return;
    auto objFlow= scene->sceneQPtrTag();
    if(!objFlow) return;
    auto flow=qobject_cast<XvFlow*>(objFlow);
    if(!flow) return;

    QString role=xItem->itemType();
    auto func=flow->createXvFunc(role);
    if(!func)
    {
        scene->removeXItem(xItem);
        Log_Warn(flow->lastErrorMsg());
        return;
    }
    func->setFuncName(xItem->text());
    xItem->setItemTag(func->funcId());//设置XItem的Tag为算子ID
    xItem->setItemQPtrTag(func);//设置XItem的QPtrTag为算子指针
    updateFuncToolTip(xItem,func);
    initFuncXItem(func,xItem);
}

bool UiXvWorkManager::onFlowSceneXItemRemoveStart(XFlowGraphicsItem *xItem)
{
    auto objScene=sender();
    if(!objScene) return false;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(!scene) return false;
    auto objFlow= scene->sceneQPtrTag();
    if(!objFlow) return false;
    auto flow=qobject_cast<XvFlow*>(objFlow);
    if(!flow) return false;
    auto id= xItem->itemTag().toString();
    auto func= flow->getXvFunc(id);
    auto bRet= flow->removeXvFunc(id);//删除成功返回置反的removeXvFunc结果
    if(bRet)
    {
        uninitFuncXItem(func,xItem);
    }
    else
    {
        Log_Warn(flow->lastErrorMsg());
    }
    return !bRet;
}

bool UiXvWorkManager::onFlowSceneXItemConnectJudge(XFlowGraphicsItem *fatherXItem, const QString &startKey, XFlowGraphicsItem *sonXItem, const QString &sonKey)
{
    auto objScene=sender();
    if(!objScene) return true;
    auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
    if(!scene) return true;
    auto objFlow= scene->sceneQPtrTag();
    if(!objFlow) return true;
    auto flow=qobject_cast<XvFlow*>(objFlow);
    if(!flow) return true;

    auto fatherId= fatherXItem->itemTag().toString();
    auto sonId= sonXItem->itemTag().toString();
    auto fatherFunc= flow->getXvFunc(fatherId);
    auto sonFunc= flow->getXvFunc(sonId);
    if(!fatherFunc||!sonFunc) return true;
    if(fatherFunc->existSonFunc(sonFunc))//已经存在连接
    {
        auto sons= fatherXItem->getSonConnectLinks();
        foreach (auto son, sons)
        {
            if(son->fatherXItem()==fatherXItem&&son->sonXItem()==sonXItem)//修改旧连接线
            {
                son->setFatherKey(startKey);
                son->setSonKey(sonKey);
                break;
            }
        }
        return true;//不可再连接
    }
    if(fatherFunc==sonFunc) //同一个算子判断是否可以自连
    {
        if(!fatherFunc->canConnectSelf())
        {
            return true;
        }
    }
    if(fatherFunc->addSonFunc(sonFunc))
    {
       if(sonFunc->existFatherFunc(fatherFunc))
       {
           return false;
       }
       else
       {
           fatherFunc->delSonFunc(sonFunc);
           return true;
       }
    }
    return false;
}


void UiXvWorkManager::onFlowSceneConnectRemove(XFlowGraphicsConnectLink *xLink)
{
    if(xLink&&xLink->fatherXItem()&&xLink->sonXItem())
    {
        auto objScene=sender();
        if(!objScene) return;
        auto scene=qobject_cast<XFlowGraphicsScene*>(objScene);
        if(!scene) return;
        auto objFlow= scene->sceneQPtrTag();
        if(!objFlow) return;
        auto flow=qobject_cast<XvFlow*>(objFlow);
        if(!flow) return;

        auto fatherXItem=xLink->fatherXItem();
        auto sonXItem=xLink->sonXItem();
        auto fatherId= fatherXItem->itemTag().toString();
        auto sonId= sonXItem->itemTag().toString();
        auto fatherFunc= flow->getXvFunc(fatherId);
        auto sonFunc= flow->getXvFunc(sonId);
        if(!fatherFunc||!sonFunc) return;
        fatherFunc->delSonFunc(sonFunc);
        if(sonFunc->existFatherFunc(fatherFunc))
        {
            sonFunc->delFatherFunc(fatherFunc);
        }
    }
}

//*[算子操作]*
void UiXvWorkManager::funcShow(XFlowGraphicsItem* item)
{
    if(!item) return;
    auto qPtr=  item->itemQPtrTag();
    if(!qPtr) return;
    auto func=qobject_cast<XvFunc*>(qPtr);
    if(!func) return;
    func->onShowFunc();
}

void UiXvWorkManager::funcRun(XFlowGraphicsItem *item)
{
    if(!item) return;
    auto qPtr=  item->itemQPtrTag();
    if(!qPtr) return;
    auto func=qobject_cast<XvFunc*>(qPtr);
    if(!func) return;
    func->runXvFunc();
}

void UiXvWorkManager::funcRename()
{
    auto objAct=sender();
    if(!objAct) return;
    auto act=qobject_cast<QAction*>(objAct);
    if(!act) return;
    auto var=act->data();
    if(!var.isValid()) return;
    auto xItem=  var.value<XFlowGraphicsItem*>();
    if(!xItem) return;
    auto qPtr=  xItem->itemQPtrTag();
    if(!qPtr) return;
    auto func=qobject_cast<XvFunc*>(qPtr);
    if(!func) return;
    if(!xItem->parScene()) return;
    if(!xItem->parScene()->getView()) return;



    QRectF rect=xItem->textRect();
    if(!xItem->item()) return;
    auto sRect=xItem->item()->mapRectToScene(rect);
    auto vTLPos=  xItem->parScene()->getView()->mapFromScene(sRect.topLeft());
    auto vBRPos=xItem->parScene()->getView()->mapFromScene(sRect.bottomRight());
    QRectF itemRect = QRectF(vTLPos, vBRPos);

    auto textEdit=new XFlowGraphicsTextEdit(xItem->parScene()->getView());
    textEdit->setXItem(xItem);
    textEdit->setFixedSize(itemRect.width(), itemRect.height());
    textEdit->setFont(xItem->textFont());
    textEdit->setText(xItem->text());
    textEdit->move(itemRect.topLeft().toPoint());
    textEdit->setFocus();
    textEdit->show();
    xItem->parScene()->getView()->setZoomAble(false);
    connect(textEdit,&XFlowGraphicsTextEdit::focusOut,this,[=](){

        if(textEdit->xItem())
        {
            auto str=textEdit->toPlainText();
            textEdit->xItem()->setText(str);
            func->setFuncName(str);
        }
        xItem->parScene()->getView()->setZoomAble(true);
        textEdit->hide();
        textEdit->deleteLater();
    });


}



/*-----Scene/View/Flow信号:流程/流程UI状态更新(m_flowStatusBar区域相关)-----*/

void UiXvWorkManager::onFlowViewZoomSliderUpdate()
{
    auto scene=getCurDockFlowScene();
    if(scene)
    {
        auto view=scene->getView();
        if(view)
        {
          auto max=view->zoomMaxScaleSize()/view->zoomOriginalScaleSize()*100;
          auto min=view->zoomMinScaleSize()/view->zoomOriginalScaleSize()*100;
          auto val=view->zoomScale()*100;
          m_flowViewZoomSlider->setRange(min,max);
          m_flowViewZoomSlider->setValue(val);
        }
    }
}
