#include "XMatFlatButton.h"
#include "XMatFlatButton_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QBitmap>
#include <QPainterPath>
#include <QIcon>
#include "XMatRippleoverlay.h"
#include "XMatRipple.h"

#include "XMatFlatButton_internal.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatFlatButtonPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatFlatButtonPrivate::XMatFlatButtonPrivate(XMatFlatButton *q)
    : q_ptr(q)
{
    backgroundColor=C_XMatThemeColor;
    foregroundColor=QColor(255,255,255,255);
    rippleColor=QColor(255,255,255,255);
    overlayColor=C_XMatOverlaydColor;
    disabledForegroundColor=C_XMatDisableForegroundColor;
    disabledBackgroundColor=C_XMatDisableBackgroundColor;
}

/*!
 *  \internal
 */
XMatFlatButtonPrivate::~XMatFlatButtonPrivate()
{
}

/*!
 *  \internal
 */
void XMatFlatButtonPrivate::init()
{
    Q_Q(XMatFlatButton);

    rippleOverlay        = new XMatRippleOverlay(q);
    stateMachine         = new XMatFlatButtonStateMachine(q);
    rippleStyle          = XMatCommonDef::PositionedRipple;
    overlayStyle         = XMatCommonDef::GrayOverlay;
    iconPlacement        = XMatFlatButton::FlatButtonIconPlacement::LeftIcon;
    bgMode               = Qt::OpaqueMode;
    textAlignment        = Qt::AlignHCenter;
    fixedRippleRadius    = 64;
    cornerRadius         = 3;
    baseOpacity          = 0.13;
    fontSize             = 10;        // 10.5;
    useFixedRippleRadius = false;
    haloVisible          = false;

    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setMinimumHeight(16);

    QFont font(C_XMatFont);
    q->setFont(font);

    QPainterPath path;
    path.addRoundedRect(q->rect(), cornerRadius, cornerRadius);
    rippleOverlay->setClipPath(path);
    rippleOverlay->setClipping(true);

    stateMachine->setupProperties();
    stateMachine->startAnimations();
}

/*!
 *  \class XMatFlatButton
 */

XMatFlatButton::XMatFlatButton(QWidget *parent, FlatButtonPreset preset)
    : QPushButton(parent),
      d_ptr(new XMatFlatButtonPrivate(this))
{
    d_func()->init();
    setText("FlatButton");
    resize(80,26);
    applyPreset(preset);
}

XMatFlatButton::XMatFlatButton(const QString &text, QWidget *parent, FlatButtonPreset preset)
    : QPushButton(text, parent),
      d_ptr(new XMatFlatButtonPrivate(this))
{

    d_func()->init();

    applyPreset(preset);
}

XMatFlatButton::~XMatFlatButton()
{
}

void XMatFlatButton::applyPreset( FlatButtonPreset preset)
{
    switch (preset)
    {
    case FlatButtonPreset::FlatPreset:
        setOverlayStyle(XMatCommonDef::NoOverlay);
        break;
    case FlatButtonPreset::CheckablePreset:
        setOverlayStyle(XMatCommonDef::NoOverlay);
        setCheckable(true);
        setHaloVisible(false);
        break;
    default:
        break;
    }
}



void XMatFlatButton::setForegroundColor(const QColor &color)
{
    Q_D(XMatFlatButton);

    d->foregroundColor = color;


    update();
}

QColor XMatFlatButton::foregroundColor() const
{
    Q_D(const XMatFlatButton);
    return d->foregroundColor;
}

void XMatFlatButton::setBackgroundColor(const QColor &color)
{
    Q_D(XMatFlatButton);

    d->backgroundColor = color;

    update();
}

QColor XMatFlatButton::backgroundColor() const
{
    Q_D(const XMatFlatButton);
    return d->backgroundColor;
}

void XMatFlatButton::setRippleColor(const QColor &color)
{
    Q_D(XMatFlatButton);

    d->rippleColor = color;

    update();
}

QColor XMatFlatButton::rippleColor() const
{
    Q_D(const XMatFlatButton);
    return d->rippleColor;
}

void XMatFlatButton::setOverlayColor(const QColor &color)
{
    Q_D(XMatFlatButton);

    d->overlayColor = color;

    setOverlayStyle(XMatCommonDef::TintedOverlay);
    update();
}

QColor XMatFlatButton::overlayColor() const
{
    Q_D(const XMatFlatButton);

    if (!d->overlayColor.isValid()) {
        return foregroundColor();
    }
    return d->overlayColor;
}

void XMatFlatButton::setDisabledForegroundColor(const QColor &color)
{
    Q_D(XMatFlatButton);

    d->disabledForegroundColor = color;


    update();
}

QColor XMatFlatButton::disabledForegroundColor() const
{
    Q_D(const XMatFlatButton);

    return d->disabledForegroundColor;
}

void XMatFlatButton::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(XMatFlatButton);

    d->disabledBackgroundColor = color;


    update();
}

QColor XMatFlatButton::disabledBackgroundColor() const
{
    Q_D(const XMatFlatButton);

    return d->disabledBackgroundColor;
}

void XMatFlatButton::setFontSize(qreal size)
{
    Q_D(XMatFlatButton);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal XMatFlatButton::fontSize() const
{
    Q_D(const XMatFlatButton);
    return d->fontSize;
}

void XMatFlatButton::setHaloVisible(bool visible)
{
    Q_D(XMatFlatButton);

    d->haloVisible = visible;
    update();
}

bool XMatFlatButton::haloVisible() const
{
    Q_D(const XMatFlatButton);
    return d->haloVisible;
}

void XMatFlatButton::setOverlayStyle(XMatCommonDef::OverlayStyle style)
{
    Q_D(XMatFlatButton);

    d->overlayStyle = style;
    update();
}

 XMatCommonDef::OverlayStyle XMatFlatButton::overlayStyle() const
{
    Q_D(const XMatFlatButton);

    return d->overlayStyle;
}

void XMatFlatButton::setRippleStyle(XMatCommonDef::RippleStyle style)
{
    Q_D(XMatFlatButton);

    d->rippleStyle = style;
}

XMatCommonDef::RippleStyle XMatFlatButton::rippleStyle() const
{
    Q_D(const XMatFlatButton);
    return d->rippleStyle;
}

void XMatFlatButton::setIconPlacement(FlatButtonIconPlacement placement)
{
    Q_D(XMatFlatButton);

    d->iconPlacement = placement;
    update();
}

XMatFlatButton::FlatButtonIconPlacement XMatFlatButton::iconPlacement() const
{
    Q_D(const XMatFlatButton);

    return d->iconPlacement;
}

void XMatFlatButton::setCornerRadius(qreal radius)
{
    Q_D(XMatFlatButton);

    d->cornerRadius = radius;
    updateClipPath();
    update();
}

qreal XMatFlatButton::cornerRadius() const
{
    Q_D(const XMatFlatButton);

    return d->cornerRadius;
}

void XMatFlatButton::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(XMatFlatButton);

    d->bgMode = mode;
    d->stateMachine->setupProperties();
}

Qt::BGMode XMatFlatButton::backgroundMode() const
{
    Q_D(const XMatFlatButton);
    return d->bgMode;
}

void XMatFlatButton::setBaseOpacity(qreal opacity)
{
    Q_D(XMatFlatButton);

    d->baseOpacity = opacity;
    d->stateMachine->setupProperties();
}

qreal XMatFlatButton::baseOpacity() const
{
    Q_D(const XMatFlatButton);

    return d->baseOpacity;
}

void XMatFlatButton::setCheckable(bool value)
{
    Q_D(XMatFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::setCheckable(value);
}

void XMatFlatButton::setHasFixedRippleRadius(bool value)
{
    Q_D(XMatFlatButton);

    d->useFixedRippleRadius = value;
}

bool XMatFlatButton::hasFixedRippleRadius() const
{
    Q_D(const XMatFlatButton);

    return d->useFixedRippleRadius;
}

void XMatFlatButton::setFixedRippleRadius(qreal radius)
{
    Q_D(XMatFlatButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
}

qreal XMatFlatButton::fixedRippleRadius() const
{
    Q_D(const XMatFlatButton);

    return d->fixedRippleRadius;
}

void XMatFlatButton::setTextAlignment(Qt::Alignment alignment)
{
    Q_D(XMatFlatButton);
    d->textAlignment = alignment;
}

Qt::Alignment XMatFlatButton::textAlignment() const
{
    Q_D(const XMatFlatButton);

    return d->textAlignment;
}

/*!
 *  \reimp
 */
QSize XMatFlatButton::sizeHint() const
{
    ensurePolished();

    QSize label(fontMetrics().size(Qt::TextSingleLine, text()));

    int w = 20 + label.width();
    int h = label.height();
    if (!icon().isNull()) {
        w += iconSize().width() + XMatFlatButton::IconPadding;
        h = qMax(h, iconSize().height());
    }
    return QSize(w, 10 + h);
}

XMatFlatButton::XMatFlatButton(XMatFlatButtonPrivate &d,QWidget *parent,FlatButtonPreset preset)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();

    applyPreset(preset);
}

/*!
 *  \reimp
 */
void XMatFlatButton::checkStateSet()
{
    Q_D(XMatFlatButton);

    d->stateMachine->updateCheckedStatus();

    QPushButton::checkStateSet();
}

/*!
 *  \reimp
 */
void XMatFlatButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatFlatButton);

    if (XMatCommonDef::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (XMatCommonDef::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->pos();
        }

        if (d->useFixedRippleRadius) {
            radiusEndValue = d->fixedRippleRadius;
        } else {
            radiusEndValue = static_cast<qreal>(width())/2;
        }

        XMatRipple *ripple = new XMatRipple(pos);
        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(rippleColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);
        d->rippleOverlay->addRipple(ripple);
    }

    QPushButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void XMatFlatButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(XMatFlatButton);

    QPushButton::mouseReleaseEvent(event);

    d->stateMachine->updateCheckedStatus();
}

void XMatFlatButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);

    updateClipPath();
}

/*!
 *  \reimp
 */
void XMatFlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatFlatButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const qreal cr = d->cornerRadius;

    if (cr > 0)
    {
        QPainterPath path;
        path.addRoundedRect(rect(), cr, cr);

        painter.setClipPath(path);
        painter.setClipping(true);
    }

    paintBackground(&painter);
    paintHalo(&painter);

    painter.setOpacity(1);
    painter.setClipping(false);

    paintForeground(&painter);
}

/*!
 *  \internal
 */
void XMatFlatButton::paintBackground(QPainter *painter)
{
    Q_D(XMatFlatButton);

    const qreal overlayOpacity = d->stateMachine->overlayOpacity();
    const qreal checkedProgress = d->stateMachine->checkedOverlayProgress();

    if (Qt::OpaqueMode == d->bgMode) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        if (isEnabled()) {
            brush.setColor(backgroundColor());
        } else {
            brush.setColor(disabledBackgroundColor());
        }
        painter->setOpacity(1);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(Qt::NoPen);

    if (!isEnabled()) {
        return;
    }

    if ((XMatCommonDef::NoOverlay != d->overlayStyle) && (overlayOpacity > 0)) {
        if (XMatCommonDef::TintedOverlay == d->overlayStyle) {
            brush.setColor(overlayColor());
        } else {
            brush.setColor(Qt::gray);
        }
        painter->setOpacity(overlayOpacity);
        painter->setBrush(brush);
        painter->drawRect(rect());
    }

    if (isCheckable() && checkedProgress > 0) {
        const qreal q = Qt::TransparentMode == d->bgMode ? 0.45 : 0.7;
        brush.setColor(foregroundColor());
        painter->setOpacity(q*checkedProgress);
        painter->setBrush(brush);
        QRect r(rect());
        r.setHeight(static_cast<qreal>(r.height())*checkedProgress);
        painter->drawRect(r);
    }
}

/*!
 *  \internal
 */
void XMatFlatButton::paintHalo(QPainter *painter)
{
    Q_D(XMatFlatButton);

    if (!d->haloVisible) {
        return;
    }

    const qreal opacity = d->stateMachine->haloOpacity();
    const qreal s = d->stateMachine->haloScaleFactor()*d->stateMachine->haloSize();
    const qreal radius = static_cast<qreal>(width())*s;

    if (isEnabled() && opacity > 0) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(foregroundColor());
        painter->setOpacity(opacity);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        const QPointF center = rect().center();
        painter->drawEllipse(center, radius, radius);
    }
}

#define COLOR_INTERPOLATE(CH) (1-progress)*source.CH() + progress*dest.CH()

/*!
 *  \internal
 */
void XMatFlatButton::paintForeground(QPainter *painter)
{
    Q_D(XMatFlatButton);

    if (isEnabled()) {
        painter->setPen(foregroundColor());
        const qreal progress = d->stateMachine->checkedOverlayProgress();
        if (isCheckable() && progress > 0) {
            QColor source = foregroundColor();
            QColor dest = Qt::TransparentMode == d->bgMode ? Qt::white
                                                           : backgroundColor();
            if (qFuzzyCompare(1, progress)) {
                painter->setPen(dest);
            } else {
                painter->setPen(QColor(COLOR_INTERPOLATE(red),
                                       COLOR_INTERPOLATE(green),
                                       COLOR_INTERPOLATE(blue),
                                       COLOR_INTERPOLATE(alpha)));
            }
        }
    } else {
        painter->setPen(disabledForegroundColor());
    }

    if (icon().isNull())  {
        if (Qt::AlignLeft == d->textAlignment) {
            painter->drawText(rect().adjusted(12, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
        } else {
           painter->drawText(rect(), Qt::AlignCenter, text());
        }
        return;
    }

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size()-textSize);

    const int iw = iconSize().width() + IconPadding;
    QPoint pos(Qt::AlignLeft == d->textAlignment ? 12 : (base.width()-iw)/2, 0);

    QRect textGeometry(pos + QPoint(0, base.height()/2), textSize);
    QRect iconGeometry(pos + QPoint(0, (height()-iconSize().height())/2), iconSize());

    if (FlatButtonIconPlacement::LeftIcon == d->iconPlacement) {
        textGeometry.translate(iw, 0);
    } else {
        iconGeometry.translate(textSize.width() + IconPadding, 0);
    }

    painter->drawText(textGeometry, Qt::AlignCenter, text());
    QPixmap pixmap = icon().pixmap(iconSize());
    if(text().isEmpty())
    {
        QRect iconRect=QRect(QPoint((width()-iconSize().width())/2,(height()-iconSize().height())/2),iconSize());
        painter->drawPixmap(iconRect, pixmap);
    }
    else
    {
        painter->drawPixmap(iconGeometry, pixmap);
    }
}

/*!
 *  \internal
 */
void XMatFlatButton::updateClipPath()
{
    Q_D(XMatFlatButton);

    const qreal radius = d->cornerRadius;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    d->rippleOverlay->setClipPath(path);
}
