#include "XMatSuspendWidget_internal.h"
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include <QStackedLayout>
#include "XMatSuspendWidget.h"

/*!
 *  \class XMatSuspendWidgetProxy
 *  \internal
 */

XMatSuspendWidgetProxy::XMatSuspendWidgetProxy(
        XMatSuspendWidgetWindow *source,
        QStackedLayout         *layout,
        XMatSuspendWidget       *widget,
        QWidget                *parent)
    : QWidget(parent),
      m_source(source),
      m_layout(layout),
      m_widget(widget),
      m_opacity(0),
      m_mode(Transparent)
{
}

XMatSuspendWidgetProxy::~XMatSuspendWidgetProxy()
{
}

void XMatSuspendWidgetProxy::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_mode = SemiTransparent;
    update();
    m_widget->update();
}


void XMatSuspendWidgetProxy::makeOpaque()
{
    m_widget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    m_layout->setCurrentIndex(0);
    m_opacity = 1.0;
    m_mode = Opaque;
    update();
}

void XMatSuspendWidgetProxy::makeTransparent()
{
    m_opacity = 0.0;
    m_mode = Transparent;
    update();
}

QSize XMatSuspendWidgetProxy::sizeHint() const
{
    return m_source->sizeHint();
}

bool XMatSuspendWidgetProxy::event(QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Move == type || QEvent::Resize == type) {
        m_source->setGeometry(geometry());
    }
    return QWidget::event(event);
}

void XMatSuspendWidgetProxy::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    if (Transparent == m_mode) {
        return;
    } else if (Opaque != m_mode) {
        painter.setOpacity(m_opacity);
    }
    QPixmap pm = m_source->grab(m_source->rect());
    painter.drawPixmap(0, 0, pm);
}

/*!
 *  \class XMatSuspendWidgetWindow
 *  \internal
 */

XMatSuspendWidgetWindow::XMatSuspendWidgetWindow(
        XMatSuspendWidget *widget,
        QWidget          *parent)
    : QWidget(parent),
      m_widget(widget)
{
}

XMatSuspendWidgetWindow::~XMatSuspendWidgetWindow()
{
}

void XMatSuspendWidgetWindow::setOffset(int offset)
{
    QMargins margins = m_widget->layout()->contentsMargins();
    margins.setBottom(offset);
    m_widget->layout()->setContentsMargins(margins);
}

int XMatSuspendWidgetWindow::offset() const
{
    return m_widget->layout()->contentsMargins().bottom();
}

void XMatSuspendWidgetWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawRect(rect());
}
