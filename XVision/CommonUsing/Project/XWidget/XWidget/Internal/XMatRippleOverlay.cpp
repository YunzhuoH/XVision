#include "XMatRippleOverlay.h"
#include <QPainter>
#include "XMatRipple.h"

/*!
 *  \class XMatRippleOverlay
 *  \internal
 */

XMatRippleOverlay::XMatRippleOverlay(QWidget *parent)
    : XMatOverlayWidget(parent),
      m_useClip(false)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

XMatRippleOverlay::~XMatRippleOverlay()
{
}

void XMatRippleOverlay::addRipple(XMatRipple *ripple)
{
    ripple->setOverlay(this);
    m_ripples.push_back(ripple);
    ripple->start();

    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(stop()));
    connect(this, SIGNAL(destroyed(QObject*)), ripple, SLOT(deleteLater()));
}

void XMatRippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    XMatRipple *ripple = new XMatRipple(position);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void XMatRippleOverlay::removeRipple(XMatRipple *ripple)
{
    if (m_ripples.removeOne(ripple)) {
        delete ripple;
        update();
    }
}

/*!
 *  \reimp
 */
void XMatRippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (m_useClip) {
        painter.setClipPath(m_clipPath);
    }

    QList<XMatRipple *>::const_iterator i;
    for (i = m_ripples.begin(); i != m_ripples.end(); ++i) {
        paintRipple(&painter, *i);
    }
}

void XMatRippleOverlay::paintRipple(QPainter *painter, XMatRipple *ripple)
{
    const qreal radius = ripple->radius();
    const QPointF center = ripple->center();
    painter->setOpacity(ripple->opacity());
    painter->setBrush(ripple->brush());
    painter->drawEllipse(center, radius, radius);
}
