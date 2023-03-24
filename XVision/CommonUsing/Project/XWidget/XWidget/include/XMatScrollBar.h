#ifndef XMATSCROLLBAR_H
#define XMATSCROLLBAR_H

#include "XWidgetGlobal.h"
#include <QScrollBar>

class XMatScrollBarPrivate;

class XWIDGET_EXPORT XMatScrollBar : public QScrollBar
{
    Q_OBJECT

    Q_PROPERTY(QColor canvasColor WRITE setCanvasColor READ canvasColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor sliderColor WRITE setSliderColor READ sliderColor)

public:
    explicit XMatScrollBar(QWidget *parent = 0);
    ~XMatScrollBar();

    QSize sizeHint() const Q_DECL_OVERRIDE;


    void setCanvasColor(const QColor &color);
    QColor canvasColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setSliderColor(const QColor &color);
    QColor sliderColor() const;

    void setHideOnMouseOut(bool value);
    bool hideOnMouseOut() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatScrollBarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatScrollBar)
    Q_DECLARE_PRIVATE(XMatScrollBar)
};

#endif // XMATSCROLLBAR_H
