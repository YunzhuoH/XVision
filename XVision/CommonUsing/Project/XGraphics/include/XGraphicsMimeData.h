#ifndef XGRAPHICSMIMEDATA_H
#define XGRAPHICSMIMEDATA_H

#include <QMimeData>
#include "XGraphicsItem.h"

/// XGraphics拖拽数据类
class XGraphicsItem;
class XGRAPHICS_PUBLIC XGraphicsMimeData:public QMimeData
{
    Q_OBJECT
public:
    XGraphicsMimeData() {}
public://新增
    XGraphicsItem *xItem() {return m_xItem;}
    void setXItem(XGraphicsItem* xItem) { m_xItem=xItem; }
protected:
    XGraphicsItem* m_xItem=nullptr;
};

#endif // XGRAPHICSMIMEDATA_H
