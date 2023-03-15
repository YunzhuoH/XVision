#include "XMatSlider.h"
#include "XMatSlider_p.h"
#include <QtWidgets/QApplication>
#include <QMouseEvent>
#include <QStyle>
#include "XMatSlider_internal.h"
#include "XMatSliderStateTransition.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatSliderPrivate
 *  \internal
 */

XMatSliderPrivate::XMatSliderPrivate(XMatSlider *q)
    : q_ptr(q)
{
    thumbColor=C_XMatThemeColor;
    trackColor=QColor(170,170,170,170);
    disabledColor=C_XMatDisableForegroundColor;
}

XMatSliderPrivate::~XMatSliderPrivate()
{
}

void XMatSliderPrivate::init()
{
    Q_Q(XMatSlider);

    thumb          = new XMatSliderThumb(q);
    track          = new XMatSliderTrack(thumb, q);
    stateMachine   = new XMatSliderStateMachine(q, thumb, track);
    stepTo         = 0;
    oldValue       = q->value();
    trackWidth     = 2;
    hoverTrack     = false;
    hoverThumb     = false;
    hover          = false;
    step           = false;
    pageStepMode   = true;


    q->setMouseTracking(true);
    q->setFocusPolicy(Qt::StrongFocus);
    q->setPageStep(1);

    QSizePolicy sp(QSizePolicy::Expanding,
                   QSizePolicy::Fixed);

    if (q->orientation() == Qt::Vertical) {
        sp.transpose();
    }

    q->setSizePolicy(sp);
    q->setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    stateMachine->start();
    QCoreApplication::processEvents();
}

QRectF XMatSliderPrivate::trackBoundingRect() const
{
    Q_Q(const XMatSlider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(XMAT_SLIDER_MARGIN, q->height()/2 - hw,
                 q->width() - XMAT_SLIDER_MARGIN*2, hw*2)
        : QRectF(q->width()/2 - hw, XMAT_SLIDER_MARGIN, hw*2,
                 q->height() - XMAT_SLIDER_MARGIN*2);
}

QRectF XMatSliderPrivate::thumbBoundingRect() const
{
    Q_Q(const XMatSlider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(thumb->offset(), q->height()/2 - XMAT_SLIDER_MARGIN,
                 XMAT_SLIDER_MARGIN*2, XMAT_SLIDER_MARGIN*2)
        : QRectF(q->width()/2 - XMAT_SLIDER_MARGIN, thumb->offset(),
                 XMAT_SLIDER_MARGIN*2, XMAT_SLIDER_MARGIN*2);
}

int XMatSliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const XMatSlider);

    const int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    const int span = Qt::Horizontal == q->orientation()
        ? q->width() - XMAT_SLIDER_MARGIN*2
        : q->height() - XMAT_SLIDER_MARGIN*2;

    return QStyle::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - XMAT_SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

void XMatSliderPrivate::setHovered(bool status)
{
    Q_Q(XMatSlider);

    if (hover == status) {
        return;
    }

    hover = status;

    if (!q->hasFocus()) {
        if (status) {
            stateMachine->postEvent(new XMatSliderStateTransitionEvent(SliderNoFocusMouseEnter));
        } else {
            stateMachine->postEvent(new XMatSliderStateTransitionEvent(SliderNoFocusMouseLeave));
        }
    }

    q->update();
}

/*!
 *  \class XMatSlider
 */

XMatSlider::XMatSlider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new XMatSliderPrivate(this))
{
    d_func()->init();
}

XMatSlider::~XMatSlider()
{
}



void XMatSlider::setThumbColor(const QColor &color)
{
    Q_D(XMatSlider);

    d->thumbColor = color;


    d->stateMachine->setupProperties();
    update();
}

QColor XMatSlider::thumbColor() const
{
    Q_D(const XMatSlider);

    return d->thumbColor;
}

void XMatSlider::setTrackColor(const QColor &color)
{
    Q_D(XMatSlider);

    d->trackColor = color;


    d->stateMachine->setupProperties();
    update();
}

QColor XMatSlider::trackColor() const
{
    Q_D(const XMatSlider);

    return d->trackColor;
}

void XMatSlider::setDisabledColor(const QColor &color)
{
    Q_D(XMatSlider);

    d->disabledColor = color;

    d->stateMachine->setupProperties();
    update();
}

QColor XMatSlider::disabledColor() const
{
    Q_D(const XMatSlider);

    return d->disabledColor;
}

void XMatSlider::setPageStepMode(bool pageStep)
{
    Q_D(XMatSlider);

    d->pageStepMode = pageStep;
}

bool XMatSlider::pageStepMode() const
{
    Q_D(const XMatSlider);

    return d->pageStepMode;
}

/*!
 *  \remip
 */
QSize XMatSlider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
            ? QSize(130, 34)
            : QSize(34, 130);
}

void XMatSlider::setInvertedAppearance(bool value)
{
    QAbstractSlider::setInvertedAppearance(value);

    updateThumbOffset();
}

/*!
 *  \remip
 */
void XMatSlider::sliderChange(SliderChange change)
{
    Q_D(XMatSlider);

    if (SliderOrientationChange == change)
    {
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (orientation() == Qt::Vertical) {
            sp.transpose();
        }
        setSizePolicy(sp);
    }
    else if (SliderValueChange == change)
    {
        if (minimum() == value()) {
            triggerAction(SliderToMinimum);
            d->stateMachine->postEvent(new XMatSliderStateTransitionEvent(SliderChangedToMinimum));
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == d->oldValue) {
            d->stateMachine->postEvent(new XMatSliderStateTransitionEvent(SliderChangedFromMinimum));
        }
        d->oldValue = value();
    }

    updateThumbOffset();

    QAbstractSlider::sliderChange(change);
}

/*!
 *  \remip
 */
void XMatSlider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(XMatSlider);

    if (isSliderDown())
    {
        setSliderPosition(d->valueFromPosition(event->pos()));
    }
    else
    {
        QRectF track(d->trackBoundingRect().adjusted(-2, -2, 2, 2));

        if (track.contains(event->pos()) != d->hoverTrack) {
            d->hoverTrack = !d->hoverTrack;
            update();
        }

        QRectF thumb(0, 0, 16, 16);
        thumb.moveCenter(d->thumbBoundingRect().center());

        if (thumb.contains(event->pos()) != d->hoverThumb) {
            d->hoverThumb = !d->hoverThumb;
            update();
        }

        d->setHovered(d->hoverTrack || d->hoverThumb);
    }

    QAbstractSlider::mouseMoveEvent(event);
}

/*!
 *  \remip
 */
void XMatSlider::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatSlider);

    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbBoundingRect().center());

    if (thumb.contains(pos)) {
        setSliderDown(true);
        return;
    }

    if (!d->pageStepMode) {
        setSliderPosition(d->valueFromPosition(event->pos()));
        d->thumb->setHaloSize(0);
        setSliderDown(true);
        return;
    }

    d->step = true;
    d->stepTo = d->valueFromPosition(pos);

    SliderAction action = d->stepTo > sliderPosition()
        ? SliderPageStepAdd
        : SliderPageStepSub;

    triggerAction(action);
    setRepeatAction(action, 400, 8);
}

/*!
 *  \remip
 */
void XMatSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(XMatSlider);

    if (isSliderDown()) {
        setSliderDown(false);
    } else if (d->step) {
        d->step = false;
        setRepeatAction(SliderNoAction, 0);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}

/*!
 *  \remip
 */
void XMatSlider::leaveEvent(QEvent *event)
{
    Q_D(XMatSlider);

    if (d->hoverTrack) {
        d->hoverTrack = false;
        update();
    }
    if (d->hoverThumb) {
        d->hoverThumb = false;
        update();
    }

    d->setHovered(false);

    QAbstractSlider::leaveEvent(event);
}

void XMatSlider::updateThumbOffset()
{
    Q_D(XMatSlider);

    const int offset = QStyle::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - XMAT_SLIDER_MARGIN*2
            : height() - XMAT_SLIDER_MARGIN*2,
        invertedAppearance());

    d->thumb->setOffset(offset);
}
