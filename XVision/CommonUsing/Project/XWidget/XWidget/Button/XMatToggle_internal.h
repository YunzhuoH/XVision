#ifndef XMATTOGGLE_INTERNAL_H
#define XMATTOGGLE_INTERNAL_H

#include <QtWidgets/QWidget>
#include "XMatRippleOverlay.h"

class XMatToggle;
class XMatToggleThumb;
class XMatToggleTrack;

class XMatToggleRippleOverlay : public XMatRippleOverlay
{
    Q_OBJECT

public:
    XMatToggleRippleOverlay(XMatToggleThumb *thumb,
                                  XMatToggleTrack *track,
                                  XMatToggle *parent);
    ~XMatToggleRippleOverlay();

protected slots:
    void addToggleRipple();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatToggleRippleOverlay)

    XMatToggle      *const m_toggle;
    XMatToggleThumb *const m_thumb;
    XMatToggleTrack *const m_track;
};

class XMatToggleThumb : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)

public:
    XMatToggleThumb(XMatToggle *parent);
    ~XMatToggleThumb();

    void setShift(qreal shift);
    inline qreal shift() const;

    inline qreal offset() const;

    inline void setThumbColor(const QColor &color);
    inline QColor thumbColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatToggleThumb)

    void updateOffset();

    XMatToggle *const m_toggle;
    QColor                  m_thumbColor;
    qreal                   m_shift;
    qreal                   m_offset;
};

inline qreal XMatToggleThumb::shift() const
{
    return m_shift;
}

inline qreal XMatToggleThumb::offset() const
{
    return m_offset;
}

inline void XMatToggleThumb::setThumbColor(const QColor &color)
{
    m_thumbColor = color;
    update();
}

inline QColor XMatToggleThumb::thumbColor() const
{
    return m_thumbColor;
}

class XMatToggleTrack : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)

public:
    XMatToggleTrack(XMatToggle *parent);
    ~XMatToggleTrack();

    void setTrackColor(const QColor &color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatToggleTrack)

    XMatToggle *const m_toggle;
    QColor                  m_trackColor;
};

inline QColor XMatToggleTrack::trackColor() const
{
    return m_trackColor;
}

#endif // XMATTOGGLE_INTERNAL_H
