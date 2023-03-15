#ifndef XMATFLATBUTTONSTATETRANSITION_H
#define XMATFLATBUTTONSTATETRANSITION_H

#include <QAbstractTransition>
#include <QEvent>

enum XMatFlatButtonStateTransitionType {

    // FlatButton
    FlatButtonPressedTransition,
    FlatButtonCheckedTransition,
    FlatButtonUncheckedTransition,
};

struct XMatFlatButtonStateTransitionEvent : public QEvent
{
    XMatFlatButtonStateTransitionEvent(XMatFlatButtonStateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    XMatFlatButtonStateTransitionType type;
};


class XMatFlatButtonStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    XMatFlatButtonStateTransition(XMatFlatButtonStateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    XMatFlatButtonStateTransitionType m_type;
};

#endif // XMATFLATBUTTONSTATETRANSITION_H
