#ifndef XMATRIPPLE_H
#define XMATRIPPLE_H

#include "XWidgetGlobal.h"
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QPoint>
#include <QBrush>

class XMatRippleOverlay;

class XWIDGET_EXPORT XMatRipple : public QParallelAnimationGroup
{
    Q_OBJECT

    Q_PROPERTY(qreal radius WRITE setRadius READ radius)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit XMatRipple(const QPoint &center, QObject *parent = 0);
    XMatRipple(const QPoint &center, XMatRippleOverlay *overlay, QObject *parent = 0);
    ~XMatRipple();

    inline void setOverlay(XMatRippleOverlay *overlay);

    void setRadius(qreal radius);
    inline qreal radius() const;

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    void setColor(const QColor &color);
    inline QColor color() const;

    void setBrush(const QBrush &brush);
    inline QBrush brush() const;

    inline QPoint center() const;

    inline QPropertyAnimation *radiusAnimation() const;
    inline QPropertyAnimation *opacityAnimation() const;

    inline void setOpacityStartValue(qreal value);
    inline void setOpacityEndValue(qreal value);
    inline void setRadiusStartValue(qreal value);
    inline void setRadiusEndValue(qreal value);
    inline void setDuration(int msecs);

protected slots:
    void destroy();

private:
    Q_DISABLE_COPY(XMatRipple)

    QPropertyAnimation *animate(const QByteArray &property,
                                const QEasingCurve &easing = QEasingCurve::OutQuad,
                                int duration = 800);

    void init();

    XMatRippleOverlay  *m_overlay;
    QPropertyAnimation *const m_radiusAnimation;
    QPropertyAnimation *const m_opacityAnimation;
    qreal                     m_radius;
    qreal                     m_opacity;
    QPoint                    m_center;
    QBrush                    m_brush;
};

inline void XMatRipple::setOverlay(XMatRippleOverlay *overlay)
{
    m_overlay = overlay;
}

inline qreal XMatRipple::radius() const
{
    return m_radius;
}

inline qreal XMatRipple::opacity() const
{
    return m_opacity;
}

inline QColor XMatRipple::color() const
{
    return m_brush.color();
}

inline QBrush XMatRipple::brush() const
{
    return m_brush;
}

inline QPoint XMatRipple::center() const
{
    return m_center;
}

inline QPropertyAnimation *XMatRipple::radiusAnimation() const
{
    return m_radiusAnimation;
}

inline QPropertyAnimation *XMatRipple::opacityAnimation() const
{
    return m_opacityAnimation;
}

inline void XMatRipple::setOpacityStartValue(qreal value)
{
    m_opacityAnimation->setStartValue(value);
}

inline void XMatRipple::setOpacityEndValue(qreal value)
{
    m_opacityAnimation->setEndValue(value);
}

inline void XMatRipple::setRadiusStartValue(qreal value)
{
    m_radiusAnimation->setStartValue(value);
}

inline void XMatRipple::setRadiusEndValue(qreal value)
{
    m_radiusAnimation->setEndValue(value);
}

inline void XMatRipple::setDuration(int msecs)
{
    m_radiusAnimation->setDuration(msecs);
    m_opacityAnimation->setDuration(msecs);
}

#endif // XMATRIPPLE_H
