﻿#ifndef XMADOUBLESPINBOX_H
#define XMADOUBLESPINBOX_H

#include "XWidgetGlobal.h"
#include <QDoubleSpinBox>
#include <QScopedPointer>

class XMatDoubleSpinBoxPrivate;

class XWIDGET_EXPORT XMatDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)


public:
    explicit XMatDoubleSpinBox(QWidget *parent = nullptr);
    ~XMatDoubleSpinBox();

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatDoubleSpinBox(XMatDoubleSpinBoxPrivate &d, QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatDoubleSpinBoxPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatDoubleSpinBox)
    Q_DECLARE_PRIVATE(XMatDoubleSpinBox)

};

#endif // XMADOUBLESPINBOX_H
