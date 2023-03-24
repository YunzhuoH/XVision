#ifndef XMATLABEL_H
#define XMATLABEL_H

#include "XWidgetGlobal.h"
#include "XMatCommonDef.h"
#include <QLabel>
#include <QScopedPointer>


class XMatLabelPrivate;

class XWIDGET_EXPORT XMatLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)
    Q_PROPERTY(XMatCommonDef::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)


public:
    explicit XMatLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit XMatLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    ~XMatLabel();

    void setRippleStyle(XMatCommonDef::RippleStyle style);
    XMatCommonDef::RippleStyle rippleStyle() const;

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatLabel(XMatLabelPrivate &d, QWidget *parent = 0,Qt::WindowFlags f=Qt::WindowFlags());

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    const QScopedPointer<XMatLabelPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatLabel)
    Q_DECLARE_PRIVATE(XMatLabel)
};

#endif // XMATLABEL_H
