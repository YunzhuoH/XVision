#ifndef XMATSUSPENDWIDGET_P_H
#define XMATSUSPENDWIDGET_P_H

#include <QtGlobal>

class QStateMachine;
class XMatSuspendWidget;
class QStackedLayout;
class XMatSuspendWidgetWindow;
class XMatSuspendWidgetProxy;

class XMatSuspendWidgetPrivate
{
    Q_DISABLE_COPY(XMatSuspendWidgetPrivate)
    Q_DECLARE_PUBLIC(XMatSuspendWidget)

public:
    XMatSuspendWidgetPrivate(XMatSuspendWidget *q);
    ~XMatSuspendWidgetPrivate();

    void init();

    XMatSuspendWidget       *const q_ptr;
    XMatSuspendWidgetWindow *widgetWindow;
    QStackedLayout         *proxyStack;
    QStateMachine          *stateMachine;
    XMatSuspendWidgetProxy  *proxy;
};

#endif // XMATSUSPENDWIDGET_P_H
