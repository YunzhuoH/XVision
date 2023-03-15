#ifndef XMATCHECKABLE_H
#define XMATCHECKABLE_H

#include "XWidgetGlobal.h"
#include <QtWidgets/QAbstractButton>

class XMatCheckablePrivate;


class XWIDGET_EXPORT XMatCheckable : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QColor checkedColor READ checkedColor WRITE setCheckedColor)
    Q_PROPERTY(QColor uncheckedColor READ uncheckedColor WRITE setUncheckedColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)
    Q_PROPERTY(QIcon checkedIcon READ checkedIcon WRITE setCheckedIcon)
    Q_PROPERTY(QIcon uncheckedIcon READ uncheckedIcon WRITE setUncheckedIcon)
    Q_PROPERTY(LabelPosition labelPosition READ labelPosition WRITE setLabelPosition)
public:
    enum LabelPosition {
        LabelPositionLeft,
        LabelPositionRight,
    };
    Q_ENUM(LabelPosition)

    explicit XMatCheckable(QWidget *parent = 0);
    ~XMatCheckable();

    void setLabelPosition(LabelPosition placement);
    LabelPosition labelPosition() const;


    void setCheckedColor(const QColor &color);
    QColor checkedColor() const;

    void setUncheckedColor(const QColor &color);
    QColor uncheckedColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setCheckedIcon(const QIcon &icon);
    QIcon checkedIcon() const;

    void setUncheckedIcon(const QIcon &icon);
    QIcon uncheckedIcon() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    XMatCheckable(XMatCheckablePrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void setupProperties();

    const QScopedPointer<XMatCheckablePrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatCheckable)
    Q_DECLARE_PRIVATE(XMatCheckable)



};

#endif // XMATCHECKABLE_H
