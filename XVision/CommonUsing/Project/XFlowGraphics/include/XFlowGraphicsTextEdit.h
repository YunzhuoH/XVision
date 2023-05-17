#ifndef XFLOWGRAPHICSTEXTEDIT_H
#define XFLOWGRAPHICSTEXTEDIT_H

#include "XFlowGraphicsGlobal.h"
#include <QTextEdit>

class XFlowGraphicsItem;
class XFlowGraphicsConnectLink;
class XFLOWGRAPHICS_PUBLIC XFlowGraphicsTextEdit:public QTextEdit
{
    Q_OBJECT
public:
    XFlowGraphicsTextEdit(QWidget *parent = nullptr);
    ~XFlowGraphicsTextEdit();
public:
    void setXItem(XFlowGraphicsItem* xItem);
    XFlowGraphicsItem* xItem() const
    {
        return m_xItem;
    }

    void setXLink(XFlowGraphicsConnectLink* xLink);
    XFlowGraphicsConnectLink* xLink() const
    {
        return m_xLink;
    }
signals:
    void focusOut();
protected:
    virtual void focusOutEvent(QFocusEvent *e);
protected:
    XFlowGraphicsItem* m_xItem=nullptr;
    XFlowGraphicsConnectLink* m_xLink=nullptr;
};

#endif // XFLOWGRAPHICSTEXTEDIT_H
