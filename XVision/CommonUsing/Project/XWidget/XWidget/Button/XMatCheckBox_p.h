#ifndef XMATCHECKBOX_P_H
#define XMATCHECKBOX_P_H

#include "XMatCheckable_p.h"

class XMatCheckBox;

class XMatCheckBoxPrivate : public XMatCheckablePrivate
{
    Q_DISABLE_COPY(XMatCheckBoxPrivate)
    Q_DECLARE_PUBLIC(XMatCheckBox)

public:
    XMatCheckBoxPrivate(XMatCheckBox *q);
    ~XMatCheckBoxPrivate();

    void init();
};

#endif // XMATCHECKBOX_P_H
