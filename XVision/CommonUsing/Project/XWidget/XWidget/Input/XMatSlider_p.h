#ifndef XMATSLIDER_P_H
#define XMATSLIDER_P_H

#include <QtGlobal>
#include <QColor>
#include <QRectF>

class XMatSlider;
class XMatSliderThumb;
class XMatSliderTrack;
class XMatSliderStateMachine;

class XMatSliderPrivate
{
    Q_DISABLE_COPY(XMatSliderPrivate)
    Q_DECLARE_PUBLIC(XMatSlider)

public:
    XMatSliderPrivate(XMatSlider *q);
    ~XMatSliderPrivate();

    void init();

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    XMatSlider             *const q_ptr;
    XMatSliderThumb        *thumb;
    XMatSliderTrack        *track;
    XMatSliderStateMachine *stateMachine;
    QColor                        thumbColor;
    QColor                        trackColor;
    QColor                        disabledColor;
    int                           stepTo;
    int                           oldValue;
    int                           trackWidth;
    bool                          hoverTrack;
    bool                          hoverThumb;
    bool                          hover;
    bool                          step;
    bool                          pageStepMode;
};

#endif // XMATSLIDER_P_H
