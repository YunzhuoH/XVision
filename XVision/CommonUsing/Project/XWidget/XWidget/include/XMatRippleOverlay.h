#ifndef XMATRIPPLEOVERLAY_H
#define XMATRIPPLEOVERLAY_H

#include "XWidgetGlobal.h"
#include <QPainterPath>
#include "XMatOverlayWidget.h"

class XMatRipple;

class XWIDGET_EXPORT XMatRippleOverlay : public XMatOverlayWidget
{
    Q_OBJECT

public:
    explicit XMatRippleOverlay(QWidget *parent = 0);
    ~XMatRippleOverlay();

    void addRipple(XMatRipple *ripple);
    void addRipple(const QPoint &position, qreal radius = 300);

    void removeRipple(XMatRipple *ripple);

    inline void setClipping(bool enable);
    inline bool hasClipping() const;

    inline void setClipPath(const QPainterPath &path);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    inline QList<XMatRipple *> ripples() const;

private:
    Q_DISABLE_COPY(XMatRippleOverlay)

    void paintRipple(QPainter *painter, XMatRipple *ripple);

    QList<XMatRipple *> m_ripples;
    QPainterPath              m_clipPath;
    bool                      m_useClip;
};

inline void XMatRippleOverlay::setClipping(bool enable)
{
    m_useClip = enable;
    update();
}

inline bool XMatRippleOverlay::hasClipping() const
{
    return m_useClip;
}

inline void XMatRippleOverlay::setClipPath(const QPainterPath &path)
{
    m_clipPath = path;
    update();
}

inline QList<XMatRipple *> XMatRippleOverlay::ripples() const
{
    return m_ripples;
}

#endif // XMATRIPPLEOVERLAY_H
