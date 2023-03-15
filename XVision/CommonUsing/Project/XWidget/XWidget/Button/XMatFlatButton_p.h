#ifndef XMATFLATBUTTON_P_H
#define XMATFLATBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatFlatButton.h"

class XMatFlatButton;
class XMatRippleOverlay;
class XMatFlatButtonStateMachine;

class XMatFlatButtonPrivate
{
    Q_DISABLE_COPY(XMatFlatButtonPrivate)
    Q_DECLARE_PUBLIC(XMatFlatButton)

public:
    XMatFlatButtonPrivate(XMatFlatButton *q);
    virtual ~XMatFlatButtonPrivate();

    void init();

    XMatFlatButton                      *const q_ptr;
    XMatRippleOverlay                   *rippleOverlay;
    XMatFlatButtonStateMachine          *stateMachine;
    XMatFlatButton::FlatButtonIconPlacement  iconPlacement;
    XMatCommonDef::RippleStyle            rippleStyle;
    XMatCommonDef::OverlayStyle           overlayStyle;

    Qt::BGMode                        bgMode;
    Qt::Alignment                     textAlignment;
    QColor                            backgroundColor;
    QColor                            foregroundColor;
    QColor                            overlayColor;
    QColor                            rippleColor;
    QColor                            disabledForegroundColor;
    QColor                            disabledBackgroundColor;
    qreal                             fixedRippleRadius;
    qreal                             cornerRadius;
    qreal                             baseOpacity;
    qreal                             fontSize;
    bool                              useFixedRippleRadius;
    bool                              haloVisible;
};

#endif // XMATFLATBUTTON_P_H
