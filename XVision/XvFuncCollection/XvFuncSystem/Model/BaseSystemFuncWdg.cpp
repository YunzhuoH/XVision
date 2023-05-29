#include "BaseSystemFuncWdg.h"

#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

#include "XTitleBar.h"
#include "XMatToolButton.h"
#include "XMatCheckBox.h"

#include "XvFlow.h"

BaseSystemFuncWdg::BaseSystemFuncWdg(XvFunc *func, QWidget *parent)
    :XFramelessWidget(parent),m_func(func)
{
    this->initFrm();
    if(func)
    {
        connect(func,&XvFunc::sgFuncRunEnd,this,[=](){ onFuncRunUpdate(); });
    }
}

BaseSystemFuncWdg::~BaseSystemFuncWdg()
{

}

void BaseSystemFuncWdg::initCmbBindResultTag(XvFunc *func,QComboBox *cmb,const QStringList &types,const bool &canCustom)
{
    if(!func||!cmb) return;
    cmb->clear();
    if(canCustom)
    {
        cmb->addItem(getLang("XvFuncSystem_BaseSystemFuncWdg_Custom","自定义"));
    }
    foreach (auto type, types)
    {
        auto funcAnstResults=  func->getAncestorsResultByType(type);
        foreach (auto func, funcAnstResults.keys())
        {
            auto lstRet=funcAnstResults[func];
            foreach (auto ret, lstRet)
            {
                SBindResultTag tag(func,ret->objectName());
                QVariant var=QVariant::fromValue(tag);
                QString itemStr=QString("%1.%2").arg(func->funcName()).arg(ret->dispalyName());
                cmb->addItem(itemStr,var);
            }
        }
    }
}

bool BaseSystemFuncWdg::getCmbBindResultTag(QComboBox *cmb, SBindResultTag &tag)
{
    if(!cmb) return false;
    auto idx=cmb->currentIndex();
    auto var=cmb->itemData(idx);
    if(!var.isValid())
    {
        return false;
    }
    auto tagTemp=var.value<SBindResultTag>();
    if(!tagTemp.isValid())
    {
        return false;
    }
    tag=tagTemp;
    return true;
}

bool BaseSystemFuncWdg::setCmbBindResultTag(QComboBox *cmb, const SBindResultTag &tag)
{
    if(!cmb) return false;
    auto count=cmb->count();
    for (int i = 0; i < count; ++i)
    {
        auto var=cmb->itemData(i);
        if(var.isValid())
        {
            auto tagTemp=var.value<SBindResultTag>();
            if(tagTemp.isValid())
            {
                if(tagTemp.func==tag.func&&tagTemp.resultName==tag.resultName)
                {
                    cmb->setCurrentIndex(i);
                    return true;
                }
            }
        }

    }
    return false;
}

void BaseSystemFuncWdg::updateLbTextWithXObject(QLabel* lb,XObject *obj,const QString &suffix)
{
    if(lb&&obj)
    {
        lb->setText(obj->dispalyName()+suffix);
    }
}

void BaseSystemFuncWdg::initCmbByBool(QComboBox *cmb)
{
    cmb->clear();
    cmb->addItem("False");
    cmb->addItem("True");
}

void BaseSystemFuncWdg::setCmbBind(XObject *param, QComboBox *cmb)
{
    XvFunc::SubscribeInfo info;
    if(m_func->getParamSubscribe(param->objectName(),info))
    {
      setCmbBindResultTag(cmb,SBindResultTag(info.first,info.second));
    }
}

void BaseSystemFuncWdg::setCmbWithCmbEnable(QComboBox *cmbBind, QComboBox *cmbVal, const QString &paramName)
{
    auto idx=cmbBind->currentIndex();
    if(idx<0) return;
    if(idx==0)
    {
        if(m_bShowing)
        {
            m_func->paramUnSubscribe(paramName);
        }
        cmbVal->setEnabled(true);
    }
    else
    {
        cmbVal->setEnabled(false);
        SBindResultTag tag;
        if(getCmbBindResultTag(cmbBind,tag))
        {
            m_func->paramSubscribe(paramName,tag.func,tag.resultName);
        }

    }
}

void BaseSystemFuncWdg::setCmbWithLetEnable(QComboBox *cmbBind, QLineEdit *letVal, const QString &paramName)
{
    auto idx=cmbBind->currentIndex();
    if(idx<0) return;
    if(idx==0)
    {
        if(m_bShowing)
        {
            m_func->paramUnSubscribe(paramName);
        }
        letVal->setEnabled(true);
    }
    else
    {
        letVal->setEnabled(false);
        SBindResultTag tag;
        if(getCmbBindResultTag(cmbBind,tag))
        {
            m_func->paramSubscribe(paramName,tag.func,tag.resultName);
        }

    }
}

void BaseSystemFuncWdg::setCmbWithPetEnable(QComboBox *cmbBind, QPlainTextEdit *letVal, const QString &paramName)
{
    auto idx=cmbBind->currentIndex();
    if(idx<0) return;
    if(idx==0)
    {
        if(m_bShowing)
        {
            m_func->paramUnSubscribe(paramName);
        }
        letVal->setEnabled(true);
    }
    else
    {
        letVal->setEnabled(false);
        SBindResultTag tag;
        if(getCmbBindResultTag(cmbBind,tag))
        {
            m_func->paramSubscribe(paramName,tag.func,tag.resultName);
        }

    }
}

void BaseSystemFuncWdg::initFrm()
{
    auto tb =this->titleBar();
    auto size=tb->height()-2;
    auto btnRun=new XMatToolButton(this);
    btnRun->setText("");
    btnRun->setObjectName("btnRun");
    btnRun->setMinimumSize(QSize(size, size));
    btnRun->setIconSize(QSize(size-4,size-4));
    btnRun->setToolTip(getLang("XvFuncSystem_BaseSystemFuncWdg_RunBtn","运行"));
    btnRun->setIcon(QIcon(":/images/XvFuncRun.svg"));
    connect(btnRun,&QToolButton::clicked,this,[=]()
    {
        if(m_func)
        {
            m_func->runXvFunc();
        }

    });
    auto ckb=new XMatCheckBox(this);
    ckb->setText("");
    QString strSetTop=getLang("XvFuncSystem_BaseSystemFuncWdg_SetTop","置顶");
    QString strSetTopCancel=getLang("XvFuncSystem_BaseSystemFuncWdg_SetTopCancel","取消置顶");
    ckb->setToolTip(strSetTop);
    connect(ckb,&XMatCheckBox::toggled,this,[=]()
    {
        bool bChecked=ckb->isChecked();
        if(bChecked)
        {
            setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
            ckb->setToolTip(strSetTopCancel);
        }
        else
        {
            setWindowFlags(windowFlags() ^ Qt::WindowStaysOnTopHint);
            ckb->setToolTip(strSetTop);
        }
        this->show();

    });

    tb->rightLayout()->addWidget(btnRun);
    tb->rightLayout()->addWidget(ckb);   
}

void BaseSystemFuncWdg::initFixedSize()
{
    this->setFixedSize(this->centralWidget()->geometry().width()+10,this->centralWidget()->geometry().height()+20);
}

void BaseSystemFuncWdg::showEvent(QShowEvent *event)
{
    m_bShowing=false;
    onShow();
    m_bShowing=true;
    if(m_func)
    {
        if(m_func->parFlow())
        {
            QString flowName=m_func->parFlow()->flowName();
            this->setWindowTitle(flowName+"."+m_func->funcName());
        }
        else
        {
            this->setWindowTitle(m_func->funcName());
        }

        this->setWindowIcon(m_func->funcIcon());
    }
    return XFramelessWidget::showEvent(event);
}

void BaseSystemFuncWdg::hideEvent(QHideEvent *event)
{
    onHide();
    return XFramelessWidget::hideEvent(event);
}

void BaseSystemFuncWdg::closeEvent(QCloseEvent *event)
{
    onClose();
    return XFramelessWidget::closeEvent(event);
}


