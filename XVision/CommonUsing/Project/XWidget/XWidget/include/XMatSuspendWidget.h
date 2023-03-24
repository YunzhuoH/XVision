#ifndef XMATSUSPENDWIDGET_H
#define XMATSUSPENDWIDGET_H

#include "XWidgetGlobal.h"
#include <QScopedPointer>
#include "XMatOverlayWidget.h"

class QLayout;
class XMatSuspendWidgetPrivate;

class XWIDGET_EXPORT XMatSuspendWidget : public XMatOverlayWidget
{
    Q_OBJECT

public:
    explicit XMatSuspendWidget(QWidget *parent = 0);
    ~XMatSuspendWidget();

    QLayout *windowLayout() const;
    void setWindowLayout(QLayout *layout);

public slots:
    void showWidget();
    void hideWidget();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatSuspendWidgetPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatSuspendWidget)
    Q_DECLARE_PRIVATE(XMatSuspendWidget)
};

#endif // XMATSUSPENDWIDGET_H
