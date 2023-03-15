#ifndef XMATTOOLBUTTON_H
#define XMATTOOLBUTTON_H

#include "XWidgetGlobal.h"
#include <QToolButton>
#include <QScopedPointer>


class XMatToolButtonPrivate;

class XWIDGET_EXPORT XMatToolButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)


public:
    explicit XMatToolButton(QWidget *parent=nullptr);
    ~XMatToolButton();

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatToolButton(XMatToolButtonPrivate &d, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    const QScopedPointer<XMatToolButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatToolButton)
    Q_DECLARE_PRIVATE(XMatToolButton)
};

#endif // XMATTOOLBUTTON_H
