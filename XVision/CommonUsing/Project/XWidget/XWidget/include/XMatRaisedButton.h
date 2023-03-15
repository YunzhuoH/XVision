#ifndef XMATRAISEDBUTTON_H
#define XMATRAISEDBUTTON_H

#include "XMatFlatButton.h"

class XMatRaisedButtonPrivate;

class XWIDGET_EXPORT XMatRaisedButton : public XMatFlatButton
{
    Q_OBJECT

public:
    explicit XMatRaisedButton(QWidget *parent = 0);
    explicit XMatRaisedButton(const QString &text, QWidget *parent = 0);
    ~XMatRaisedButton();

protected:
    XMatRaisedButton(XMatRaisedButtonPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatRaisedButton)
    Q_DECLARE_PRIVATE(XMatRaisedButton)


};

#endif // XMATRAISEDBUTTON_H
