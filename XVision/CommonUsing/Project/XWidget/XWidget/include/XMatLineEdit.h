#ifndef XMATLINEEDIT_H
#define XMATLINEEDIT_H

#include "XWidgetGlobal.h"
#include <QLineEdit>
#include <QColor>

class XMatLineEditPrivate;

class XWIDGET_EXPORT XMatLineEdit : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor inputLineColor WRITE setInputLineColor READ inputLineColor)

public:
    explicit XMatLineEdit(QWidget *parent = 0);
    ~XMatLineEdit();

    void setShowLabel(bool value);
    bool hasLabel() const;

    void setLabelFontSize(qreal size);
    qreal labelFontSize() const;

    void setLabel(const QString &label);
    QString label() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setLabelColor(const QColor &color);
    QColor labelColor() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setInputLineColor(const QColor &color);
    QColor inputLineColor() const;

    void setShowInputLine(bool value);
    bool hasInputLine() const;

protected:
    XMatLineEdit(XMatLineEditPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatLineEditPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatLineEdit)
    Q_DECLARE_PRIVATE(XMatLineEdit)
};

#endif // XMATLINEEDIT_H
