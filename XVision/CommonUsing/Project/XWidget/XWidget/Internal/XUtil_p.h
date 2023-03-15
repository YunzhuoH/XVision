#pragma once

#include <QAction>

#include <memory>

class XWidgetItem;
typedef std::shared_ptr<XWidgetItem> XWidgetItemPtr;

namespace XUtil
{
XWidgetItemPtr find(QAction* action, const QList<XWidgetItemPtr>& items);
XWidgetItemPtr find(QWidget* widget, const QList<XWidgetItemPtr>& items);

template<class Layout, class Item>
void addItem(Item item, QList<Item>& items, QAction* before, Layout* layout)
{
    auto it    = std::find_if(items.begin(), items.end(), [=](Item item) { return item->action() == before; });
    it         = items.insert(it, item);
    auto index = items.indexOf(*it);
    layout->insertWidget(index, item->widget());
    if (item->isCustomWidget())
    {
        item->widget()->setVisible(item->action()->isVisible());
    }
};

template<class Layout, class Item>
void removeItem(QAction* action, QList<Item>& items, Layout* layout)
{
    auto item = XUtil::find(action, items);
    items.removeOne(item);
    layout->takeAt(layout->indexOf(item->widget()));
}
void releaseHover(QWidget* w);

} // namespace Util
