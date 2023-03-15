#include "XDrawerItemWidget.h"
#include "XDrawerItemTitle_p.h"
#include "XDrawerWidget.h"

#include <QScrollArea>
#include <QVBoxLayout>

struct XDrawerItemWidget::Impl
{
    XDrawerItemTitle* title { nullptr };
    QVBoxLayout* layout { nullptr };
    QScrollArea* content { nullptr };
    QWidget* widget { nullptr };
    int size = 0;
    XDrawerWidget* tree { nullptr };
};

/*!
    \class      XDrawerItemWidget
    \brief      抽屉窗口 XDrawerWidget 的抽屉项.
    \inherits   QWidget
    \ingroup    XWidget
    \inmodule   XWidget
    \inheaderfile XDrawerItemWidget.h

    \b          {抽屉窗口的截图，抽屉项为其中一栏:}
    \image      XDrawerWidgetDetail.png
*/

/*!
    \fn         void XDrawerItemW    idget::expandChanged(bool expand)
    \brief      当抽屉项的扩展状态发生变化时，发送该信号 \a expand.
    \sa         XDrawerItemWidget::titleClicked
*/

/*!
    \fn         void XDrawerItemWidget::titleClicked(bool expand)
    \brief      当抽屉项的标题栏被点击时发送该信号 \a expand.
    \sa         XDrawerItemWidget::expandChanged
*/

/*!
    \fn         void XDrawerItemWidget::iconSizeChanged(const QSize& size);
    \brief      当Action的图标大小发生改变时发送该信号 \a size.
    \sa         XDrawerItemWidget::setIconSize
*/

/*!
    \brief      构造一个标题为 \a title, 父窗口为 \a parent 的抽屉窗口.
*/
XDrawerItemWidget::XDrawerItemWidget(const QString& title, XDrawerWidget* parent)
    : QWidget(parent), m_impl(std::make_unique<Impl>())
{
    m_impl->tree   = parent;
    m_impl->layout = new QVBoxLayout(this);
    m_impl->layout->setContentsMargins(0, 0, 0, 0);
    m_impl->layout->setSpacing(0);

    m_impl->title = new XDrawerItemTitle(this);
    m_impl->title->setText(title);
    m_impl->title->setObjectName("title");

    m_impl->layout->addWidget(m_impl->title, 0);
    m_impl->content = new QScrollArea(this);
    m_impl->content->setWidgetResizable(true);
    m_impl->content->setFrameStyle(QFrame::NoFrame);
    m_impl->content->hide();
    m_impl->layout->addWidget(m_impl->content, 1);
    m_impl->title->setFixedHeight(30);

    connect(m_impl->title, &XDrawerItemTitle::clicked, this, &XDrawerItemWidget::onClicked);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_impl->layout->setAlignment(m_impl->title, Qt::AlignTop);
    setExpand(false);
}

/*!
    \brief      销毁该抽屉项对象.
*/
XDrawerItemWidget::~XDrawerItemWidget() {}

/*!
    \brief      设置抽屉项容纳的部件 \a widget.
    \sa         widget()
*/
void XDrawerItemWidget::setWidget(QWidget* widget)
{
    if (m_impl->widget)
        delete m_impl->widget;
    m_impl->widget = widget;
    m_impl->content->setWidget(widget);
    m_impl->title->update();
    if (!m_impl->widget)
        setExpand(false);
}

/*!
    \brief      返回该抽屉项容纳的部件.
    \sa         setWidget
*/
QWidget* XDrawerItemWidget::widget() const { return m_impl->widget; }

/*!
    \brief      设置抽屉项的标题 \a title.
    \sa         title()
*/
void XDrawerItemWidget::setTitle(const QString& title) { m_impl->title->setText(title); }

/*!
    \brief      返回抽屉项的标题.
    \sa         setTitle
*/
QString XDrawerItemWidget::title() const { return m_impl->title->text(); }

/*!
    \brief      返回该抽屉项的展开状态.
    \sa         setExpand
*/
bool XDrawerItemWidget::isExpand() const { return m_impl->title->isExpand(); }

/*!
    \brief      设置该抽屉项的展开状态 \a expand.
    \sa         isExpand
*/
void XDrawerItemWidget::setExpand(bool expand)
{
    if (isExpand() == expand)
        return;
    if (!m_impl->widget)
        return;
    m_impl->title->setExpand(expand);
    m_impl->content->setVisible(expand);
    if (m_impl->tree)
    {
        emit this->expandChanged(expand);
        this->metaObject()->invokeMethod(
            m_impl->tree, "childExpandChanged", Qt::QueuedConnection, Q_ARG(XDrawerItemWidget*, this), Q_ARG(bool, expand));
    }
    if (!expand)
        m_impl->size = this->height();
}

/*!
    \brief      响应标题栏点击信号.
*/
void XDrawerItemWidget::onClicked()
{
    emit(titleClicked(!isExpand()));
    if (m_impl->widget)
        setExpand(!isExpand());
}

/*!
    \reimp
*/
void XDrawerItemWidget::resizeEvent([[maybe_unused]] QResizeEvent* event)
{
    if (!isExpand())
    {
        if (m_impl->tree)
        {
            metaObject()->invokeMethod(m_impl->tree, "doResize", Qt::QueuedConnection);
        }
    }
}

/*!
    \brief      返回抽屉项的建议大小.
    \sa         setSuggestSize
*/
int XDrawerItemWidget::suggestSize() const
{
    return m_impl->size < this->minimumSizeHint().height() ? this->minimumSizeHint().height() : m_impl->size;
}

/*!
    \brief      设置抽屉项的建议大小 \a size.
    \sa         suggestSize()
*/
void XDrawerItemWidget::setSuggestSize(int size) { m_impl->size = size; }

/*!
    \overload   addAction
                在标题栏上添加一个文本为 \a text 的Action.
    \sa         XDrawerItemWidget::addAction, removeAction
*/
QAction* XDrawerItemWidget::addAction(const QString& text) { return insertAction(count(), text); }

/*!
    \brief      在标题栏上添加一个图标为 \a icon 文本为 \a text 的Action.
    \sa         insertAction, removeAction
*/
QAction* XDrawerItemWidget::addAction(const QIcon& icon, const QString& text) { return insertAction(count(), icon, text); }

/*!
    \overload   addAction
                在标题栏上添加一个图标为 \a icon 的Action.
    \sa         insertAction, removeAction
*/
QAction* XDrawerItemWidget::addAction(const QIcon& icon) { return addAction(icon, QString()); }

/*!
    \brief      在标题栏上的 \a index 位置插入一个 \a action.
    \sa         addAction, removeAction
*/
void XDrawerItemWidget::insertAction(int index, QAction* action) { m_impl->title->insertAction(index, action); }

/*!
    \overload   insertAction
                在标题栏上的 \a index 位置插入一个文本为 \a text 的Action.
    \sa         XDrawerItemWidget::insertAction, removeAction
*/
QAction* XDrawerItemWidget::insertAction(int index, const QString& text) { return insertAction(index, QIcon(), text); }

/*!
    \overload   insertAction
                在标题栏上的 \a index 位置插入一个图标为 \a icon 文本为 \a text 的Action.
    \sa         XDrawerItemWidget::insertAction, removeAction
*/
QAction* XDrawerItemWidget::insertAction(int index, const QIcon& icon, const QString& text)
{
    auto action = new QAction(icon, text, m_impl->title);
    insertAction(index, action);
    return action;
}

/*!
    \brief      移除给予的 \a action.
    \sa         addAction, insertAction
*/
void XDrawerItemWidget::removeAction(QAction* action) { m_impl->title->removeAction(action); }

/*!
    \brief      返回Action的数量.
*/
int XDrawerItemWidget::count() const { return m_impl->title->actions().size(); }

/*!
    \brief      返回 \a action 的位置.
    \sa         actionAt
*/
int XDrawerItemWidget::indexOf(QAction* action) { return m_impl->title->indexOf(action); }

/*!
    \brief      返回 \a index 位置的Action.
    \sa         indexOf
*/
QAction* XDrawerItemWidget::actionAt(int index) { return m_impl->title->actionAt(index); }

/*!
    \brief      设置Action的大小 \a size.
    \sa         iconSize
*/
void XDrawerItemWidget::setIconSize(const QSize& size)
{
    m_impl->title->setIconSize(size);
    emit iconSizeChanged(size);
}

/*!
    \brief      返回Action的大小.
    \sa         setIconSize
*/
const QSize& XDrawerItemWidget::iconSize() const { return m_impl->title->iconSize(); }
