#include "XvGraphicsFactory.h"
#include "XFlowGraphicsRectItem.h"
#include "XFlowGraphicsEllipseItem.h"
#include "XFlowGraphicsConnectLink.h"
#include "XFlowGraphicsScene.h"
#include "XvFuncAssembly.h"
#include "XvFunc.h"

#include "XvWorkManager.h"



XvGraphicsItemFactory::XvGraphicsItemFactory(XFlowGraphicsScene* scene,QObject *parent)
    :XFlowGraphicsItemDelegateFactory{scene,parent}
{
    m_mapPen.clear();
    //图标设置
    QPen pen;
    pen.setWidth(1);
    pen.setBrush(Qt::NoBrush);
    m_mapPen[XvFuncRunStatus_Init_Str]=pen;//初始状态

    pen.setBrush(QColor(50,130,250,230));
    m_mapPen[XvFuncRunStatus_Running_Str]=pen;//正在运行状态

    pen.setBrush(QColor(0,255,0,230));
    m_mapPen[XvFuncRunStatus_Ok_Str]=pen;//成功状态

    pen.setBrush(QColor(255,128,0,230));
    m_mapPen[XvFuncRunStatus_Fail_Str]=pen;//失败状态

    pen.setBrush(QColor(255,30,0,230));
    m_mapPen[XvFuncRunStatus_Error_Str]=pen;//错误状态

}

XFlowGraphicsItem *XvGraphicsItemFactory::getXFlowGraphicsItem(const QString &type)
{
    auto info=XvWorkMgr->getXvCoreMgr()->getXvFuncAsm()->getXvFuncInfo(type);
    auto lst=m_parScene->getXItemsByType(type);
    int nIdx=lst.count()+1;
    XFlowGraphicsRectItem *item=new XFlowGraphicsRectItem(type,"",m_parScene);
    item->setTextFont(QFont("Microsoft YaHei UI", 10, QFont::Bold));
    item->setText(info.name+QString("-%1").arg(nIdx));
    item->setSize(190,65);
    item->addPixData(new SXItemPixData(XvFuncName,info.icon,m_mapPen));
    item->switchShowPixKey(XvFuncName,XvFuncRunStatus_Init_Str);
    item->setConnectRectSize(30);
    item->updateShape();
    item->setSelectBoundingRectPen(QPen(QColor(25, 150, 255),1,Qt::DashLine));
    return item;
}


XvGraphicsLinkFactory::XvGraphicsLinkFactory(XFlowGraphicsScene *scene, QObject *parent)
    :XFlowGraphicsLinkDelegateFactory{scene,parent}
{

}

XFlowGraphicsConnectLink *XvGraphicsLinkFactory::getXFlowGraphicsLink()
{
    XFlowGraphicsConnectLink *link=new XFlowGraphicsConnectLink(m_parScene);
    link->setSelectBoundingRectPen(QPen(QColor(25, 150, 255),1,Qt::DashLine));
    return link;
}
