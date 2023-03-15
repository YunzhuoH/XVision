#ifndef XMATRADIOBUTTON_H
#define XMATRADIOBUTTON_H

#include "XMatCheckable.h"

class XMatRadioButtonPrivate;

class XWIDGET_EXPORT XMatRadioButton : public XMatCheckable
{
    Q_OBJECT
public:
    explicit XMatRadioButton(QWidget *parent = 0);
    ~XMatRadioButton();

protected:
    void setupProperties();

private:
    Q_DISABLE_COPY(XMatRadioButton)
    Q_DECLARE_PRIVATE(XMatRadioButton)


};

#endif // XMATRADIOBUTTON_H
