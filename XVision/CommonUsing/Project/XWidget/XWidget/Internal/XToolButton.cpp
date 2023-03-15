#include "XToolButton_p.h"

#include <QAction>
#include <QEvent>
#include <QStyle>
#include <QStyleOption>
#include <QStylePainter>

struct XToolButton::Impl
{
    bool showToolTip { true };
    bool selected { false };
};

XToolButton::XToolButton(QWidget* parent) : QToolButton(parent), m_impl(std::make_unique<Impl>())
{
    connect(this,
            &QAbstractButton::toggled,
            this,
            [=](bool)
            {
                style()->unpolish(this);
                style()->polish(this);
            });
}

XToolButton::~XToolButton() {}

void XToolButton::setIcon(const QIcon& icon)
{
    if (defaultAction())
    {
        defaultAction()->setIcon(icon);
    }
    else
        QToolButton::setIcon(icon);
}

void XToolButton::setShowToolTips(bool show) { m_impl->showToolTip = show; }

bool XToolButton::showToolTips() const { return m_impl->showToolTip; }

void XToolButton::setSelected(bool select) { m_impl->selected = select; }

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
void XToolButton::initStyleOption(QStyleOptionToolButton* option) const
{
    QToolButton::initStyleOption(option);
    if (m_impl->selected)
        option->icon = this->icon().pixmap(
            iconSize(), m_impl->selected ? QIcon::Mode::Selected : QIcon::Mode::Normal, isChecked() ? QIcon::State::On : QIcon::State::Off);
}
#else
void XToolButton::paintEvent(QPaintEvent*)
{
    QStylePainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    if (m_impl->selected)
        opt.icon = this->icon().pixmap(
            iconSize(), m_impl->selected ? QIcon::Mode::Selected : QIcon::Mode::Normal, isChecked() ? QIcon::State::On : QIcon::State::Off);
    p.drawComplexControl(QStyle::CC_ToolButton, opt);
}
#endif
bool XToolButton::event(QEvent* e)
{
    if (e->type() == QEvent::ToolTip)
    {
        return m_impl->showToolTip ? QToolButton::event(e) : true;
    }
    return QToolButton::event(e);
}
