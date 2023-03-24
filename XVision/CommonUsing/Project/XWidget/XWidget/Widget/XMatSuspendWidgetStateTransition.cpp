#include "XMatSuspendWidgetStateTransition.h"

XMatSuspendWidgetStateTransition::XMatSuspendWidgetStateTransition(XMatSuspendWidgetStateTransitionType type)
    : m_type(type)
{
}

bool XMatSuspendWidgetStateTransition::eventTest(QEvent *event)
{
    if (event->type() != QEvent::Type(QEvent::User + 1)) {
        return false;
    }
    XMatSuspendWidgetStateTransitionEvent *transition = static_cast<XMatSuspendWidgetStateTransitionEvent *>(event);
    return (m_type == transition->type);
}

void XMatSuspendWidgetStateTransition::onTransition(QEvent *)
{
}
