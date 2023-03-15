#ifndef XMATOVERLAYWIDGET_H
#define XMATOVERLAYWIDGET_H

#include "XWidgetGlobal.h"
#include <QWidget>

class XWIDGET_EXPORT XMatOverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XMatOverlayWidget(QWidget *parent = 0);
    ~XMatOverlayWidget();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

    virtual QRect overlayGeometry() const;

private:
    Q_DISABLE_COPY(XMatOverlayWidget)
};

#endif // XMATOVERLAYWIDGET_H
