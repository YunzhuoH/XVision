#include "XMatFlatButtonStateTransition.h"

XMatFlatButtonStateTransition::XMatFlatButtonStateTransition(XMatFlatButtonStateTransitionType type)
    : m_type(type)
{
}

bool XMatFlatButtonStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    XMatFlatButtonStateTransitionEvent *transition = static_cast<XMatFlatButtonStateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void XMatFlatButtonStateTransition::onTransition(QEvent *)
{
}
