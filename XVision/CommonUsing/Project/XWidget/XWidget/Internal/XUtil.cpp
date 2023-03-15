#include "XWidgetItem_p.h"
#include "XUtil_p.h"
#include <QEvent>
#include <QApplication>

XWidgetItemPtr XUtil::find(QAction* action, const QList<XWidgetItemPtr>& items)
{
    for (auto& item : items)
    {
        if (item->action() == action)
            return item;
    }
    return nullptr;
}

XWidgetItemPtr XUtil::find(QWidget* widget, const QList<XWidgetItemPtr>& items)
{
    for (auto& item : items)
    {
        if (item->widget() == widget)
            return item;
    }
    return nullptr;
}

void XUtil::releaseHover(QWidget *w)
{
    auto children = w->children();
    for (auto& child : children)
    {
        if (child->isWidgetType())
        {
            auto widget = qobject_cast<QWidget*>(child);
            if (widget)
            {
                if (widget->underMouse())
                {
                    QEvent* e = new QEvent(QEvent::Leave);
                    qApp->sendEvent(widget, e);
                    widget->repaint();
                }
                releaseHover(widget);
            }
        }
    }
}
