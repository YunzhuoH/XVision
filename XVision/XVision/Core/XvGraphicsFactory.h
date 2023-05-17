#ifndef XVGRAPHICSITEMFACTORY_H
#define XVGRAPHICSITEMFACTORY_H

#include "XFlowGraphicsDelegateFactory.h"

class XvGraphicsItemFactory: public XFlowGraphicsItemDelegateFactory
{
    Q_OBJECT
public:
    XvGraphicsItemFactory(XFlowGraphicsScene* scene,QObject* parent=nullptr);
public:

    XFlowGraphicsItem *getXFlowGraphicsItem(const QString &type) override;
protected:
    QMap<QString,QPen> m_mapPen;
};

class XvGraphicsLinkFactory:public XFlowGraphicsLinkDelegateFactory
{
    Q_OBJECT
public:
    XvGraphicsLinkFactory(XFlowGraphicsScene* scene,QObject* parent=nullptr);

public:
    XFlowGraphicsConnectLink *getXFlowGraphicsLink() override;
};

#endif // XVGRAPHICSITEMFACTORY_H
