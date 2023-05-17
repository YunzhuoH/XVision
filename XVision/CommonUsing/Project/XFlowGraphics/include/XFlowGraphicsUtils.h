#ifndef XFLOWGRAPHICSUTILS_H
#define XFLOWGRAPHICSUTILS_H

#include "XFlowGraphicsItem.h"
#include "XFlowGraphicsConnectLink.h"

#pragma region xItem转换{

//[xItem转换]
///单xItem转换 QItem→XItem
inline static  XFlowGraphicsItem* qItemtoXItem(QGraphicsItem* qItem)
{
    return dynamic_cast<XFlowGraphicsItem*>(qItem);
}
///图元列表转换
///过滤非XItem图元
inline static QList<QGraphicsItem*> filterNoXItem(const QList<QGraphicsItem*> &lst)
{
    QList<QGraphicsItem*> retLst;
    foreach (auto item, lst)
    {
       auto xItem=qItemtoXItem(item);
       if(!xItem) continue;
       if(xItem->item())
       {
          retLst.append(xItem->item());
       }
    }
    return retLst;
}
///图元列表转换
///获取QItem列表中的XItem图元
inline static QList<XFlowGraphicsItem*> filterQItemToXItem(const QList<QGraphicsItem*> &lst)
{
    QList<XFlowGraphicsItem*> retLst;
    foreach (auto item, lst)
    {
       auto xItem=qItemtoXItem(item);
       if(!xItem) continue;
       if(xItem->item())
       {
          retLst.append(xItem);
       }
    }
    return retLst;
}

#pragma endregion}

#pragma region xLink转换{

//[xLink转换]
///单xLink转换 QItem→XLink
inline static  XFlowGraphicsConnectLink* qItemtoXLink(QGraphicsItem* qItem)
{
    return dynamic_cast<XFlowGraphicsConnectLink*>(qItem);
}
///link列表转换
///过滤非XLink图元
inline static QList<QGraphicsItem*> filterNoXLink(const QList<QGraphicsItem*> &lst)
{
    QList<QGraphicsItem*> retLst;
    foreach (auto item, lst)
    {
       auto xLink=qItemtoXLink(item);
       if(!xLink) continue;
        retLst.append(xLink);
    }
    return retLst;
}
///link列表转换
///获取QItem列表中的XItem图元
inline static QList<XFlowGraphicsConnectLink*> filterGItemToXLink(const QList<QGraphicsItem*> &lst)
{
    QList<XFlowGraphicsConnectLink*> retLst;
    foreach (auto item, lst)
    {
       auto xLink=qItemtoXLink(item);
       if(!xLink) continue;
       retLst.append(xLink);
    }
    return retLst;
}

#pragma endregion }

#pragma region 图型算法{

//[图型算法]

///查询当前curXItem是否存在为ancestorXItem的祖先节点
/// 向上查询(Father)
inline static bool existAncestorXItem(XFlowGraphicsItem* curXItem,XFlowGraphicsItem* ancestorXItem)
{
    auto fathers=curXItem->getFatherConnectLinks();
    if(fathers.count()==0) return false;
    bool bExist=false;
    foreach (auto father, fathers)
    {
        if(father&&father->fatherXItem())
        {
           auto fatherXItem=father->fatherXItem();
           if(fatherXItem)
           {
               if(fatherXItem==ancestorXItem)
               {
                   return true;
               }
               else
               {
                  bExist=existAncestorXItem(fatherXItem,ancestorXItem);
                  if(bExist)
                  {
                      return true;
                  }
               }
           }
        }
    }
    return  bExist;
}

///查询当前curXItem是否存在为descendantsXItem的后代节点
/// 向下查询(Son)
inline static bool existDescendantsXItem(XFlowGraphicsItem* curXItem,XFlowGraphicsItem* descendantsXItem)
{
    auto sons=curXItem->getSonConnectLinks();
    if(sons.count()==0) return false;
    bool bExist=false;
    foreach (auto son, sons)
    {
        if(son&&son->sonXItem())
        {
           auto sonXItem=son->sonXItem();
           if(sonXItem)
           {
               if(sonXItem==descendantsXItem)
               {
                   return true;
               }
               else
               {
                  bExist=existDescendantsXItem(sonXItem,descendantsXItem);
                  if(bExist)
                  {
                      return true;
                  }
               }
           }
        }
    }
    return  bExist;
}



#pragma endregion }


#pragma region 椭圆相关{
///生成椭圆环
inline static QPainterPath genEllipseRing(const QPointF &ptCenter,const double &rx,const double &ry,const double &thickness)
{
    double size=thickness/2;
    QPainterPath ellipseOut;//外圆
    ellipseOut.addEllipse(ptCenter,rx+size,ry+size);
    QPainterPath ellipseIn;//内圆
    ellipseIn.addEllipse(ptCenter,rx-size,ry-size);
    return ellipseOut-ellipseIn;
}
///获取射线和椭圆交点
inline static QPointF getLineEllipseCross(const QPointF &startPt,const double &angle,const QPointF &ptEllipseCenter,const double &rx,const double &ry)
{
    double a=qDegreesToRadians((double)angle);
    int R=rx*ry/sqrt(pow(rx*sin(a),2)+pow(ry*cos(a),2));
    int x=startPt.x()+R*cos(a);
    int y=startPt.y()+R*sin(a);
    return QPointF(x,y);
}

#pragma endregion }

#endif // XFLOWGRAPHICSUTILS_H
