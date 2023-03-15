#include "XDrawerWidget.h"
#include "XDrawerItemWidget.h"

#include <QDebug>
#include <QPainter>
#include <QSplitter>
#include <QStyleOption>
#include <QVBoxLayout>

#include <algorithm>

struct XDrawerWidget::Impl
{
    QSplitter* splitter { nullptr };
    bool exclusive { false };
    bool resizeLator { false };
    QList<int> sizes;
    QSize iconSize { 16, 16 };
};

/*!
    \class      XDrawerWidget
    \brief      抽屉窗口类.
    \inherits   QWidget
    \ingroup    XWidget
    \inmodule   XWidget
    \inheaderfile XDrawerWidget.h

    \b          {抽屉窗口的截图:}
    \image      XDrawerWidgetDetail.png
*/

/*!
    \property   XDrawerWidget::exclusive
    \brief      该属性表示抽屉窗口的各项展开状态是否互斥.
*/

/*!
    \fn         void XDrawerWidget::itemExpandChanged(XDrawerItemWidget* item, bool expand)
    \brief      抽屉项 \a item 的展开状态 \a expand 发生变化时发送该信号.
    \sa         itemTitleClicked
*/

/*!
    \fn         void XDrawerWidget::itemTitleClicked(XDrawerItemWidget* item, bool expand)
    \brief      抽屉项 \a item 的标题被点击时发送该信号 \a expand.
    \sa         itemExpandChanged
*/

/*!
    \fn         void XDrawerWidget::iconSizeChanged(const QSize& size);
    \brief      当Action的图标大小发生改变时发送该信号 \a size.
    \sa         setIconSize
*/

/*!
    \brief      构造一个父窗口为 \a parent 的抽屉窗口对象.
*/
XDrawerWidget::XDrawerWidget(QWidget* parent) : QWidget(parent), m_impl(std::make_unique<Impl>())
{
    m_impl->splitter = new QSplitter(this);
    m_impl->splitter->setHandleWidth(0);
    m_impl->splitter->setOrientation(Qt::Vertical);
    m_impl->splitter->setChildrenCollapsible(false);
    m_impl->splitter->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_impl->splitter);
    layout->setContentsMargins(0, 0, 0, 0);
    qRegisterMetaType<XDrawerItemWidget*>("XDrawerItemWidget*");
}

/*!
    \brief      销毁该抽屉窗口对象.
*/
XDrawerWidget::~XDrawerWidget() {}

/*!
    \brief      添加并返回一个标题为 \a title 容纳窗口为 \a widget 的抽屉项.
    \sa         insertWidget, removeItem
*/
XDrawerItemWidget* XDrawerWidget::addWidget(const QString& title, QWidget* widget) { return insertWidget(count(), title, widget); }

/*!
    \brief      在 \a index 位置插入并返回一个标题为 \a title 容纳窗口为 \a widget 的抽屉项.
    \sa         addWidget, removeItem
*/
XDrawerItemWidget* XDrawerWidget::insertWidget(int index, const QString& title, QWidget* widget)
{
    auto item = new XDrawerItemWidget(title, this);
    item->setIconSize(m_impl->iconSize);
    connect(item, &XDrawerItemWidget::expandChanged, this, &XDrawerWidget::onItemExpand);
    connect(item, &XDrawerItemWidget::titleClicked, this, &XDrawerWidget::onItemClicked);
    connect(this, &XDrawerWidget::iconSizeChanged, item, &XDrawerItemWidget::setIconSize);
    item->setWidget(widget);
    m_impl->splitter->insertWidget(index, item);
    m_impl->sizes = m_impl->splitter->sizes();
    item->installEventFilter(this);
    doResize();
    return item;
}

/*!
    \brief      移除给予的抽屉项 \a item.
    \sa         addWidget, insertWidget
*/
void XDrawerWidget::removeItem(XDrawerItemWidget* item) { delete item; }

/*!
    \brief      返回抽屉项 \a item 所在的位置.
    \sa         item
*/
int XDrawerWidget::indexOf(XDrawerItemWidget* item) const { return m_impl->splitter->indexOf(item); }

/*!
    \brief      返回 \a index 位置的抽屉项.
    \sa         indexOf
*/
XDrawerItemWidget* XDrawerWidget::item(int index) const
{
    return qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(index));
}

/*!
    \brief      返回抽屉项数量.
*/
int XDrawerWidget::count() const { return m_impl->splitter->count(); }

/*!
    \brief      设置抽屉项的展开状态是否互斥 \a exclusive.
    \sa         exclusive()
*/
void XDrawerWidget::setExclusive(bool exclusive) { m_impl->exclusive = exclusive; }

/*!
    \brief      返回抽屉项的展开状态是否互斥.
    \sa         setExclusive
*/
bool XDrawerWidget::exclusive() const { return m_impl->exclusive; }

/*!
    \brief      设置各抽屉项的大小 \a sizes.
\*/
void XDrawerWidget::setSizes(const QList<int>& sizes)
{
    m_impl->sizes = sizes;
    for (int i = 0; i < sizes.size(); i++)
    {
        auto item = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
        if (item)
        {
            item->setSuggestSize(sizes[i]);
        }
    }
    if (isVisible())
        m_impl->splitter->setSizes(sizes);
    else
        m_impl->resizeLator = true;
}

/*!
    \brief      设置Action的图标大小 \a size.
    \sa         iconSize
*/
void XDrawerWidget::setIconSize(const QSize& size)
{
    m_impl->iconSize = size;
    emit iconSizeChanged(size);
}

/*!
    \brief      返回Action的图标大小.
    \sa         setIconSize
*/
const QSize& XDrawerWidget::iconSize() const { return m_impl->iconSize; }
/*!
    \brief      计算各抽屉项的大小.
*/
void XDrawerWidget::doResize()
{
    auto sizes = m_impl->splitter->sizes();

    if (isAllCollapsed())
    {
        for (int i = 0; i < sizes.size(); i++)
        {
            auto w   = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
            sizes[i] = w->minimumSizeHint().height();
        }
        sizes.last() = this->height();
        m_impl->splitter->setSizes(sizes);
        return;
    }

    for (int i = 0; i < sizes.size(); i++)
    {
        auto w = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
        if (w)
        {
            if (!w->isExpand())
            {
                auto h   = w->minimumSizeHint().height();
                sizes[i] = h;
            }
        }
    }
    for (int i = sizes.size() - 1; i >= 0; i--)
    {
        auto w = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
        if (w)
        {
            if (w->isExpand())
            {
                sizes[i] += m_impl->splitter->height() - this->totalSize(sizes);
                break;
            }
        }
    }

    m_impl->splitter->setSizes(sizes);
}

/*!
    \brief      响应抽屉项展开状态 \a expand.
    \sa         onItemClicked
*/
void XDrawerWidget::onItemExpand(bool expand)
{
    auto item = qobject_cast<XDrawerItemWidget*>(sender());
    if (item && expand && m_impl->exclusive)
    {
        for (int i = 0; i < m_impl->splitter->count(); i++)
        {
            auto it = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
            if (it && it != item)
            {
                it->setExpand(false);
            }
        }
    }
    if (item)
    {
        emit itemExpandChanged(item, expand);
    }
}

/*!
    \brief      响应抽屉项标题点击信号 \a expand.
    \sa         onItemExpand
*/
void XDrawerWidget::onItemClicked(bool expand)
{
    auto item = qobject_cast<XDrawerItemWidget*>(sender());
    if (item)
    {
        m_impl->sizes = this->m_impl->splitter->sizes();
        emit itemTitleClicked(item, expand);
    }
}

/*!
    \brief      展开所有抽屉项.
    \sa         collapseAll()
*/
void XDrawerWidget::expandAll()
{
    for (int i = 0; i < count(); i++)
    {
        item(i)->setExpand(true);
    }
}

/*!
    \brief      关闭所有抽屉项.
    \sa         expandAll()
*/
void XDrawerWidget::collapseAll()
{
    for (int i = 0; i < count(); i++)
    {
        item(i)->setExpand(false);
    }
}

/*!
    \brief      返回所有的抽屉项是否都关闭了.
*/
bool XDrawerWidget::isAllCollapsed() const
{
    for (int i = 0; i < m_impl->splitter->count(); i++)
    {
        auto w = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
        if (w->isExpand())
            return false;
    }
    return true;
}

/*!
    \brief      返回 \a sizes 的总和.
*/
int XDrawerWidget::totalSize(const QList<int>& sizes) const { return std::accumulate(sizes.begin(), sizes.end(), 0); }

/*!
    \reimp
*/
void XDrawerWidget::showEvent(QShowEvent* event)
{
    if (m_impl->resizeLator)
    {
        m_impl->splitter->setSizes(m_impl->sizes);
        m_impl->resizeLator = false;
    }
    QWidget::showEvent(event);
}

/*!
    \brief      响应抽屉项 \a item 的展开状态变化 \a expand.
*/
void XDrawerWidget::childExpandChanged(XDrawerItemWidget* item, bool expand)
{
    if (expand)
    {
        if (item)
        {
            int index = m_impl->splitter->indexOf(item);
            if (index != -1)
            {
                QList<int> sizes = m_impl->sizes;
                {
                    int i = sizes.size();
                    while (sizes.size() < m_impl->splitter->count())
                        sizes << m_impl->splitter->widget(i)->height();
                }
                for (int i = 0; i < m_impl->splitter->count(); i++)
                {
                    m_impl->splitter->setStretchFactor(i, i == index ? 1 : 0);
                }
                auto total1  = totalSize(sizes);
                sizes[index] = item->suggestSize();
                auto total2  = totalSize(sizes);
                int s        = total2 - total1;
                for (int i = index + 1; i < sizes.size(); i++)
                {
                    if (s <= 0)
                        break;
                    auto item = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
                    if (item->isExpand())
                    {
                        auto sub = item->height() - item->minimumSizeHint().height();
                        auto h   = s >= sub ? sub : s;
                        s -= h;
                        sizes[i] -= h;
                    }
                }

                for (int i = index - 1; i >= 0; i--)
                {
                    if (s <= 0)
                        break;
                    auto item = qobject_cast<XDrawerItemWidget*>(m_impl->splitter->widget(i));
                    if (item->isExpand())
                    {
                        auto sub = item->height() - item->minimumSizeHint().height();
                        auto h   = s >= sub ? sub : s;
                        s -= h;
                        sizes[i] -= h;
                    }
                }

                m_impl->splitter->setSizes(sizes);
            }
        }
    }
    doResize();
}
