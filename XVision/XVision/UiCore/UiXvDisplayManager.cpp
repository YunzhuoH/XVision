#include "UiXvDisplayManager.h"

//Qt
#include <QLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QVBoxLayout>

//XvDisplay
#include <XvDisplay>

//XWidget
#include "XMatToolBar.h"
#include "XMatVLine.h"
#include "XMatToolButton.h"
#include "XMatComboBox.h"

//XVsion
#include "XvViewManager.h"
#include "UiXvWorkManager.h"
#include "UiUtils.h"


//XvData
#include <XObjectBaseType>

//XvCore
#include "XvFuncAssembly.h"
#include "XvFunc.h"
#include "XvFlow.h"
#include "XvProject.h"
#include "XvCoreDef.h"
#include "XvCoreHelper.h"

using namespace XvCore;

/**************************************************************/
//* [UiXvDisplayManagerPrivate]
/**************************************************************/
class UiXvDisplayManagerPrivate
{
    Q_DISABLE_COPY(UiXvDisplayManagerPrivate)
    Q_DECLARE_PUBLIC(UiXvDisplayManager)

public:
    UiXvDisplayManagerPrivate(UiXvDisplayManager *q):q_ptr(q)
    {

    };
    ~UiXvDisplayManagerPrivate(){};

public:
    UiXvDisplayManager              *const q_ptr;


};

/**************************************************************/
//* [UiXvDisplayManager]
/**************************************************************/
UiXvDisplayManager::UiXvDisplayManager(QObject *parent)
    :QObject{parent},d_ptr(new UiXvDisplayManagerPrivate(this))
{
    init();
}

UiXvDisplayManager::~UiXvDisplayManager()
{

}

void UiXvDisplayManager::init()
{
   initView();
   initToolBar();
   initConnect();
}

void UiXvDisplayManager::initView()
{
    m_displayView=new XvDisplayView();
    m_displayView->setBackgroundPixmapSize(64);
    m_displayView->setSceneRect(-DisplayViewSceneSize/2,-DisplayViewSceneSize/2,DisplayViewSceneSize,DisplayViewSceneSize);
    m_displayView->setMinZoomCoeff(ViewMinZoomCoeff_Default*10);
    m_displayView->setMaxZoomCoeff(ViewMaxZoomCoeff_Default*5);

    auto lyView=new QVBoxLayout(m_displayView);
    lyView->setContentsMargins(0,0,0,0);
    lyView->setSpacing(0);

    auto topWdg=new QWidget(m_displayView);
    topWdg->setFixedHeight(30);
    auto hLy=new QHBoxLayout(topWdg);
    hLy->setSpacing(10);
    hLy->setContentsMargins(0,0,0,0);
    auto lbGrayValue=new QLabel(m_displayView);//显示灰度值
    lbGrayValue->setStyleSheet("color:rgb(0,255,0); background-color:rgba(100,100,100,155); font-size: 17px;font-weight: 200px;");
    lbGrayValue->setFixedHeight(30);
    lbGrayValue->setAlignment(Qt::AlignCenter);
    lbGrayValue->setText("");
    hLy->addWidget(lbGrayValue);
    hLy->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding,QSizePolicy::Minimum));


    auto downWdg=new QWidget(m_displayView);
    downWdg->setFixedHeight(30);
    hLy=new QHBoxLayout(downWdg);
    hLy->setSpacing(10);
    hLy->setContentsMargins(0,0,0,0);
    auto  lbSizeValue=new QLabel(m_displayView);//显示尺寸大小
    lbSizeValue->setStyleSheet("color:rgb(0,255,0); background-color:rgba(100,100,100,155); font-size: 17px;font-weight: 200px;");
    lbSizeValue->setFixedHeight(30);
    lbSizeValue->setAlignment(Qt::AlignCenter);
    lbSizeValue->setText("");
    hLy->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding,QSizePolicy::Minimum));
    hLy->addWidget(lbSizeValue);

    lyView->addWidget(topWdg);
    lyView->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,QSizePolicy::Expanding));
    lyView->addWidget(downWdg);



    auto scene=m_displayView->getScene();
    auto imageItem=scene->getDisplayImageItem();
    connect(imageItem,&XvDisplayImageItem::sgHoverImagePosition,this,[=](const QPoint &pt)
    {
        int nR,nG,nB;
        imageItem->pixmap().toImage().pixelColor(pt.x(), pt.y()).getRgb(&nR,&nG,&nB);
        QString info=QString("X:%1 Y:%2 | [R:%3 G:%4 B:%5]")
                .arg(QString::number((int)pt.x()),4,' ')
                .arg(QString::number((int)pt.y()),4,' ')
                .arg(QString::number(nR),3,' ')
                .arg(QString::number(nG),3,' ')
                .arg(QString::number(nB),3,' ');
        lbGrayValue->setText(info);
    });
    connect(imageItem,&XvDisplayImageItem::sgHoverLeave,this,[=]()
    {
        lbGrayValue->setText("");
    });
    connect(scene,&XvDisplayScene::sgUpdataDisplayImage,this,[=](const QImage& img)
    {
        if(!img.isNull())
        {
            QString info=QString("[W:%1 H:%2]")
                    .arg(QString::number(img.width()),3,' ')
                    .arg(QString::number(img.height()),3,' ');
            lbSizeValue->setText(info);
        }
        else
        {
            lbSizeValue->setText("");
        }

    });
}

void UiXvDisplayManager::initToolBar()
{
    const int cstHeight=36;//固定高度
    auto btnSize=cstHeight;
    auto iconSize=btnSize-2;

    m_displayToolBar=new XMatToolBar();
    m_displayToolBar->setFixedHeight(cstHeight);
    auto ly=m_displayToolBar->layout();
    ly->setContentsMargins(5,0,5,0);
    ly->setSpacing(5);

//*[添加ComboBox]*
    m_displayComboBox=new XMatComboBox(m_displayToolBar);
    m_displayComboBox->setFixedWidth(200);
    m_displayToolBar->addWidget(m_displayComboBox);
    connect(m_displayComboBox,&QComboBox::currentIndexChanged,this,&UiXvDisplayManager::onUpdateXvFuncDisplay);
//*[添加Spacer]*
    auto wdgSpacer=new QWidget(m_displayToolBar);
    wdgSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    m_displayToolBar->addWidget(wdgSpacer);

//*[添加十字按钮]*
    auto btn=new XMatToolButton(m_displayToolBar);
    btn->setObjectName("btnSetCross");
    U_initSetButton(btn,getLang(App_UiXvDisplayManager_Cross,"显示十字"),getLang(App_UiXvDisplayManager_Cross,"显示十字"), QIcon(":/images/Ui/UiXvDisplayManagerCross.svg")
                    ,iconSize, QSize(btnSize,btnSize),QSize(btnSize,btnSize));
    m_displayToolBar->addWidget(btn);
    connect(btn,&XMatToolButton::clicked,this,[=]()
    {
        auto imageItem= m_displayView->getScene()->getDisplayImageItem();
        if(imageItem)
        {
            imageItem->setCenterCrossShow(!imageItem->centerCrossShow());
            imageItem->update();
        }
    });

//*[添加分割线]*
    auto vLine=new XMatVLine(m_displayToolBar);
    vLine->setLineWidth(1);
    m_displayToolBar->addWidget(vLine);

//*[添加放大按钮]*
    btn=new XMatToolButton(m_displayToolBar);
    btn->setObjectName("btnZoomUp");
    U_initSetButton(btn,getLang(App_UiXvDisplayManager_ZoomUp,"放大"),getLang(App_UiXvDisplayManager_ZoomUp,"放大"), QIcon(":/images/Ui/UiXvDisplayManagerZoomUp.svg")
                    ,iconSize, QSize(btnSize,btnSize),QSize(btnSize,btnSize));
    m_displayToolBar->addWidget(btn);
    connect(btn,&XMatToolButton::clicked,this,[=]()
    {
        m_displayView->zoomUp();
    });

//*[添加缩小按钮]*
    btn=new XMatToolButton(m_displayToolBar);
    btn->setObjectName("btnZoomDown");
    U_initSetButton(btn,getLang(App_UiXvDisplayManager_ZoomDown,"缩小"),getLang(App_UiXvDisplayManager_ZoomDown,"缩小"), QIcon(":/images/Ui/UiXvDisplayManagerZoomDown.svg")
                    ,iconSize, QSize(btnSize,btnSize),QSize(btnSize,btnSize));
    m_displayToolBar->addWidget(btn);
    connect(btn,&XMatToolButton::clicked,this,[=]()
    {
        m_displayView->zoomDown();
    });

    btn=new XMatToolButton(m_displayToolBar);
    btn->setObjectName("btnZoomFit");
    U_initSetButton(btn,getLang(App_UiXvDisplayManager_ZoomFit,"缩放到合适大小"),getLang(App_UiXvDisplayManager_ZoomFit,"缩放到合适大小"), QIcon(":/images/Ui/UiXvDisplayManagerZoomFit.svg")
                    ,iconSize, QSize(btnSize,btnSize),QSize(btnSize,btnSize));
    m_displayToolBar->addWidget(btn);
    connect(btn,&XMatToolButton::clicked,this,[=]()
    {
        m_displayView->zoomToDisplayFit();
    });


}

void UiXvDisplayManager::initConnect()
{
    auto uiWorkMgr=XvViewMgr->uiXvWorkManager();
    if(!uiWorkMgr)
    {
        Log_Critical("UiXvDisplayManager::initConnect:uiXvWorkManager==nullptr");
    }
    else
    {
        connect(uiWorkMgr,&UiXvWorkManager::sgFlowSceneMouseClickWithXvFunc,this,&UiXvDisplayManager::onBindXvFunc);
    }
}



XvDisplayScene *UiXvDisplayManager::displayScene() const
{
    if(!m_displayView) return nullptr;
    return m_displayView->getScene();
}

XMatToolBar *UiXvDisplayManager::displayToolBar() const
{
    return m_displayToolBar;
}


void UiXvDisplayManager::onBindXvFunc(XvFunc *func)
{
    if(!func)
    {
       return;
    }
    auto lstImage=func->getResultsByType(XImage::type());//检查有无图像结果，无图像结果不绑定
    if(lstImage.count()<1)
    {
        return;
    }
    if(m_curBindFunc)
    {
        disconnect(m_curBindFunc,&XvFunc::sgFuncRunEnd,this,&UiXvDisplayManager::onUpdateXvFuncDisplay);
    }
    m_curBindFunc=func;
    connect(m_curBindFunc,&XvFunc::sgFuncRunEnd,this,&UiXvDisplayManager::onUpdateXvFuncDisplay);
    connect(m_curBindFunc,&XvFunc::destroyed,this,[=]()
    {
        m_curBindFunc=nullptr;
        onUpdateXvFunc();
    });
    onUpdateXvFunc();
}

void UiXvDisplayManager::onUpdateXvFunc()
{
    m_displayComboBox->clear();
    m_displayView->getScene()->clearImage();
    m_displayView->getScene()->clearDisplayText();
    m_displayView->getScene()->clearRoi();
    if(!m_curBindFunc)
    {
       return;
    }

    auto lstImage=m_curBindFunc->getResultsByType(XImage::type());
    foreach (auto img, lstImage)
    {
        QString str=QString("%1.%2.%3").arg(m_curBindFunc->parFlow()->flowName()).arg(m_curBindFunc->funcName()).arg(img->dispalyName());
        m_displayComboBox->addItem(str,img->objectName());
    }
    if(m_displayComboBox->count()>0)
    {
        m_displayComboBox->setCurrentIndex(0);
    }
    onUpdateXvFuncDisplay();
}

void UiXvDisplayManager::onUpdateXvFuncDisplay()
{
    if(!m_curBindFunc)
    {
       return;
    }
    int nIdx=m_displayComboBox->currentIndex();
    if(nIdx<0)
    {
        return;
    }
    auto objName=m_displayComboBox->itemData(nIdx).toString();
    auto imgObj=m_curBindFunc->getResultsByName(objName);
    if(imgObj)
    {
        auto img=imgObj->toObject<XImage>();
        if(img)
        {
            m_displayView->getScene()->displayImage(img->value());
        }
    }

}

