#ifndef XGRAPHICSDELEGATEFACTORY_H
#define XGRAPHICSDELEGATEFACTORY_H

#include "XGraphicsItem.h"
#include <QGraphicsScene>
#include <QObject>

#include "XGraphicsGlobal.h"

class  XGraphicsScene;
///形状节点委托工厂类
class XGRAPHICS_PUBLIC XGraphicsItemDelegateFactory:public QObject
{
public:
    XGraphicsItemDelegateFactory(XGraphicsScene* scene,QObject* parent=nullptr)
        :QObject{parent},
        m_parScene(scene)
    {

    }
public:
    void setScene(XGraphicsScene* scene) {m_parScene=scene;}
    virtual XGraphicsItem* getXGraphicsItem(const QString &type) {  return nullptr; }
protected:
    XGraphicsScene* m_parScene;
};

class XGRAPHICS_PUBLIC XGraphicsLinkDelegateFactory:public QObject
{
public:
    XGraphicsLinkDelegateFactory(XGraphicsScene* scene,QObject* parent=nullptr)
        :QObject{parent},
         m_parScene(scene)
    {

    }
public:
    void setScene(XGraphicsScene* scene) {m_parScene=scene;}
    virtual XGraphicsConnectLink* getXGraphicsLink() {  return nullptr; }
protected:
    XGraphicsScene* m_parScene;
};
#endif // XGRAPHICSDELEGATEFACTORY_H
