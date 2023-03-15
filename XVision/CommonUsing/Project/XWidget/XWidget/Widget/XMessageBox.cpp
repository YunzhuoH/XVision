#include "XMessageBox.h"
#include "XTitleBar.h"

#include <QApplication>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QStyle>
#include <QVBoxLayout>

struct XMessageBox::Impl
{
    QLabel* label { nullptr };
    QLabel* iconLabel { nullptr };
    Icon icon { Icon::NoIcon };
    QDialogButtonBox* buttonBox { nullptr };
    QAbstractButton* clickedButton { nullptr };
    QAbstractButton* defaultButton { nullptr };
    QAbstractButton* escapeButton { nullptr };
};

/*!
    \class      XMessageBox
    \brief      自定义外观的消息框，用法参考 QMessageBox.
    \inherits   XFramelessDialog
    \ingroup    XWidget
    \inmodule   XWidget
    \sa         QMessageBox
    \inheaderfile XMessageBox.h
*/

/*!
    \enum       XMessageBox::ButtonRole
                按钮角色.
    \value      InvalidRole     无效按钮.
    \value      AcceptRole      点击按钮将使窗口以 Accepted 关闭，例如：“确定” 按钮.
    \value      RejectRole      点击按钮将使窗口以 Rejected 关闭，例如：“取消” 按钮.
    \value      DestructiveRole 点击按钮将取消更改并关闭弹窗，例如：“放弃更改” 按钮.
    \value      ActionRole      点击该按钮将导致对话框中的元素发生更改.
    \value      HelpRole        点击按钮请求帮助.
    \value      YesRole         类似于 “是” 按钮.
    \value      NoRole          类似于 “否” 按钮.
    \value      ApplyRole       类似于 “应用” 按钮.
    \value      ResetRole       类似于 “恢复默认” 按钮.

    \omitvalue  NRoles

    \sa         StandardButton
*/

/*!
    \enum       XMessageBox::StandardButton
                这些枚举描述了标准按钮的标志。每个按钮有一个对应的 \l ButtonRole.

    \value      Ok              “确定” 按钮，对应 \l AcceptRole.
    \value      Open            “打开” 按钮，对应 \l AcceptRole.
    \value      Save            “保存” 按钮，对应 \l AcceptRole.
    \value      Cancel          “取消” 按钮，对应 \l RejectRole.
    \value      Close           “关闭” 按钮，对应 \l RejectRole.
    \value      Discard         “放弃更改” 按钮，对应 \l DestructiveRole.
    \value      Apply           “应用” 按钮，对应 \l ApplyRole.
    \value      Reset           “重置” 按钮，对应 \l ResetRole.
    \value      RestoreDefaults “恢复默认” 按钮，对应 \l ResetRole.
    \value      Help            “帮助” 按钮，对应 \l HelpRole.
    \value      SaveAll         “全部保存” 按钮，对应 \l AcceptRole.
    \value      Yes             “是” 按钮，对应 \l YesRole.
    \value      YesToAll        “全部是” 按钮，对应 \l YesRole.
    \value      No              “否” 按钮，对应 \l NoRole.
    \value      NoToAll         “全部否” 按钮，对应 \l NoRole.
    \value      Abort           “中止” 按钮，对应 \l RejectRole.
    \value      Retry           “重试” 按钮，对应 \l AcceptRole.
    \value      Ignore          “忽略” 按钮，对应 \l AcceptRole.
    \value      NoButton        无效按钮.

    \omitvalue FirstButton
    \omitvalue LastButton

    \sa ButtonRole, standardButtons
*/

/*!
    \enum       XMessageBox::Icon
                显示图标.
    \value      NoIcon      无图标/自定义图标.
    \value      Question    询问图标.
    \value      Information 信息图标.
    \value      Warning     警告图标.
    \value      Critical    错误图标.
*/

/*!
    \property    XMessageBox::text
    \brief      消息弹窗的显示文本.
*/

/*!
    \property   XMessageBox::icon
    \brief      消息弹窗的图标.

    这些图标可以是下面的任意一个:

    \list
    \li XMessageBox::NoIcon
    \li XMessageBox::Question
    \li XMessageBox::Information
    \li XMessageBox::Warning
    \li XMessageBox::Critical
    \endlist

    默认为 XMessageBox::NoIcon.

    \sa iconPixmap
*/

/*!
    \property   XMessageBox::iconPixmap
    \brief      当前显示图标.
    \sa         icon
*/

/*!
    \property   XMessageBox::textFormat
    \brief      消息框显示的文本格式.
    \sa         setText()
*/

/*!
    \property    XMessageBox::standardButtons
    \brief      消息弹窗的按钮集合.
    \sa         addButton
*/

/*!
    \property   XMessageBox::textInteractionFlags
                指定消息框的标签应如何与用户交互输入。
*/

/*!
    \brief      构造函数 \a parent.
*/
XMessageBox::XMessageBox(QWidget* parent) : XFramelessDialog(parent), m_impl(std::make_unique<Impl>()) { init(); }

/*!
    \brief      构造函数，并指定显示图标 \a icon, 标题文本 \a title, 显示文本 \a text, 按钮集合 \a buttons, 父窗口 \a parent, 窗口风格 \a f.
*/
XMessageBox::XMessageBox(Icon icon,
                               const QString& title,
                               const QString& text,
                               StandardButtons buttons /*= NoButton */
                               ,
                               QWidget* parent /*= Q_NULLPTR */
                               ,
                               Qt::WindowFlags f /*= Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint*/)
    : XMessageBox(parent)
{
    m_impl->buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons((int)buttons));
    m_impl->label->setText(text);
    setWindowTitle(title);
    setWindowFlags(f | Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
    setIcon(icon);
}

/*!
    \brief      析构函数.
*/
XMessageBox::~XMessageBox() {}

/*!
    \brief      设置按钮集合 \a buttons.
    \sa         standardButtons()
*/
void XMessageBox::setStandardButtons(StandardButtons buttons)
{
    m_impl->buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));

    QList<QAbstractButton*> buttonList = m_impl->buttonBox->buttons();
    if (!buttonList.contains(m_impl->escapeButton))
        m_impl->escapeButton = nullptr;
    if (!buttonList.contains(m_impl->defaultButton))
        m_impl->defaultButton = nullptr;
    updateSize();
}

/*!
    \brief      返回按钮集合.
    \sa         setStandardButtons
*/
XMessageBox::StandardButtons XMessageBox::standardButtons() const
{
    return XMessageBox::StandardButtons(int(m_impl->buttonBox->standardButtons()));
}

/*!
    \brief      设置默认按钮 \a button.
    \sa         defaultButton
*/
void XMessageBox::setDefaultButton(StandardButton button)
{
    auto btn = m_impl->buttonBox->button(QDialogButtonBox::StandardButton(button));
    if (btn)
    {
        btn->setFocus();
        m_impl->defaultButton = btn;
    }
}

/*!
    \brief      返回默认按钮.
    \sa         setDefaultButton
*/
XMessageBox::StandardButton XMessageBox::defaultButton()
{
    return XMessageBox::StandardButton(m_impl->buttonBox->standardButton(m_impl->defaultButton));
}

/*!
    \brief      返回点击的按钮.
*/
QAbstractButton* XMessageBox::clickedButton() const { return m_impl->clickedButton; }

/*!
    \brief      返回按钮对应的标准按钮 \a button.
*/
XMessageBox::StandardButton XMessageBox::standardButton(QAbstractButton* button) const
{
    if (!button)
    {
        detectEscapeButton();
        return XMessageBox::StandardButton(m_impl->buttonBox->standardButton(m_impl->escapeButton));
    }
    return XMessageBox::StandardButton(m_impl->buttonBox->standardButton(button));
}

/*!
    \brief      添加按钮 \a button 并指定其角色 \a role.
    \sa         removeButton
*/
void XMessageBox::addButton(QAbstractButton* button, ButtonRole role)
{
    if (!button)
        return;
    if (m_impl->buttonBox->buttons().contains(button))
        return;
    m_impl->buttonBox->addButton(button, (QDialogButtonBox::ButtonRole)role);
}

/*!
    \brief      创建文本为 \a text 的按钮并指定其角色 \a role.
    \overload   addButton
    \sa         removeButton
*/
QPushButton* XMessageBox::addButton(const QString& text, ButtonRole role)
{
    auto btn = new QPushButton(text, this);
    addButton(btn, role);
    return btn;
}

/*!
    \brief      添加标准按钮 \a button.
    \overload   addButton
    \sa         removeButton
*/
QPushButton* XMessageBox::addButton(StandardButton button)
{
    return m_impl->buttonBox->addButton((QDialogButtonBox::StandardButton)button);
}

/*!
    \brief      移除按钮 \a button.
    \sa         addButton
*/
void XMessageBox::removeButton(QAbstractButton* button)
{
    if (!button)
        return;
    m_impl->buttonBox->removeButton(button);
}

/*!
    \brief      设置显示文本 \a text.
    \sa         text()
*/
void XMessageBox::setText(const QString& text) { m_impl->label->setText(text); }

/*!
    \brief      返回显示文本.
    \sa         setText
*/
QString XMessageBox::text() const { return m_impl->label->text(); }

/*!
    \brief      返回显示图标.
    \sa         setIcon
*/
XMessageBox::Icon XMessageBox::icon() const { return m_impl->icon; }

/*!
    \brief      设置显示图标 \a icon.
    \sa         icon()
*/
void XMessageBox::setIcon(Icon icon)
{
    m_impl->icon = icon;
    switch (icon)
    {
    case Information:
        m_impl->iconLabel->setPixmap(this->style()->proxy()->standardPixmap(QStyle::SP_MessageBoxInformation));
        break;
    case Question:
        m_impl->iconLabel->setPixmap(this->style()->proxy()->standardPixmap(QStyle::SP_MessageBoxQuestion));
        break;
    case Critical:
        m_impl->iconLabel->setPixmap(this->style()->proxy()->standardPixmap(QStyle::SP_MessageBoxCritical));
        break;
    case Warning:
        m_impl->iconLabel->setPixmap(this->style()->proxy()->standardPixmap(QStyle::SP_MessageBoxWarning));
        break;
    default:
        break;
    }
}

/*!
    \brief      返回图标.
    \sa         setIconPixmap
*/
QPixmap XMessageBox::iconPixmap() const { return m_impl->iconLabel->pixmap(Qt::ReturnByValue); }

/*!
    \brief      设置自定义的图标 \a pixmap, 并且 \l icon 将被设置为 Icon::Custom.
    \sa         iconPixmap
*/
void XMessageBox::setIconPixmap(const QPixmap& pixmap)
{
    m_impl->icon = Icon::Custom;
    m_impl->iconLabel->setPixmap(pixmap);
}

/*!
    \brief      返回文本格式.
    \sa         setTextFormat
*/
Qt::TextFormat XMessageBox::textFormat() const { return m_impl->label->textFormat(); }

/*!
    \brief      设置文本格式 \a format.
    \sa         textFormat()
*/
void XMessageBox::setTextFormat(Qt::TextFormat format) { m_impl->label->setTextFormat(format); }

/*!
    \brief      设置文本交互方式 \a flags.
    \sa         textInteractionFlags()
*/
void XMessageBox::setTextInteractionFlags(Qt::TextInteractionFlags flags) { m_impl->label->setTextInteractionFlags(flags); }

/*!
    \brief      返回文本交互方式.
    \sa         setTextInteractionFlags
*/
Qt::TextInteractionFlags XMessageBox::textInteractionFlags() const { return m_impl->label->textInteractionFlags(); }

/*!
    \brief      构造一个错误消息弹窗，并指定标题文本 \a title, 显示文本 \a text, 按钮集合 \a buttons, 默认按钮 \a defaultButton, 父窗口 \a
   parent. \sa         QMessageBox::critical
*/
XMessageBox::StandardButton XMessageBox::critical( const QString& title,
                                                   const QString& text,
                                                   QWidget* parent,
                                                   StandardButtons buttons /*= Ok */
                                                   ,
                                                   StandardButton defaultButton /*= NoButton*/)
{
    XMessageBox box(Icon::Critical, title, text, buttons, parent);
    box.setDefaultButton(defaultButton);
    box.exec();
    return box.standardButton(box.clickedButton());
}

/*!
    \brief      构造一个信息消息弹窗，并指定标题文本 \a title, 显示文本 \a text, 按钮集合 \a buttons, 默认按钮 \a defaultButton, 父窗口 \a
   parent. \sa         QMessageBox::information
*/
XMessageBox::StandardButton XMessageBox::information(const QString& title,
                                                     const QString& text,
                                                     QWidget* parent,
                                                     StandardButtons buttons /*= Ok */
                                                     ,
                                                     StandardButton defaultButton /*= NoButton*/)
{
    XMessageBox box(Icon::Information, title, text, buttons, parent);
    box.setDefaultButton(defaultButton);
    box.exec();
    return box.standardButton(box.clickedButton());
}

/*!
    \brief      构造一个询问消息弹窗，并指定标题文本 \a title, 显示文本 \a text, 按钮集合 \a buttons, 默认按钮 \a defaultButton, 父窗口 \a
   parent. \sa         QMessageBox::question
*/
XMessageBox::StandardButton XMessageBox::question(const QString& title,
                                                  const QString& text,
                                                   QWidget* parent,
                                                   StandardButtons buttons /*= StandardButtons(Yes | No) */
                                                   ,
                                                   StandardButton defaultButton /*= NoButton*/)
{
    XMessageBox box(Icon::Question, title, text, buttons, parent);
    box.setDefaultButton(defaultButton);
    box.exec();
    return box.standardButton(box.clickedButton());
}

/*!
    \brief      构造一个警告消息弹窗，并指定标题文本 \a title, 显示文本 \a text, 按钮集合 \a buttons, 默认按钮 \a defaultButton, 父窗口 \a
   parent. \sa         QMessageBox::warning
*/
XMessageBox::StandardButton XMessageBox::warning(const QString& title,
                                                 const QString& text,
                                                 QWidget* parent,
                                                 StandardButtons buttons /*= Ok */
                                                 ,
                                                 StandardButton defaultButton /*= NoButton*/)
{
    XMessageBox box(Icon::Warning, title, text, buttons, parent);
    box.setDefaultButton(defaultButton);
    box.exec();
    return box.standardButton(box.clickedButton());
}

XMessageBox::StandardButton XMessageBox::custom(const QString &title,
                                                const QString &text,
                                                const QPixmap &icon,
                                                QWidget *parent,
                                                StandardButtons buttons,
                                                StandardButton defaultButton)
{
    XMessageBox box(Icon::Custom, title, text, buttons, parent);
    box.setIconPixmap(icon);
    box.setDefaultButton(defaultButton);
    box.exec();
    return box.standardButton(box.clickedButton());
}

/*!
    \reimp
*/
void XMessageBox::showEvent(QShowEvent* event)
{
    updateSize();
#ifdef Q_OS_WIN
    setAttribute(Qt::WA_Moved, false);
#endif
    XFramelessDialog::showEvent(event);
}

/*!
    \brief      初始化.
*/
void XMessageBox::init()
{
    m_impl->label       = new QLabel(this);
    m_impl->iconLabel   = new QLabel(this);
    m_impl->buttonBox   = new QDialogButtonBox(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget());

    QHBoxLayout* msgLayout = new QHBoxLayout;
    msgLayout->addWidget(m_impl->iconLabel, 0);
    msgLayout->addWidget(m_impl->label, 1);
    msgLayout->setContentsMargins(0, 0, 0, 0);
    msgLayout->setSpacing(20);
    layout->addLayout(msgLayout);
    layout->addWidget(m_impl->buttonBox);

    connect(m_impl->buttonBox, &QDialogButtonBox::clicked, this, [=](QAbstractButton* button) { m_impl->clickedButton = button; });
    connect(m_impl->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_impl->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/*!
    \brief      返回最小布局宽度.
    \sa         updateSize
*/
int XMessageBox::layoutMinimumWidth()
{
    centralWidget()->layout()->activate();
    return centralWidget()->layout()->totalMinimumSize().width();
}

/*!
    \brief      计算大小.
    \sa         layoutMinimumWidth
*/
void XMessageBox::updateSize()
{
    if (!isVisible())
        return;

    auto screen = qApp->screenAt(QCursor::pos());
    if (!screen)
        return;
    const auto& screenSize = screen->size();

    int hardLimit = qMin(screenSize.width() - 480, 1000); // can never get bigger than this
    // on small screens allows the messagebox be the same size as the screen
    if (screenSize.width() <= 1024)
        hardLimit = screenSize.width();
#ifdef Q_OS_MAC
    int softLimit = qMin(screenSize.width() / 2, 420);
#else
    // note: ideally on windows, hard and soft limits but it breaks compat
    int softLimit = qMin(screenSize.width() / 2, 500);
#endif

    m_impl->label->setWordWrap(false); // makes the label return min size
    int width = layoutMinimumWidth();

    if (width > softLimit)
    {
        m_impl->label->setWordWrap(true);
        width = qMax(softLimit, layoutMinimumWidth());
    }

    QFontMetrics fm(QApplication::font("QMdiSubWindowTitleBar"));
    int windowTitleWidth = qMin(fm.horizontalAdvance(windowTitle()) + 50, hardLimit);
    if (windowTitleWidth > width)
        width = windowTitleWidth;

    auto layout = centralWidget()->layout();
    layout->activate();
    int height = (layout->hasHeightForWidth()) ? layout->totalHeightForWidth(width) : layout->totalMinimumSize().height();

    const auto& margins       = contentsMargins();
    const auto& layoutMargins = layout->contentsMargins();
    setFixedSize(width + margins.left() + margins.right() + layoutMargins.left() + layoutMargins.right(),
                 height + this->titleBar()->height() + margins.bottom() + margins.top() + layoutMargins.top() + layoutMargins.bottom());
}

/*!
    \brief      检测取消按钮动作.
*/
void XMessageBox::detectEscapeButton() const
{
    if (m_impl->escapeButton)
    { // escape button explicitly set
        return;
    }

    // Cancel button automatically becomes escape button
    m_impl->escapeButton = m_impl->buttonBox->button(QDialogButtonBox::Cancel);
    if (m_impl->escapeButton)
        return;

    // If there is only one button, make it the escape button
    const QList<QAbstractButton*> buttons = m_impl->buttonBox->buttons();
    if (buttons.count() == 1)
    {
        m_impl->escapeButton = buttons.first();
        return;
    }

    // if the message box has one RejectRole button, make it the escape button
    for (auto* button : buttons)
    {
        if (m_impl->buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
        {
            m_impl->escapeButton = button;
            if (m_impl->escapeButton)
                return;
        }
    }

    // if the message box has one NoRole button, make it the escape button
    for (auto* button : buttons)
    {
        if (m_impl->buttonBox->buttonRole(button) == QDialogButtonBox::NoRole)
        {
            m_impl->escapeButton = button;
            if (m_impl->escapeButton)
                return;
        }
    }
}
