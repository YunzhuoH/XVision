#include "XMatSliderStateTransition.h"

XMatSliderStateTransition::XMatSliderStateTransition(XMatSliderStateTransitionType type)
    : m_type(type)
{
}

bool XMatSliderStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    XMatSliderStateTransitionEvent *transition = static_cast<XMatSliderStateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void XMatSliderStateTransition::onTransition(QEvent *)
{
}
