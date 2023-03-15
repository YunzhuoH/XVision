#ifndef XMATTOOLBAR_P_H
#define XMATTOOLBAR_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatToolBar.h"

class XMatToolBar;
class XMatRippleOverlay;


class XMatToolBarPrivate
{
    Q_DISABLE_COPY(XMatToolBarPrivate)
    Q_DECLARE_PUBLIC(XMatToolBar)

public:
    XMatToolBarPrivate(XMatToolBar *q);
    virtual ~XMatToolBarPrivate();

    void init();

    XMatToolBar                      *const q_ptr;
    XMatRippleOverlay                *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATTOOLBAR_P_H
