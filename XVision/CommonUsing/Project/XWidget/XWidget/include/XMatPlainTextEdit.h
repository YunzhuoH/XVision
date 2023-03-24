#ifndef XMATPLAINTEXTEDIT_H
#define XMATPLAINTEXTEDIT_H

#include "XWidgetGlobal.h"
#include "XMatCommonDef.h"
#include <QPlainTextEdit>
#include <QScopedPointer>


class XMatPlainTextEditPrivate;

class XWIDGET_EXPORT XMatPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)
    Q_PROPERTY(XMatCommonDef::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)

public:
    explicit XMatPlainTextEdit(QWidget *parent=nullptr);
    explicit XMatPlainTextEdit(const QString &text, QWidget *parent=nullptr);
    ~XMatPlainTextEdit();

    void setRippleStyle(XMatCommonDef::RippleStyle style);
    XMatCommonDef::RippleStyle rippleStyle() const;


    void setRippleColor(const QColor &color);
    QColor rippleColor() const;
protected:

    XMatPlainTextEdit(XMatPlainTextEditPrivate &d, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatPlainTextEditPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatPlainTextEdit)
    Q_DECLARE_PRIVATE(XMatPlainTextEdit)



};

#endif // XMATPLAINTEXTEDIT_H
