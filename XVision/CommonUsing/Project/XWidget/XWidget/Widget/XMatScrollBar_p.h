#ifndef XMATSCROLLBAR_P_H
#define XMATSCROLLBAR_P_H

#include <QtGlobal>
#include <QColor>

class XMatScrollBar;
class XMatScrollBarStateMachine;

class XMatScrollBarPrivate
{
    Q_DISABLE_COPY(XMatScrollBarPrivate)
    Q_DECLARE_PUBLIC(XMatScrollBar)

public:
    XMatScrollBarPrivate(XMatScrollBar *q);
    ~XMatScrollBarPrivate();

    void init();

    XMatScrollBar             *const q_ptr;
    XMatScrollBarStateMachine *stateMachine;
    QColor                           backgroundColor;
    QColor                           sliderColor;
    QColor                           canvasColor;
    bool                             hideOnMouseOut;
};

#endif // XMATSCROLLBAR_P_H
