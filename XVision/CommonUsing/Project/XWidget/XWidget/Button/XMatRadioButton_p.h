#ifndef XMATRADIOBUTTON_P_H
#define XMATRADIOBUTTON_P_H

#include "XMatCheckable_p.h"

class XMatRadioButton;

class XMatRadioButtonPrivate : public XMatCheckablePrivate
{
    Q_DISABLE_COPY(XMatRadioButtonPrivate)
    Q_DECLARE_PUBLIC(XMatRadioButton)

public:
    XMatRadioButtonPrivate(XMatRadioButton *q);
    ~XMatRadioButtonPrivate();

    void init();
};

#endif // XMATRADIOBUTTON_P_H
