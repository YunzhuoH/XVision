#include "WdgItemXvFunc.h"
#include "ui_WdgItemXvFunc.h"

#include <QDrag>
#include <QMimeData>

#define Item_Btn_Property "Role"
const static int WdgItemXvFunc_XvFunc_IconSize=40;

WdgItemXvFunc::WdgItemXvFunc(const XvCore::XvFuncInfo &info,QWidget *parent) :
    BaseWidget(parent),m_xvFuncInfo(info),
    ui(new Ui::WdgItemXvFunc)
{
    ui->setupUi(this);
    initFrm();
}

WdgItemXvFunc::~WdgItemXvFunc()
{
    delete ui;
}

void WdgItemXvFunc::initFrm()
{
    auto btn=ui->btnXvFunc;
    U_initSetButton(btn,m_xvFuncInfo.name,m_xvFuncInfo.name,m_xvFuncInfo.icon,WdgItemXvFunc_XvFunc_IconSize);
    btn->setProperty(Item_Btn_Property,m_xvFuncInfo.role);
    auto lb=ui->lbXvFunc;
    lb->setText(m_xvFuncInfo.name);
    lb->setAlignment(Qt::AlignCenter);
    connect(btn,&QToolButton::released,this,&WdgItemXvFunc::onXvFunc);
}

void WdgItemXvFunc::onXvFunc()
{
    auto btn=qobject_cast<QToolButton*>(sender());
    if(btn)
    {
         auto xvFuncType= btn->property(Item_Btn_Property);
         if(xvFuncType.isValid())
         {
             auto role=xvFuncType.toString();

             QDrag *drag = new QDrag(this);
             QMimeData *data = new QMimeData();
             data->clear();
             data->setText(role);
             drag->setMimeData(data);
             drag->exec();
         }
    }

}
