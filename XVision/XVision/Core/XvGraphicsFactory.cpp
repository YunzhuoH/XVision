#include "XvGraphicsFactory.h"
#include "XGraphicsRectItem.h"
#include "XGraphicsEllipseItem.h"
#include "XGraphicsConnectLink.h"
#include "XGraphicsScene.h"
#include "XvCoreManager.h"
#include "XvFuncAssembly.h"
#include "XvFuncBase.h"




XvGraphicsItemFactory::XvGraphicsItemFactory(XGraphicsScene* scene,QObject *parent)
    :XGraphicsItemDelegateFactory{scene,parent}
{

}

XGraphicsItem *XvGraphicsItemFactory::getXGraphicsItem(const QString &type)
{
    auto info=XvCoreMgr->getXvFuncAsm()->getXvFuncInfo(type);
    auto lst=m_parScene->getXItemsByType(type);
    int nIdx=lst.count()+1;
    XGraphicsRectItem *item=new XGraphicsRectItem(type,"",m_parScene);
    //item->setWidth(180);
    //item->setHeight(60);
    item->setTextFont(QFont("Microsoft YaHei UI", 9, QFont::Normal));
    item->setText(info.name+QString("-%1").arg(nIdx));
    item->setTip(QString("Item-Id:%1\r\nRole:%2").arg(item->itemId()).arg(type));
    //图标设置
    QPen pen;
    pen.setBrush(Qt::NoBrush);
    QBrush brush=(Qt::NoBrush);
    //初始状态
    item->addPixData(new SXItemPixData(XvFuncStatus_Init_Str,info.icon,true,pen,brush));

    //成功状态
    brush=QBrush(QColor(0,255,0,230));
    item->addPixData(new SXItemPixData(XvFuncStatus_Ok_Str,info.icon,true,pen,brush));

    //失败状态
    brush=QBrush(QColor(255,128,0,230));
    item->addPixData(new SXItemPixData(XvFuncStatus_Fail_Str,info.icon,true,pen,brush));

    //错误状态
    brush=QBrush(QColor(255,30,0,230));
    item->addPixData(new SXItemPixData(XvFuncStatus_Error_Str,info.icon,true,pen,brush));

    item->switchShowPixKey(XvFuncStatus_Init_Str);
    return item;

}

