#ifndef XMATPLAINTEXTEDIT_P_H
#define XMATPLAINTEXTEDIT_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatPlainTextEdit.h"

class XMatPlainTextEdit;
class XMatRippleOverlay;


class XMatPlainTextEditPrivate
{
    Q_DISABLE_COPY(XMatPlainTextEditPrivate)
    Q_DECLARE_PUBLIC(XMatPlainTextEdit)

public:
    XMatPlainTextEditPrivate(XMatPlainTextEdit *q);
    virtual ~XMatPlainTextEditPrivate();

    void init();

    XMatPlainTextEdit              *const q_ptr;
    XMatRippleOverlay              *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATPLAINTEXTEDIT_P_H
