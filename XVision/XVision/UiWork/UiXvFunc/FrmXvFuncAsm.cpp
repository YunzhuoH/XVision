#include "FrmXvFuncAsm.h"
#include "ui_FrmXvFuncAsm.h"
#include <QScrollBar>

#include "XvFuncAssembly.h"

#include "FrmXvFuncType.h"

#include "XvCoreManager.h"
#include "LangDef.h"


#define XvFuncType_Btn_Property "Type"///算子类型按钮属性

const static int FrmXvFuncAsm_Width=40; ///窗口固定尺寸
const static int CS_XvFuncType_Btn_Size=38;///算子类型按钮尺寸

FrmXvFuncAsm::FrmXvFuncAsm(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmXvFuncAsm)
{
    ui->setupUi(this);
    initFrm();
}

FrmXvFuncAsm::~FrmXvFuncAsm()
{
    delete ui;
}

void FrmXvFuncAsm::setDrawerParWidget(QWidget *drawerParWidget)
{
    m_drawerParWidget=drawerParWidget;
    foreach (auto drawer, m_mapXMatDrawerType)
    {
        drawer->setParent(drawerParWidget);
    }
    if(m_drawerAllTypeXvFuncs)
    {
        m_drawerAllTypeXvFuncs->setParent(m_drawerParWidget);
    }
}



bool FrmXvFuncAsm::eventFilter(QObject *watched, QEvent *event)
{
    auto type=event->type();
    if(type==QEvent::HoverMove)
    {

        auto btn=qobject_cast<QToolButton*>(watched);
        if(btn)
        {
            auto pos=  mapToParent(btn->rect().topRight());
            auto xvFuncType= btn->property(XvFuncType_Btn_Property);
            if(xvFuncType.isValid())
            {
                auto type=xvFuncType.value<XvCore::EXvFuncType>();
               if(m_drawerCurSingleTypeXvFuncs)
               {
                  if(!m_drawerCurSingleTypeXvFuncs->isCloseState())
                  {
                    onShowXvFuncTypeDrawer(btn->geometry(),type);
                  }
               }
            }
        }
    }

    return BaseWidget::eventFilter(watched,event);
}


void FrmXvFuncAsm::initFrm()
{    
    auto funcCreateFrmType=[&](QMap<XvCore::EXvFuncType,XMatDrawer*> &map,const XvCore::EXvFuncType &type)
    {
        if(map.contains(type)) return;
        auto info=XvFuncAsm->getXvFuncTypeInfo(type);
        auto lst=XvFuncAsm->getXvFuncInfos(type);
        FrmXvFuncType *frmType=new FrmXvFuncType(info,lst);     
        auto drawer=  new XMatDrawer(m_drawerParWidget);
        drawer->setClickOutsideToClose(true);
        drawer->setOverlayMode(false);
        auto layout= new QVBoxLayout();
        drawer->setDrawerLayout(layout);
        layout->addWidget(frmType);
        layout->setContentsMargins(0,0,0,0);
        drawer->setDrawerHeight(frmType->height());
        drawer->setDrawerWidth(frmType->width());
        drawer->installEventFilter(this);
        connect(frmType,&FrmXvFuncType::closeDrawer,drawer,&XMatDrawer::closeDrawer);
        map[type]=drawer;
    };

    auto funcAddBtn=[&](QVBoxLayout *layout,QWidget *parent,QIcon icon,XvCore::EXvFuncType type,QString tip="",QString text="")
    {
        auto fmH=CS_XvFuncType_Btn_Size;
        XMatToolButton* btn = new XMatToolButton(parent);
        U_initSetButton(btn,text,tip,icon,fmH-8,QSize(fmH,fmH),QSize(fmH,fmH));
        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn->setProperty(XvFuncType_Btn_Property,QVariant::fromValue(type));
        btn->installEventFilter(this);
        layout->addWidget(btn);
        connect(btn,&QToolButton::clicked,this,[&]()
        {
            auto btn=qobject_cast<QToolButton*>(sender());
            if(btn)
            {
                auto xvFuncType= btn->property(XvFuncType_Btn_Property);
                if(xvFuncType.isValid())
                {
                    auto type=xvFuncType.value<XvCore::EXvFuncType>();
                    onShowXvFuncTypeDrawer(btn->geometry(),type);
                }
            }

        });
    };



    this->setWindowTitle("FrmXvFuncAsm");
    this->setMinimumWidth(FrmXvFuncAsm_Width);
    this->setMaximumWidth(FrmXvFuncAsm_Width);
    this->setAttribute(Qt::WA_Hover);
    this->installEventFilter(this);


    ///初始化左侧算子工具栏模块
    auto scArea=ui->scAreaXvFuncAsm;
    scArea->setWidgetResizable(true);
    scArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    scArea->setLineWidth(1);
    scArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scArea->verticalScrollBar()->hide();
    scArea->verticalScrollBar()->resize(0,0);
    scArea->horizontalScrollBar()->hide();
    scArea->horizontalScrollBar()->resize(0,0);
    auto scAreaWcXvFuncAsm=ui->scAreaWcXvFuncAsm;

    ///添加算子分类按钮及算子单独类型窗口
    QVBoxLayout *vLayout = new QVBoxLayout(scAreaWcXvFuncAsm);
    vLayout->setObjectName("verticalLayout");
    vLayout->setContentsMargins(0, 5, 0, 5);
    vLayout->setSpacing(5);
    scAreaWcXvFuncAsm->setLayout(vLayout);

    auto lst=XvFuncAsm->getXvFuncTypeInfos();
    foreach (auto info, lst)
    {
        if(info.type==XvCore::EXvFuncType::Null)//NULL类型不添加
        {
            continue;
        }
        auto lstTemp=XvFuncAsm->getXvFuncInfos(info.type);
        if(lstTemp.count()==0)
        {
           // continue;//xie.y
        }
        funcAddBtn(vLayout,scAreaWcXvFuncAsm,info.icon,info.type,info.name,info.name);
        funcCreateFrmType(m_mapXMatDrawerType,info.type);
    }
    vLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum ,QSizePolicy::Expanding ));




    ///下侧按钮初始化

    auto btnShowXvFuncAsm=ui->btnShowXvFuncAsm;  
    U_initSetButton(btnShowXvFuncAsm,getLang(App_Ui_FrmXvFuncAsmExpand,"展开"),getLang(App_Ui_FrmXvFuncAsmExpand,"展开"),
                    QIcon(":/images/Ui/FrmXvFuncAsmExpand.svg"),0,QSize(CS_XvFuncType_Btn_Size,20),QSize(CS_XvFuncType_Btn_Size,20));

    btnShowXvFuncAsm->setVisible(false);
    m_drawerAllTypeXvFuncs=  new XMatDrawer(m_drawerParWidget);
    m_drawerAllTypeXvFuncs->setClickOutsideToClose(true);
    m_drawerAllTypeXvFuncs->setOverlayMode(false);
    m_drawerAllTypeXvFuncs->installEventFilter(this);
    auto layout= new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    m_drawerAllTypeXvFuncs->setDrawerLayout(layout);

    //废弃该功能↑
    //xie.y 20230322 todo:需要设置抽屉m_drawerAllTypeXvFuncs



    auto btnUp=ui->btnXvFuncUp;
    U_initSetButton(btnUp,getLang(App_Ui_FrmXvFuncAsmUp,"向上滚动"),getLang(App_Ui_FrmXvFuncAsmUp,"向上滚动"),
                    QIcon(":/images/Ui/FrmXvFuncAsmUp.svg"),0,QSize(CS_XvFuncType_Btn_Size,20),QSize(CS_XvFuncType_Btn_Size,20));

    connect(btnUp,&QToolButton::clicked,this,[&]()
    {
        auto scArea=ui->scAreaXvFuncAsm;
        auto bar=scArea->verticalScrollBar();
        auto curVal= bar->value();
        auto newVal=curVal-bar->singleStep();
        bar->setValue(newVal);
    });

    auto btnDown=ui->btnXvFuncDown;
    U_initSetButton(btnDown,getLang(App_Ui_FrmXvFuncAsmDown,"向下滚动"),getLang(App_Ui_FrmXvFuncAsmDown,"向下滚动"),
                    QIcon(":/images/Ui/FrmXvFuncAsmDown.svg"),0,QSize(CS_XvFuncType_Btn_Size,20),QSize(CS_XvFuncType_Btn_Size,20));

    connect(btnDown,&QToolButton::clicked,this,[&]()
    {
        auto scArea=ui->scAreaXvFuncAsm;
        auto bar=scArea->verticalScrollBar();
        auto curVal= bar->value();
        auto newVal=curVal+bar->singleStep();
        bar->setValue(newVal);
    });
}

void FrmXvFuncAsm::onShowXvFuncTypeDrawer(const QRect &rect,const XvCore::EXvFuncType &type)
{
    auto drawer=m_mapXMatDrawerType[type];
    if(m_drawerCurSingleTypeXvFuncs)
    {
        if(m_drawerCurSingleTypeXvFuncs!=drawer)
        {
            m_drawerCurSingleTypeXvFuncs->closeDrawer();
        }
        m_drawerCurSingleTypeXvFuncs=nullptr;
    }
    if(drawer)
    {
        auto btnTop=rect.top();
        auto btnBottom=rect.bottom();
        auto offsetBtnTopPos= this->mapToParent(QPoint(0,btnTop));
        auto offsetBtnBottomPos= this->mapToParent(QPoint(0,btnBottom));
        auto parWdg=qobject_cast<QWidget*>(drawer->parent());
        if(parWdg)
        {

             auto drawerH=drawer->drawerHeight();
             auto parH= parWdg->height();
             if(offsetBtnTopPos.y()+drawerH>parH)
             {
                 auto offsetY=offsetBtnBottomPos.y()-drawerH;
                 if(offsetY<0)
                 {
                     offsetY=0;
                 }
                 else if(offsetY+drawerH>parH)
                 {
                     offsetY=parH-drawerH;
                 }
                 drawer->setDrawerOffsetY(offsetY);
             }
             else
             {
               drawer->setDrawerOffsetY(offsetBtnTopPos.y());
             }

        }
        drawer->openDrawer();
        m_drawerCurSingleTypeXvFuncs=drawer;
    }


}
