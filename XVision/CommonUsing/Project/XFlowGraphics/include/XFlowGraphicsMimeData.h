#ifndef XFLOWGRAPHICSMIMEDATA_H
#define XFLOWGRAPHICSMIMEDATA_H

#include <QMimeData>
#include "XFlowGraphicsItem.h"

/// XFlowGraphics拖拽数据类
class XFlowGraphicsItem;
class XFLOWGRAPHICS_PUBLIC XFlowGraphicsMimeData:public QMimeData
{
    Q_OBJECT
public:
    XFlowGraphicsMimeData() {}
public://新增
    XFlowGraphicsItem *xItem() {return m_xItem;}
    void setXItem(XFlowGraphicsItem* xItem) { m_xItem=xItem; }
protected:
    XFlowGraphicsItem* m_xItem=nullptr;
};

#endif // XFLOWGRAPHICSMIMEDATA_H
