#ifndef XMATMENUBAR_H
#define XMATMENUBAR_H

#include "XWidgetGlobal.h"
#include <QMenuBar>
#include <QScopedPointer>


class XMatMenuBarPrivate;

class XWIDGET_EXPORT XMatMenuBar : public QMenuBar
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)


public:
    explicit XMatMenuBar(QWidget *parent=nullptr);
    ~XMatMenuBar();

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatMenuBar(XMatMenuBarPrivate &d, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    const QScopedPointer<XMatMenuBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatMenuBar)
    Q_DECLARE_PRIVATE(XMatMenuBar)
};

#endif // XMATMENUBAR_H
