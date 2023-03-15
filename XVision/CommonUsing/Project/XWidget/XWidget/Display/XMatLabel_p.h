#ifndef XMATLABEL_P_H
#define XMATLABEL_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatLabel.h"

class XMatLabel;
class XMatRippleOverlay;


class XMatLabelPrivate
{
    Q_DISABLE_COPY(XMatLabelPrivate)
    Q_DECLARE_PUBLIC(XMatLabel)

public:
    XMatLabelPrivate(XMatLabel *q);
    virtual ~XMatLabelPrivate();

    void init();

    XMatLabel                      *const q_ptr;
    XMatRippleOverlay              *rippleOverlay;

    QColor                            rippleColor;

};

#endif // XMATLABEL_P_H
