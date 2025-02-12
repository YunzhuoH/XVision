﻿#ifndef XMASPINBOX_H
#define XMASPINBOX_H

#include "XWidgetGlobal.h"
#include "XMatCommonDef.h"
#include <QSpinBox>
#include <QScopedPointer>


class XMatSpinBoxPrivate;

class XWIDGET_EXPORT XMatSpinBox : public QSpinBox
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)
    Q_PROPERTY(XMatCommonDef::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)


public:
    explicit XMatSpinBox(QWidget *parent = nullptr);
    ~XMatSpinBox();


    void setRippleStyle(XMatCommonDef::RippleStyle style);
    XMatCommonDef::RippleStyle rippleStyle() const;

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatSpinBox(XMatSpinBoxPrivate &d, QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatSpinBoxPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatSpinBox)
    Q_DECLARE_PRIVATE(XMatSpinBox)


};

#endif // XMASPINBOX_H
