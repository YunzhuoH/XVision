#include "XMatComboBox_internal.h"
#include <QPainter>
#include <QIcon>
#include <QTransform>
#include "XMatComboBox.h"

/*!
 *  \class XMatComboBoxIcon
 *  \internal
 */

XMatComboBoxIcon::XMatComboBoxIcon(const QIcon &icon, XMatComboBox *parent)
    : QWidget(parent),
      m_comboBox(parent),
      m_color(Qt::black),
      m_icon(icon),
      m_iconSize(12),
      m_opacity(1.0)
{
    Q_ASSERT(parent);

    setAttribute(Qt::WA_TransparentForMouseEvents);
}

XMatComboBoxIcon::~XMatComboBoxIcon()
{
}

QSize XMatComboBoxIcon::sizeHint() const
{
    return QSize(m_iconSize, m_iconSize);
}

void XMatComboBoxIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(m_opacity);

    QPixmap pixmap = icon().pixmap(12, 12);

    if (!pixmap.isNull())
    {
        const qreal p = static_cast<qreal>((height()-m_iconSize)/2+2);
        const qreal z = m_iconSize/12;

        QTransform t;
        t.translate(width()-14, p);
        t.scale(z, z);
        painter.setTransform(t);

        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), color());
        painter.drawPixmap(0, 0, pixmap);
    }
}
