#ifndef XFLOWGRAPHICSDELEGATEFACTORY_H
#define XFLOWGRAPHICSDELEGATEFACTORY_H

#include "XFlowGraphicsItem.h"
#include <QGraphicsScene>
#include <QObject>

#include "XFlowGraphicsGlobal.h"

class  XFlowGraphicsScene;
///形状节点委托工厂类
class XFLOWGRAPHICS_PUBLIC XFlowGraphicsItemDelegateFactory:public QObject
{
public:
    XFlowGraphicsItemDelegateFactory(XFlowGraphicsScene* scene,QObject* parent=nullptr)
        :QObject{parent},
        m_parScene(scene)
    {

    }
public:
    void setScene(XFlowGraphicsScene* scene) {m_parScene=scene;}
    virtual XFlowGraphicsItem* getXFlowGraphicsItem(const QString &type) {  return nullptr; }
protected:
    XFlowGraphicsScene* m_parScene;
};

class XFLOWGRAPHICS_PUBLIC XFlowGraphicsLinkDelegateFactory:public QObject
{
public:
    XFlowGraphicsLinkDelegateFactory(XFlowGraphicsScene* scene,QObject* parent=nullptr)
        :QObject{parent},
         m_parScene(scene)
    {

    }
public:
    void setScene(XFlowGraphicsScene* scene) {m_parScene=scene;}
    virtual XFlowGraphicsConnectLink* getXFlowGraphicsLink() {  return nullptr; }
protected:
    XFlowGraphicsScene* m_parScene;
};
#endif // XFLOWGRAPHICSDELEGATEFACTORY_H
