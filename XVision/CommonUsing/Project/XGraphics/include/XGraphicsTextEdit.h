#ifndef XGRAPHICSTEXTEDIT_H
#define XGRAPHICSTEXTEDIT_H

#include "XGraphicsGlobal.h"

#include <QTextEdit>
#include "XGraphicsItem.h"
#include "XGraphicsConnectLink.h"

class XGRAPHICS_PUBLIC XGraphicsTextEdit:public QTextEdit
{
    Q_OBJECT
public:
    XGraphicsTextEdit(QWidget *parent = nullptr);
    ~XGraphicsTextEdit();
public:
    void setXItem(XGraphicsItem* xItem);
    XGraphicsItem* xItem() const
    {
        return m_xItem;
    }

    void setXLink(XGraphicsConnectLink* xLink);
    XGraphicsConnectLink* xLink() const
    {
        return m_xLink;
    }
signals:
    void focusOut();
protected:
    virtual void focusOutEvent(QFocusEvent *e);
protected:
    XGraphicsItem* m_xItem=nullptr;
    XGraphicsConnectLink* m_xLink=nullptr;
};

#endif // XGRAPHICSTEXTEDIT_H
