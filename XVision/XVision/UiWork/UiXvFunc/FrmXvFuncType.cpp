#include "FrmXvFuncType.h"
#include "ui_FrmXvFuncType.h"

#include "LangDef.h"

#include "XMatScrollBar.h"
#include "WdgItemXvFunc.h"


///算子每行最大个数
const static int FrmXvFuncType_Max_Col=3;
///算子图标大小
const static int FrmXvFuncType_XvFunc_IconSize=30;
const static int FrmXvFuncType_XvFunc_BtnSize=38;

FrmXvFuncType::FrmXvFuncType(const XvCore::XvFuncTypeInfo &info,
                             const QList<XvCore::XvFuncBaseInfo> &lst,
                             QWidget *parent) :
    BaseWidget(parent),m_typeInfo(info),m_lstXvFuncInfos(lst),
    ui(new Ui::FrmXvFuncType)
{
    ui->setupUi(this);
    initFrm();
}

FrmXvFuncType::~FrmXvFuncType()
{
    delete ui;
}

void FrmXvFuncType::initFrm()
{
    auto btnType=ui->btnXvFuncType;
    U_initSetButton(btnType,m_typeInfo.name,m_typeInfo.name,m_typeInfo.icon,FrmXvFuncType_XvFunc_IconSize);

    auto lbType=ui->lbXvFuncType;
    lbType->setText(m_typeInfo.name);

    auto btnClose=ui->btnCloseDrawer;
    U_initSetButton(btnClose,getLang(App_Close,"关闭"),getLang(App_Close,"关闭"),QIcon(":/images/Ui/FrmXvFuncTypeClose.svg"),FrmXvFuncType_XvFunc_IconSize);
    connect(btnClose,&QToolButton::clicked,this,&FrmXvFuncType::onCloseDrawer);

    auto scArea=ui->scAreaXvFunc;
    auto scAreaWc=ui->scAreaWcXvFunc;
    scArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    scArea->setLineWidth(1);
    scArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scArea->setVerticalScrollBar(new XMatScrollBar(scArea));
    QVBoxLayout *vLayout = new QVBoxLayout(scAreaWc);
    vLayout->setObjectName("verticalLayout");
    vLayout->setContentsMargins(0, 5, 0, 5);
    vLayout->setSpacing(5);
    scAreaWc->setLayout(vLayout);

    auto row=ceil(m_lstXvFuncInfos.count()*1.0/3);
    for (int i = 0; i < row; ++i)
    {
        QHBoxLayout *hLayout=new QHBoxLayout();
        vLayout->addLayout(hLayout);
        for (int j = 0; j < 3; ++j)
        {
            int curIdx=i*3+j;
            if(m_lstXvFuncInfos.count()>curIdx)
            {
                auto info=m_lstXvFuncInfos.at(curIdx);
                auto item=new WdgItemXvFunc(info);
                hLayout->addWidget(item);
            }


        }
    }
    vLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum,QSizePolicy::Expanding ));
}

void FrmXvFuncType::onCloseDrawer()
{
    emit closeDrawer();
}



