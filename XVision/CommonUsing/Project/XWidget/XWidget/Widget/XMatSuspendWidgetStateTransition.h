#ifndef XMATSUSPENDWIDGETSTATETRANSITION_H
#define XMATSUSPENDWIDGETSTATETRANSITION_H

#include <QAbstractTransition>
#include <QEvent>

enum XMatSuspendWidgetStateTransitionType {

    // SuspendWidget
    SuspendWidgetShowTransition,
    SuspendWidgetHideTransition,
};

struct XMatSuspendWidgetStateTransitionEvent : public QEvent
{
    XMatSuspendWidgetStateTransitionEvent(XMatSuspendWidgetStateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    XMatSuspendWidgetStateTransitionType type;
};


class XMatSuspendWidgetStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    XMatSuspendWidgetStateTransition(XMatSuspendWidgetStateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    XMatSuspendWidgetStateTransitionType m_type;
};

#endif // XMATSUSPENDWIDGETSTATETRANSITION_H
