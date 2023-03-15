#include "XUserButton_p.h"

#include <QPainter>
#include <QStyleOption>

constexpr int Space = 5;

struct XUserButton::Impl
{
};

XUserButton::XUserButton(QWidget* parent) : XToolButton(parent), m_impl(std::make_unique<Impl>()) {}

XUserButton::~XUserButton() {}

void XUserButton::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);

    opt.text = "";
    opt.icon = QIcon();
    this->style()->drawComplexControl(QStyle::CC_ToolButton, &opt, &p, this);

    QIcon::State state = opt.state & QStyle::State_On ? QIcon::On : QIcon::Off;
    QIcon::Mode mode;
    if (!(opt.state & QStyle::State_Enabled))
        mode = QIcon::Disabled;
    else if ((opt.state & QStyle::State_MouseOver) && (opt.state & QStyle::State_AutoRaise))
        mode = QIcon::Active;
    else
        mode = QIcon::Normal;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    const auto& pm = this->icon().pixmap(opt.rect.size().boundedTo(opt.iconSize), this->devicePixelRatioF(), mode, state);
#else
    const auto& pm = this->icon().pixmap(this->windowHandle(), opt.rect.size().boundedTo(opt.iconSize), mode, state);
#endif
    this->style()->drawItemPixmap(&p, doIconRect(opt), Qt::AlignCenter, pm);
    this->style()->drawItemText(&p, doTextRect(opt), Qt::AlignCenter, opt.palette, opt.state.testFlag(QStyle::State_Enabled), this->text());
}

QSize XUserButton::sizeHint() const
{
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    const auto& rect = this->style()->subElementRect(QStyle::SE_FrameContents, &opt, this);
    auto margin      = this->width() - rect.width();
    auto width       = doTextRect(opt).width() + doIconRect(opt).width() + margin + Space;
    return QSize(width, -1);
}

QSize XUserButton::minimumSizeHint() const { return sizeHint(); }

QRect XUserButton::doTextRect(const QStyleOptionToolButton& opt) const
{
    const auto& rect    = this->style()->subElementRect(QStyle::SE_FrameContents, &opt, this);
    auto&& boundingRect = opt.fontMetrics.boundingRect(rect, Qt::TextDontClip, this->text());
    boundingRect.moveLeft(this->iconSize().width() + Space + rect.left());
    boundingRect.setHeight(std::min(rect.height(), boundingRect.height()));
    boundingRect.setTop(rect.top());
    boundingRect.setBottom(rect.bottom());
    return boundingRect;
}

QRect XUserButton::doIconRect(const QStyleOptionToolButton& opt) const
{
    const auto& rect = this->style()->subElementRect(QStyle::SE_FrameContents, &opt, this);
    return QRect(rect.left(), rect.top(), iconSize().width(), rect.height());
}
