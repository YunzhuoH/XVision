#include "XFlowGraphicsTextEdit.h"
#include "XFlowGraphicsItem.h"
#include "XFlowGraphicsConnectLink.h"

XFlowGraphicsTextEdit::XFlowGraphicsTextEdit(QWidget *parent)
    :QTextEdit(parent)
{
   this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

XFlowGraphicsTextEdit::~XFlowGraphicsTextEdit()
{

}

void XFlowGraphicsTextEdit::setXItem(XFlowGraphicsItem *xItem)
{
    m_xItem=xItem;
}

void XFlowGraphicsTextEdit::setXLink(XFlowGraphicsConnectLink *xLink)
{
    m_xLink=xLink;
}

void XFlowGraphicsTextEdit::focusOutEvent(QFocusEvent *e)
{
    QTextEdit::focusOutEvent(e);
    emit focusOut();
}
