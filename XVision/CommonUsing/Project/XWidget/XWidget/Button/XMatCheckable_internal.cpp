#include "XMatCheckable_internal.h"
#include <QPainter>
#include <QIcon>
#include <QTransform>
#include "XMatCheckable.h"

/*!
 *  \class XMatCheckableIcon
 *  \internal
 */

XMatCheckableIcon::XMatCheckableIcon(const QIcon &icon, XMatCheckable *parent)
    : QWidget(parent),
      m_checkable(parent),
      m_color(Qt::black),
      m_icon(icon),
      m_iconSize(24),
      m_opacity(1.0)
{
    Q_ASSERT(parent);

    setAttribute(Qt::WA_TransparentForMouseEvents);
}

XMatCheckableIcon::~XMatCheckableIcon()
{
}

QSize XMatCheckableIcon::sizeHint() const
{
    return QSize(m_iconSize, m_iconSize);
}

void XMatCheckableIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(m_opacity);

    QPixmap pixmap = icon().pixmap(24, 24);

    if (!pixmap.isNull())
    {
        const qreal p = static_cast<qreal>((height())-m_iconSize)/2;
        const qreal z = m_iconSize/24;

        QTransform t;
        if (XMatCheckable::LabelPositionLeft == m_checkable->labelPosition()) {
            t.translate(width()-24, p);
        } else {
            t.translate(0, p);
        }
        t.scale(z, z);
        painter.setTransform(t);

        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), color());
        painter.drawPixmap(0, 0, pixmap);
    }
}
