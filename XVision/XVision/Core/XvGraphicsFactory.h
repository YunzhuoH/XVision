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

};

#endif // XVGRAPHICSITEMFACTORY_H
