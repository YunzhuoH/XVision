#ifndef XMATTOOLBAR_H
#define XMATTOOLBAR_H

#include "XWidgetGlobal.h"
#include <QToolBar>
#include <QScopedPointer>


class XMatToolBarPrivate;

class XWIDGET_EXPORT XMatToolBar : public QToolBar
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)


public:
    explicit XMatToolBar(QWidget *parent=nullptr);
    explicit XMatToolBar(const QString &title,QWidget *parent=nullptr);
    ~XMatToolBar();

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatToolBar(XMatToolBarPrivate &d, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    const QScopedPointer<XMatToolBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatToolBar)
    Q_DECLARE_PRIVATE(XMatToolBar)
};

#endif // XMATTOOLBAR_H
