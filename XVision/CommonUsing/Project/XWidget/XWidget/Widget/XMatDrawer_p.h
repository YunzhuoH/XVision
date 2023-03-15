#ifndef XMATDRAWER_P_H
#define XMATDRAWER_P_H

#include <QObject>

class XMatDrawer;
class XMatDrawerWidget;
class XMatDrawerStateMachine;

class XMatDrawerPrivate
{
    Q_DISABLE_COPY(XMatDrawerPrivate)
    Q_DECLARE_PUBLIC(XMatDrawer)

public:
    XMatDrawerPrivate(XMatDrawer *q);
    ~XMatDrawerPrivate();

    void init();
    void setClosed(bool value = true);

    XMatDrawer             *const q_ptr;
    XMatDrawerWidget       *widget;
    XMatDrawerStateMachine *stateMachine;
    QWidget                      *window;

    int                           width;
    bool                          clickToClose;
    bool                          autoRaise;
    bool                          closed;
    bool                          overlay;
};

#endif // XMATDRAWER_P_H
