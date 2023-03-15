#ifndef XMATTOGGLE_H
#define XMATTOGGLE_H

#include "XWidgetGlobal.h"
#include <QtWidgets/QAbstractButton>

class XMatTogglePrivate;

class XWIDGET_EXPORT XMatToggle : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
    Q_PROPERTY(QColor activeColor WRITE setActiveColor READ activeColor)
    Q_PROPERTY(QColor inactiveColor WRITE setInactiveColor READ inactiveColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(Qt::Orientation  orientation WRITE setOrientation READ orientation)

public:
    explicit XMatToggle(QWidget *parent = 0);
    ~XMatToggle();

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setActiveColor(const QColor &color);
    QColor activeColor() const;

    void setInactiveColor(const QColor &color);
    QColor inactiveColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatTogglePrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatToggle)
    Q_DECLARE_PRIVATE(XMatToggle)
};

#endif // XMATTOGGLE_H
