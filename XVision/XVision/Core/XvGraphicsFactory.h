#ifndef XVGRAPHICSITEMFACTORY_H
#define XVGRAPHICSITEMFACTORY_H

#include "XGraphicsDelegateFactory.h"

class XvGraphicsItemFactory: public XGraphicsItemDelegateFactory
{
    Q_OBJECT
public:
    XvGraphicsItemFactory(XGraphicsScene* scene,QObject* parent=nullptr);
public:

    XGraphicsItem *getXGraphicsItem(const QString &type) override;
protected:
    QMap<QString,QPen> m_mapPen;
};

class XvGraphicsLinkFactory:public XGraphicsLinkDelegateFactory
{
    Q_OBJECT
public:
    XvGraphicsLinkFactory(XGraphicsScene* scene,QObject* parent=nullptr);

public:
    XGraphicsConnectLink *getXGraphicsLink() override;
};

#endif // XVGRAPHICSITEMFACTORY_H
