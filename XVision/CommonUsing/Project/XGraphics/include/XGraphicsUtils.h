#ifndef XGRAPHICSUTILS_H
#define XGRAPHICSUTILS_H

#include "XGraphicsItem.h"
#include "XGraphicsConnectLink.h"

#pragma region xItem转换{

//[xItem转换]
///单xItem转换 QItem→XItem
inline static  XGraphicsItem* qItemtoXItem(QGraphicsItem* qItem)
{
    return dynamic_cast<XGraphicsItem*>(qItem);
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
inline static QList<XGraphicsItem*> filterQItemToXItem(const QList<QGraphicsItem*> &lst)
{
    QList<XGraphicsItem*> retLst;
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
inline static  XGraphicsConnectLink* qItemtoXLink(QGraphicsItem* qItem)
{
    return dynamic_cast<XGraphicsConnectLink*>(qItem);
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
inline static QList<XGraphicsConnectLink*> filterGItemToXLink(const QList<QGraphicsItem*> &lst)
{
    QList<XGraphicsConnectLink*> retLst;
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
inline static bool existAncestorXItem(XGraphicsItem* curXItem,XGraphicsItem* ancestorXItem)
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
inline static bool existDescendantsXItem(XGraphicsItem* curXItem,XGraphicsItem* descendantsXItem)
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



#endif // XGRAPHICSUTILS_H
