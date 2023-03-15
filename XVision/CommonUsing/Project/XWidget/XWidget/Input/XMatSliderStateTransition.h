#ifndef XMATSLIDERSTATETRANSITION_H
#define XMATSLIDERSTATETRANSITION_H

#include <QAbstractTransition>
#include <QEvent>

enum XMatSliderStateTransitionType {

    // Slider
    SliderChangedToMinimum,
    SliderChangedFromMinimum,
    SliderNoFocusMouseEnter,
    SliderNoFocusMouseLeave,
};

struct XMatSliderStateTransitionEvent : public QEvent
{
    XMatSliderStateTransitionEvent(XMatSliderStateTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1)),
          type(type)
    {
    }

    XMatSliderStateTransitionType type;
};


class  XMatSliderStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
     XMatSliderStateTransition(XMatSliderStateTransitionType type);

protected:
    virtual bool eventTest(QEvent *event);
    virtual void onTransition(QEvent *);

private:
    XMatSliderStateTransitionType m_type;
};

#endif // XMATSLIDERSTATETRANSITION_H
