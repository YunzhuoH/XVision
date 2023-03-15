#ifndef XMATCHECKBOX_H
#define XMATCHECKBOX_H

#include "XMatCheckable.h"

class XMatCheckBoxPrivate;

class XWIDGET_EXPORT XMatCheckBox : public XMatCheckable
{
    Q_OBJECT

public:
    explicit XMatCheckBox(QWidget *parent = 0);
    ~XMatCheckBox();

private:
    Q_DISABLE_COPY(XMatCheckBox)
    Q_DECLARE_PRIVATE(XMatCheckBox)

};

#endif // XMATCHECKBOX_H
