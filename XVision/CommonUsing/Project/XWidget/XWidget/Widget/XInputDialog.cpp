#include "XInputDialog.h"
#include "XTitleBar.h"
#ifdef Q_OS_WIN
#include "XFramelessDelegate_win.h"
#else
#include "XFramelessDelegate_p.h"
#endif

#include "private/qwidget_p.h"
#include <QApplication>
#include <QEvent>
#include <QLabel>
#include <QStyle>
#include <QVBoxLayout>

struct XInputDialog::Impl
{
    XTitleBar* title { nullptr };
#ifdef Q_OS_WIN
    XWinFramelessDelegate* delegate { nullptr };
#else
    XFramelessDelegate* delegate { nullptr };
#endif
    QVBoxLayout* layout { nullptr };
    QLayout* mainLayout { nullptr };
};

/*!
    \class      XInputDialog
    \brief      功能与QInputDialog相同，实现了XWidget的窗口风格.
    \inherits   QInputDialog
    \ingroup    XWidget
    \inmodule   XWidget
    \inheaderfile XInputDialog.h
*/

/*!
    \brief      构造函数 \a parent, \a flags.
*/
XInputDialog::XInputDialog(QWidget* parent, Qt::WindowFlags flags) : QInputDialog(parent, flags), m_impl(std::make_unique<Impl>())
{
    sizeHint();
    m_impl->layout = new QVBoxLayout;
    m_impl->layout->setContentsMargins(0, 0, 0, 0);
    m_impl->title = new XTitleBar(this);
    m_impl->title->setObjectName("xDialogTitleBar");
    m_impl->layout->addWidget(m_impl->title, 0);
    {
        m_impl->mainLayout = qobject_cast<QVBoxLayout*>(this->layout());
        auto w             = new QWidget(this);
        w->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        w->setLayout(m_impl->mainLayout);
        m_impl->mainLayout->setParent(w);
        auto style = this->style();
        m_impl->mainLayout->setContentsMargins(style->pixelMetric(QStyle::PM_LayoutLeftMargin),
                                               style->pixelMetric(QStyle::PM_LayoutTopMargin),
                                               style->pixelMetric(QStyle::PM_LayoutRightMargin),
                                               style->pixelMetric(QStyle::PM_LayoutBottomMargin));
        m_impl->layout->addWidget(w, 1);
    }
    setLayout(m_impl->layout);
#ifdef Q_OS_WIN
    m_impl->delegate = new XWinFramelessDelegate(this, m_impl->title);
#else
    m_impl->delegate = new XFramelessDelegate(this, m_impl->title);
    setWindowFlag(Qt::Dialog);
#endif
    setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
}

/*!
    \brief      析构函数.
*/
XInputDialog::~XInputDialog() {}

/*!
    \brief      设置标题栏 \a titleBar.
    \sa         titleBar, removeTitleBar
*/
void XInputDialog::setTitleBar(XTitleBar* titleBar)
{
    if (m_impl->title)
    {
        m_impl->layout->replaceWidget(m_impl->title, titleBar);
        delete m_impl->title;
    }
    else
    {
        m_impl->layout->insertWidget(0, titleBar);
    }
    m_impl->delegate->addMoveBar(titleBar);
    m_impl->title = titleBar;
}

/*!
    \brief      返回标题栏.
    \sa         setTitleBar, removeTitleBar
*/
XTitleBar* XInputDialog::titleBar() const { return m_impl->title; }

/*!
    \brief      移除标题栏.
    \sa         setTitleBar, titleBar
*/
void XInputDialog::removeTitleBar()
{
    if (m_impl->title)
    {
        delete m_impl->title;
        m_impl->title = nullptr;
    }
}

/*!
    \brief      弹出显示一个单行文本输入窗口，并返回输入的字符串，
                父窗口为 \a parent,
                标题栏为 \a title,
                显示信息为 \a label,
                显示模式为 \a echo,
                显示文本为 \a text,
                是否点击确定按钮 \a ok,
                窗口标志位为 \a flags,
                输入法为 \a inputMethodHints.
*/
QString XInputDialog::getText(const QString& title,
                              const QString& label,
                              QWidget* parent,
                              QLineEdit::EchoMode echo,
                              const QString& text,
                              bool* ok,
                              Qt::WindowFlags flags,
                              Qt::InputMethodHints inputMethodHints)
{
    XInputDialog dlg(parent, flags);
    dlg.setWindowTitle(title);
    dlg.setLabelText(label);
    dlg.setTextValue(text);
    dlg.setTextEchoMode(echo);
    dlg.setInputMethodHints(inputMethodHints);

    const int ret = dlg.exec();
    if (ok)
        *ok = !!ret;
    if (ret)
    {
        return dlg.textValue();
    }
    else
    {
        return QString();
    }
}

/*!
    \brief      弹出显示一个多行文本输入窗口，并返回输入的字符串，
                父窗口为 \a parent,
                标题栏为 \a title,
                显示信息为 \a label,
                显示文本为 \a text,
                是否点击确定按钮 \a ok,
                窗口标志位为 \a flags,
                输入法为 \a inputMethodHints.
*/
QString XInputDialog::getMultiLineText(const QString& title,
                                       const QString& label,
                                       QWidget* parent,
                                       const QString& text,
                                       bool* ok,
                                       Qt::WindowFlags flags,
                                       Qt::InputMethodHints inputMethodHints)
{
    XInputDialog dialog(parent, flags);
    dialog.setOptions(QInputDialog::UsePlainTextEditForTextInput);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setTextValue(text);
    dialog.setInputMethodHints(inputMethodHints);

    const int ret = dialog.exec();
    if (ok)
        *ok = !!ret;
    if (ret)
    {
        return dialog.textValue();
    }
    else
    {
        return QString();
    }
}

/*!
    \brief      弹出显示一个 ComboBox 选择窗口，并返回选中的字符串，
                父窗口为 \a parent,
                标题栏为 \a title,
                显示信息为 \a label,
                候选项目为 \a items,
                当前显示项为 \a current,
                是否可编辑 \a editable,
                是否点击确定按钮 \a ok,
                窗口标志位为 \a flags,
                输入法为 \a inputMethodHints.
*/
QString XInputDialog::getItem(const QString& title,
                              const QString& label,
                              const QStringList& items,
                              QWidget* parent,
                              int current,
                              bool editable,
                              bool* ok,
                              Qt::WindowFlags flags,
                              Qt::InputMethodHints inputMethodHints)
{
    QString text(items.value(current));

    XInputDialog dialog(parent, flags);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setComboBoxItems(items);
    dialog.setTextValue(text);
    dialog.setComboBoxEditable(editable);
    dialog.setInputMethodHints(inputMethodHints);

    const int ret = dialog.exec();
    if (ok)
        *ok = !!ret;
    if (ret)
    {
        return dialog.textValue();
    }
    else
    {
        return text;
    }
}

/*!
    \brief      弹出显示一个整数输入窗口，并返回输入的值，
                父窗口为 \a parent,
                标题栏为 \a title,
                显示信息为 \a label,
                值为 \a value,
                最小值为 \a minValue,
                最大值为 \a maxValue,
                步进为 \a step,
                是否点击确定按钮 \a ok,
                窗口标志位为 \a flags.
*/
int XInputDialog::getInt(const QString& title,
                        const QString& label,
                        QWidget* parent,
                        int value,
                        int minValue,
                        int maxValue,
                        int step,
                        bool* ok,
                        Qt::WindowFlags flags)
{
    XInputDialog dialog(parent, flags);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setIntRange(minValue, maxValue);
    dialog.setIntValue(value);
    dialog.setIntStep(step);

    const int ret = dialog.exec();
    if (ok)
        *ok = !!ret;
    if (ret)
    {
        return dialog.intValue();
    }
    else
    {
        return value;
    }
}

/*!
    \brief      弹出显示一个浮点数输入窗口，并返回输入的值，
                父窗口为 \a parent,
                标题栏为 \a title,
                显示信息为 \a label,
                值为 \a value,
                最小值为 \a minValue,
                最大值为 \a maxValue,
                保留小数位为 \a decimals,
                是否点击确定按钮 \a ok,
                窗口标志位为 \a flags,
                步进为 \a step.
*/
double XInputDialog::getDouble(const QString& title,
                               const QString& label,
                               QWidget* parent,
                               double value,
                               double minValue,
                               double maxValue,
                               int decimals,
                               bool* ok,
                               Qt::WindowFlags flags,
                               double step)
{
    XInputDialog dialog(parent, flags);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setDoubleDecimals(decimals);
    dialog.setDoubleRange(minValue, maxValue);
    dialog.setDoubleValue(value);
    dialog.setDoubleStep(step);

    const int ret = dialog.exec();
    if (ok)
        *ok = !!ret;
    if (ret)
        return dialog.doubleValue();
    else
        return value;
}

/*!
    \reimp
*/
void XInputDialog::hideEvent(QHideEvent*)
{
    auto closeBtn = m_impl->title->findChild<QWidget*>("closeBtn");
    if (closeBtn)
    {
        auto e = new QEvent(QEvent::Type::Leave);
        qApp->sendEvent(closeBtn, e);
    }
}

/*!
    \reimp
*/
void XInputDialog::showEvent(QShowEvent* e)
{
    m_impl->layout->setSizeConstraint(m_impl->mainLayout->sizeConstraint());
    QInputDialog::showEvent(e);
}

/*!
    \reimp
*/
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
bool XInputDialog::nativeEvent(const QByteArray& eventType, void* message, long* result)
#else
bool XInputDialog::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
#endif
{
#ifdef Q_OS_WIN
    if (!m_impl->delegate)
        return QInputDialog::nativeEvent(eventType, message, result);
    if (!m_impl->delegate->nativeEvent(eventType, message, result))
        return QInputDialog::nativeEvent(eventType, message, result);
    else
        return true;
#else
    return QInputDialog::nativeEvent(eventType, message, result);
#endif
}
