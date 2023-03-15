#ifndef XMATMENU_P_H
#define XMATMENU_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatMenu.h"

class XMatMenu;
class XMatRippleOverlay;


class XMatMenuPrivate
{
    Q_DISABLE_COPY(XMatMenuPrivate)
    Q_DECLARE_PUBLIC(XMatMenu)

public:
    XMatMenuPrivate(XMatMenu *q);
    virtual ~XMatMenuPrivate();

    void init();

    XMatMenu                      *const q_ptr;
    XMatRippleOverlay                *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATMENU_P_H
