#include "XMatRipple.h"
#include "XMatRippleOverlay.h"

/*!
 *  \class XMatRipple
 *  \internal
 */

XMatRipple::XMatRipple(const QPoint &center, QObject *parent)
    : QParallelAnimationGroup(parent),
      m_overlay(0),
      m_radiusAnimation(animate("radius")),
      m_opacityAnimation(animate("opacity")),
      m_radius(0),
      m_opacity(0),
      m_center(center)
{
    init();
}

XMatRipple::XMatRipple(const QPoint &center,
                                   XMatRippleOverlay *overlay,
                                   QObject *parent)
    : QParallelAnimationGroup(parent),
      m_overlay(overlay),
      m_radiusAnimation(animate("radius")),
      m_opacityAnimation(animate("opacity")),
      m_radius(0),
      m_opacity(0),
      m_center(center)
{
    init();
}

XMatRipple::~XMatRipple()
{
}

void XMatRipple::setRadius(qreal radius)
{
    Q_ASSERT(m_overlay);

    if (m_radius == radius) {
        return;
    }
    m_radius = radius;
    m_overlay->update();
}

void XMatRipple::setOpacity(qreal opacity)
{
    Q_ASSERT(m_overlay);

    if (m_opacity == opacity) {
        return;
    }
    m_opacity = opacity;
    m_overlay->update();
}

void XMatRipple::setColor(const QColor &color)
{
    if (m_brush.color() == color) {
        return;
    }
    m_brush.setColor(color);

    if (m_overlay) {
        m_overlay->update();
    }
}

void XMatRipple::setBrush(const QBrush &brush)
{
    m_brush = brush;

    if (m_overlay) {
        m_overlay->update();
    }
}

void XMatRipple::destroy()
{
    Q_ASSERT(m_overlay);

    m_overlay->removeRipple(this);
}

/*!
 *  \internal
 */
QPropertyAnimation *XMatRipple::animate(const QByteArray &property,
                                              const QEasingCurve &easing,
                                              int duration)
{
    QPropertyAnimation *animation = new QPropertyAnimation;
    animation->setTargetObject(this);
    animation->setPropertyName(property);
    animation->setEasingCurve(easing);
    animation->setDuration(duration);
    addAnimation(animation);
    return animation;
}

/*!
 *  \internal
 */
void XMatRipple::init()
{
    setOpacityStartValue(0.5);
    setOpacityEndValue(0);
    setRadiusStartValue(0);
    setRadiusEndValue(300);

    m_brush.setColor(Qt::black);
    m_brush.setStyle(Qt::SolidPattern);

    connect(this, SIGNAL(finished()), this, SLOT(destroy()));
}
