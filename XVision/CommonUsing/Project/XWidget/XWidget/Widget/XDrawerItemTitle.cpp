#include "XDrawerItemTitle_p.h"
#include "XDrawerItemWidget.h"
#include "XWidgetItem_p.h"
#include "XUtil_p.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

struct XDrawerItemTitle::Impl
{
    bool expand { false };
    bool pressed { false };
    QHBoxLayout* layout { nullptr };
    QHBoxLayout* widgetLayout { nullptr };
    QList<XWidgetItemPtr> items;
    XDrawerItemWidget* treeItem { nullptr };
    QSize iconSize { 16, 16 };
};

XDrawerItemTitle::XDrawerItemTitle(XDrawerItemWidget* parent) : QPushButton(parent), m_impl(std::make_unique<Impl>())
{
    m_impl->treeItem = parent;
    m_impl->layout   = new QHBoxLayout(this);
    m_impl->layout->setContentsMargins(0, 0, 0, 0);
    m_impl->layout->setSpacing(0);
    m_impl->layout->addStretch(1);
    m_impl->widgetLayout = new QHBoxLayout;
    m_impl->widgetLayout->setContentsMargins(0, 0, 0, 0);
    m_impl->widgetLayout->setSpacing(0);
    m_impl->layout->addLayout(m_impl->widgetLayout);
    m_impl->widgetLayout->setAlignment(Qt::AlignRight);
}

XDrawerItemTitle::~XDrawerItemTitle() {}

void XDrawerItemTitle::setExpand(bool expand)
{
    m_impl->expand = expand;
    if (isVisible())
        update();
}

bool XDrawerItemTitle::isExpand() const { return m_impl->expand; }

void XDrawerItemTitle::insertAction(int index, QAction* action)
{
    auto before = actionAt(index);
    QWidget::insertAction(before, action);
}

QAction* XDrawerItemTitle::actionAt(int index) const
{
    if (index < 0)
        return nullptr;
    if (m_impl->items.size() > index)
    {
        return m_impl->items.at(index)->action();
    }
    return nullptr;
}

int XDrawerItemTitle::indexOf(QAction* action) const
{
    auto item = XUtil::find(action, m_impl->items);
    return m_impl->items.indexOf(item);
}

void XDrawerItemTitle::setIconSize(const QSize& size)
{
    m_impl->iconSize = size;
    emit iconSizeChanged(m_impl->iconSize);
}

const QSize& XDrawerItemTitle::iconSize() const { return m_impl->iconSize; }

void XDrawerItemTitle::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter p(this);
    QStyleOptionButton opt;
    this->initStyleOption(&opt);
    opt.text.clear();
    style()->drawControl(QStyle::CE_PushButton, &opt, &p, this);

    QStyleOptionViewItem itemOpt;
    itemOpt.initFrom(this);
    auto indent = style()->pixelMetric(QStyle::PM_TreeViewIndentation, &itemOpt, this);
    do
    {
        if (!m_impl->treeItem->widget())
            break;
        itemOpt.rect             = QRect(0, 0, indent, height());
        itemOpt.viewItemPosition = QStyleOptionViewItem::Beginning;
        itemOpt.state            = QStyle::State_Children;
        if (m_impl->expand)
            itemOpt.state |= QStyle::State_Open;
        style()->drawPrimitive(QStyle::PE_IndicatorBranch, &itemOpt, &p, this);
    } while (false);
    {
        auto rect = QRect(opt.rect.left() + indent, opt.rect.top(), opt.rect.width() - 40, opt.rect.height());
        QTextOption to;
        to.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        p.save();
        p.setPen(opt.palette.windowText().color());
        p.drawText(rect, text(), to);
        p.restore();
    }
}

void XDrawerItemTitle::actionEvent(QActionEvent* event)
{
    if (event->type() == QEvent::ActionAdded)
    {
        XWidgetItemPtr item = std::make_shared<XWidgetItem>(event->action(), Qt::Horizontal, m_impl->iconSize, this);
        connect(this, &XDrawerItemTitle::iconSizeChanged, item.get(), &XWidgetItem::iconSizeChanged);
        XUtil::addItem(item, m_impl->items, event->before(), m_impl->widgetLayout);
    }
    else if (event->type() == QEvent::ActionRemoved)
    {
        XUtil::removeItem(event->action(), m_impl->items, m_impl->widgetLayout);
    }
}
