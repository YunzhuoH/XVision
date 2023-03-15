#ifndef XMATTABS_P_H
#define XMATTABS_P_H

#include <QtGlobal>
#include "XMatTabs.h"

class QHBoxLayout;
class XMatTabs;
class XMatTabsInkBar;

class XMatTabsPrivate
{
    Q_DISABLE_COPY(XMatTabsPrivate)
    Q_DECLARE_PUBLIC(XMatTabs)

public:
    XMatTabsPrivate(XMatTabs *q);
    ~XMatTabsPrivate();

    void init();

    XMatTabs       *const q_ptr;
    XMatTabsInkBar *inkBar;
    QHBoxLayout          *tabLayout;
    XMatCommonDef::RippleStyle rippleStyle;
    QColor                inkColor;
    QColor                backgroundColor;
    QColor                textColor;
    int                   tab;
    bool                  showHalo;
};

#endif // XMATTABS_P_H
