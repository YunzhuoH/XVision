﻿#ifndef XMATMENU_H
#define XMATMENU_H

#include "XWidgetGlobal.h"
#include <QMenu>
#include <QScopedPointer>


class XMatMenuPrivate;

class XWIDGET_EXPORT XMatMenu : public QMenu
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)


public:
    explicit XMatMenu(QWidget *parent=nullptr);
    explicit XMatMenu(const QString &title,QWidget *parent=nullptr);
    ~XMatMenu();

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatMenu(XMatMenuPrivate &d, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    const QScopedPointer<XMatMenuPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatMenu)
    Q_DECLARE_PRIVATE(XMatMenu)
};

#endif // XMATMENU_H