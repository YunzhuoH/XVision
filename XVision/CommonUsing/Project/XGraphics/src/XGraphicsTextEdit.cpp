#include "XGraphicsTextEdit.h"


XGraphicsTextEdit::XGraphicsTextEdit(QWidget *parent)
    :QTextEdit(parent)
{
   this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

XGraphicsTextEdit::~XGraphicsTextEdit()
{

}

void XGraphicsTextEdit::setXItem(XGraphicsItem *xItem)
{
    m_xItem=xItem;
}

void XGraphicsTextEdit::setXLink(XGraphicsConnectLink *xLink)
{
    m_xLink=xLink;
}

void XGraphicsTextEdit::focusOutEvent(QFocusEvent *e)
{
    QTextEdit::focusOutEvent(e);
    emit focusOut();
}
