#ifndef XMATMENUBAR_P_H
#define XMATMENUBAR_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatMenuBar.h"

class XMatMenuBar;
class XMatRippleOverlay;


class XMatMenuBarPrivate
{
    Q_DISABLE_COPY(XMatMenuBarPrivate)
    Q_DECLARE_PUBLIC(XMatMenuBar)

public:
    XMatMenuBarPrivate(XMatMenuBar *q);
    virtual ~XMatMenuBarPrivate();

    void init();

    XMatMenuBar                      *const q_ptr;
    XMatRippleOverlay                *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATMENUBAR_P_H
