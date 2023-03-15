#ifndef XMATSLIDER_INTERNAL_H
#define XMATSLIDER_INTERNAL_H

#include <QStateMachine>
#include "XMatOverlaywidget.h"

class XMatSlider;
class XMatSliderThumb;
class XMatSliderTrack;

class XMatSliderStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    XMatSliderStateMachine(XMatSlider *slider,
                                 XMatSliderThumb *thumb,
                                 XMatSliderTrack *track);
    ~XMatSliderStateMachine();

    void setupProperties();

private:
    Q_DISABLE_COPY(XMatSliderStateMachine)

    XMatSlider      *const m_slider;
    XMatSliderThumb *const m_thumb;
    XMatSliderTrack *const m_track;
    QState                *const m_topState;
    QState                *const m_fstState;
    QState                *const m_sndState;
    QState                *const m_inactiveState;
    QState                *const m_focusState;
    QState                *const m_slidingState;
    QState                *const m_pulseOutState;
    QState                *const m_pulseInState;
    QState                *const m_minState;
    QState                *const m_normalState;
};

class XMatSliderThumb : public XMatOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal diameter WRITE setDiameter READ diameter)
    Q_PROPERTY(qreal borderWidth WRITE setBorderWidth READ borderWidth)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)
    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)
    Q_PROPERTY(qreal haloSize WRITE setHaloSize READ haloSize)
    Q_PROPERTY(QColor haloColor WRITE setHaloColor READ haloColor)

public:
    explicit XMatSliderThumb(XMatSlider *slider);
    ~XMatSliderThumb();

    inline void setDiameter(qreal diameter);
    inline qreal diameter() const;

    inline void setBorderWidth(qreal width);
    inline qreal borderWidth() const;

    inline void setBorderColor(const QColor &color);
    inline QColor borderColor() const;

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setHaloSize(qreal size);
    inline qreal haloSize() const;

    inline void setHaloColor(const QColor &color);
    inline QColor haloColor() const;

    inline void setOffset(int offset);
    inline int offset() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatSliderThumb)

    const XMatSlider *const m_slider;
    QColor                        m_borderColor;
    QColor                        m_fillColor;
    QColor                        m_haloColor;
    qreal                         m_diameter;
    qreal                         m_borderWidth;
    qreal                         m_haloSize;
    int                           m_offset;
};

inline void XMatSliderThumb::setDiameter(qreal diameter)
{
    m_diameter = diameter;
    update();
}

inline qreal XMatSliderThumb::diameter() const
{
    return m_diameter;
}

inline void XMatSliderThumb::setBorderWidth(qreal width)
{
    m_borderWidth = width;
    update();
}

inline qreal XMatSliderThumb::borderWidth() const
{
    return m_borderWidth;
}

inline void XMatSliderThumb::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    update();
}

inline QColor XMatSliderThumb::borderColor() const
{
    return m_borderColor;
}

inline void XMatSliderThumb::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

inline QColor XMatSliderThumb::fillColor() const
{
    return m_fillColor;
}

inline void XMatSliderThumb::setHaloSize(qreal size)
{
    m_haloSize = size;
    update();
}

inline qreal XMatSliderThumb::haloSize() const
{
    return m_haloSize;
}

inline void XMatSliderThumb::setHaloColor(const QColor &color)
{
    m_haloColor = color;
    update();
}

inline QColor XMatSliderThumb::haloColor() const
{
    return m_haloColor;
}

inline void XMatSliderThumb::setOffset(int offset)
{
    m_offset = offset;
    update();
}

inline int XMatSliderThumb::offset() const
{
    return m_offset;
}

class XMatSliderTrack : public XMatOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor fillColor WRITE setFillColor READ fillColor)

public:
    explicit XMatSliderTrack(XMatSliderThumb *thumb, XMatSlider *slider);
    ~XMatSliderTrack();

    inline void setFillColor(const QColor &color);
    inline QColor fillColor() const;

    inline void setTrackWidth(int width);
    inline int trackWidth() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatSliderTrack)

    const XMatSlider *const m_slider;
    XMatSliderThumb  *const m_thumb;
    QColor                        m_fillColor;
    int                           m_trackWidth;
};

inline void XMatSliderTrack::setFillColor(const QColor &color)
{
    m_fillColor = color;
    update();
}

inline QColor XMatSliderTrack::fillColor() const
{
    return m_fillColor;
}

void XMatSliderTrack::setTrackWidth(int width)
{
    m_trackWidth = width;
    update();
}

int XMatSliderTrack::trackWidth() const
{
    return m_trackWidth;
}

#endif // XMATSLIDER_INTERNAL_H
