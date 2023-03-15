#include "XSeparator_p.h"

#include <QPainter>

XSeparator::XSeparator(Qt::Orientation orientation, QWidget* parent) : QWidget(parent), m_orientation(orientation)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

XSeparator::~XSeparator() {}

Qt::Orientation XSeparator::orientation() const { return m_orientation; }

QSize XSeparator::sizeHint() const
{
    QStyleOption opt;
    initStyleOption(&opt);
    const int extent = style()->pixelMetric(QStyle::PM_ToolBarSeparatorExtent, &opt, parentWidget());
    return QSize(extent, extent);
}

void XSeparator::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    initStyleOption(&opt);
    style()->drawPrimitive(QStyle::PE_IndicatorToolBarSeparator, &opt, &p, parentWidget());
}

void XSeparator::initStyleOption(QStyleOption* opt) const
{
    opt->initFrom(this);
    if (orientation() == Qt::Horizontal)
        opt->state |= QStyle::State_Horizontal;
    const auto& rect = style()->subElementRect(QStyle::SE_FrameContents, opt, this);
    if (rect.isValid())
    {
        opt->rect = rect;
    }
}

void XSeparator::setOrientation(Qt::Orientation orientation) { m_orientation = orientation; }
