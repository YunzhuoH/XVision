#ifndef XMATTOOLBUTTON_P_H
#define XMATTOOLBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatToolButton.h"

class XMatToolButton;
class XMatRippleOverlay;


class XMatToolButtonPrivate
{
    Q_DISABLE_COPY(XMatToolButtonPrivate)
    Q_DECLARE_PUBLIC(XMatToolButton)

public:
    XMatToolButtonPrivate(XMatToolButton *q);
    virtual ~XMatToolButtonPrivate();

    void init();

    XMatToolButton                    *const q_ptr;
    XMatRippleOverlay                 *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATTOOLBUTTON_P_H
