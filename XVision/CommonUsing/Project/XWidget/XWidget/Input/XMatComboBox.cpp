#include "XMatComboBox.h"
#include "XMatComboBox_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QEventTransition>
#include <QSignalTransition>
#include <QCoreApplication>
#include <QBitmap>
#include <QPainterPath>
#include <QIcon>
#include "XMatRippleoverlay.h"
#include "XMatRipple.h"

#include "XMatComboBox_internal.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatComboBoxPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatComboBoxPrivate::XMatComboBoxPrivate(XMatComboBox *q)
    : q_ptr(q)
{
    normalColor=C_XMatThemeColor;
    showPopupColor=C_XMatThemeColor;
    backgroundColor=C_XMatBackgroundColor;
    borderColor=C_XMatForegroundColor;
    textColor=C_XMatFontdColor;
    disabledForegroundColor=C_XMatDisableForegroundColor;
    disabledBackgroundColor=C_XMatDisableBackgroundColor;
}

/*!
 *  \internal
 */
XMatComboBoxPrivate::~XMatComboBoxPrivate()
{
}

/*!
 *  \internal
 */
void XMatComboBoxPrivate::init()
{
    Q_Q(XMatComboBox);

    rippleOverlay        = new XMatRippleOverlay(q);
    normalIcon           = new XMatComboBoxIcon(QIcon(":/images/ComboBoxNormal.svg"),q);
    showPopupIcon         = new XMatComboBoxIcon(QIcon(":/images/ComboBoxShowPopup.svg"),q);
    stateMachine         = new QStateMachine(q);
    normalState          = new QState;
    showPopupState        = new QState;
  //  disabledState        = new QState;
    normalTransition     = new QSignalTransition(q,SIGNAL(cmbShowPopup()));
    showPopupTransition     = new QSignalTransition(q, SIGNAL(cmbHidePopup()));
    fontSize                =10;
    rippleStyle          = XMatCommonDef::PositionedRipple;
    rippleOverlay->setParent(q->parentWidget());
    rippleOverlay->installEventFilter(q);

    q->setFont(C_XMatFont);

    QFont font(C_XMatFont);
    q->setFont(font);
    stateMachine->addState(normalState);
    stateMachine->addState(showPopupState);
    stateMachine->setInitialState(normalState);

    // Transition to pulldown
    normalTransition->setTargetState(showPopupState);
    normalState->addTransition(normalTransition);

    // Transition to normal

    showPopupTransition->setTargetState(normalState);
    showPopupState->addTransition(showPopupTransition);



    //

    normalState->assignProperty(normalIcon, "opacity", 1);
    normalState->assignProperty(showPopupIcon, "opacity", 0);

    showPopupState->assignProperty(normalIcon, "opacity", 0);
    showPopupState->assignProperty(showPopupIcon, "opacity", 1);


    normalState->assignProperty(normalIcon, "color", q->normalColor());
    normalState->assignProperty(showPopupIcon, "color", q->showPopupColor());

    showPopupState->assignProperty(normalIcon, "color", q->normalColor());
    showPopupState->assignProperty(showPopupIcon, "color", q->showPopupColor());


    stateMachine->start();
    QCoreApplication::processEvents();

}

/*!
 *  \class XMatComboBox
 */

XMatComboBox::XMatComboBox(QWidget *parent)
    : QComboBox(parent),
      d_ptr(new XMatComboBoxPrivate(this))
{
    d_func()->init();
}


XMatComboBox::~XMatComboBox()
{
}



/**********xie.y 新增**********/
void XMatComboBox::setNormalColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->normalColor = color;

    setupProperties();
}

QColor XMatComboBox::normalColor() const
{
    Q_D(const XMatComboBox);

    return d->normalColor;
}

void XMatComboBox::setShowPopupColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->showPopupColor = color;

    setupProperties();
}

QColor XMatComboBox::showPopupColor() const
{
    Q_D(const XMatComboBox);

    return d->showPopupColor;
}

void XMatComboBox::setBackgroundColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->backgroundColor = color;

}

QColor XMatComboBox::backgroundColor() const
{
    Q_D(const XMatComboBox);

    return d->backgroundColor;
}

void XMatComboBox::showPopup()
{
    QComboBox::showPopup();
    if(this->count()>0)
    {
       emit cmbShowPopup();
    }

}

void XMatComboBox::hidePopup()
{
    QComboBox::hidePopup();
    emit cmbHidePopup();
}

void XMatComboBox::setBorderColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->borderColor = color;

    update();
}

QColor XMatComboBox::borderColor() const
{
    Q_D(const XMatComboBox);
    return d->borderColor;
}

void XMatComboBox::setTextColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->textColor = color;

    update();
}

QColor XMatComboBox::textColor() const
{
    Q_D(const XMatComboBox);
    return d->textColor;
}

void XMatComboBox::setFontSize(qreal size)
{
    Q_D(XMatComboBox);

    d->fontSize = size;

    QFont f(font());
    f.setPointSizeF(size);
    setFont(f);

    update();
}

qreal XMatComboBox::fontSize() const
{
    Q_D(const XMatComboBox);
    return d->fontSize;
}

void XMatComboBox::setDisabledForegroundColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->disabledForegroundColor = color;

    update();
}

QColor XMatComboBox::disabledForegroundColor() const
{
    Q_D(const XMatComboBox);
    return d->disabledForegroundColor;
}

void XMatComboBox::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(XMatComboBox);

    d->disabledBackgroundColor = color;


    update();
}

QColor XMatComboBox::disabledBackgroundColor() const
{
    Q_D(const XMatComboBox);

    return d->disabledBackgroundColor;
}

void XMatComboBox::setRippleStyle(XMatCommonDef::RippleStyle style)
{
    Q_D(XMatComboBox);
    d->rippleStyle = style;
}

XMatCommonDef::RippleStyle XMatComboBox::rippleStyle() const
{
    Q_D(const XMatComboBox);
    return d->rippleStyle;
}


/*!
 *  \reimp
 */


XMatComboBox::XMatComboBox(XMatComboBoxPrivate &d,QWidget *parent)
    : QComboBox(parent),
      d_ptr(&d)
{
    d_func()->init();

}

bool XMatComboBox::event(QEvent *event)
{
    Q_D(XMatComboBox);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move:
        d->normalIcon->setGeometry(rect());
        d->showPopupIcon->setGeometry(rect());
        d->rippleOverlay->setGeometry(geometry());
        break;
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->rippleOverlay->setParent(widget);
        }
        break;
    default:
        break;
    }
    return QComboBox::event(event);
}

bool XMatComboBox::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(XMatComboBox);

        d->rippleOverlay->setGeometry(geometry());
    }
    return QComboBox::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void XMatComboBox::mousePressEvent(QMouseEvent *event)
{
    Q_D(XMatComboBox);

    if (XMatCommonDef::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (XMatCommonDef::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->pos();
        }

        radiusEndValue = static_cast<qreal>(width())/2;

        XMatRipple *ripple = new XMatRipple(pos);
        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(normalColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);
        d->rippleOverlay->addRipple(ripple);
    }

    QComboBox::mousePressEvent(event);
}

void XMatComboBox::wheelEvent(QWheelEvent *event)
{
    Q_D(XMatComboBox);

    if (XMatCommonDef::NoRipple != d->rippleStyle)
    {
        QPoint pos;
        qreal radiusEndValue;

        if (XMatCommonDef::CenteredRipple == d->rippleStyle) {
            pos = rect().center();
        } else {
            pos = event->position().toPoint();
        }

        radiusEndValue = static_cast<qreal>(width())/2;

        XMatRipple *ripple = new XMatRipple(pos);
        ripple->setRadiusEndValue(radiusEndValue);
        ripple->setOpacityStartValue(0.35);
        ripple->setColor(normalColor());
        ripple->radiusAnimation()->setDuration(600);
        ripple->opacityAnimation()->setDuration(1300);
        d->rippleOverlay->addRipple(ripple);
    }

    QComboBox::wheelEvent(event);
}



/*!
 *  \reimp
 */
void XMatComboBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatComboBox);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipping(true);


    painter.setOpacity(1);
    painter.setClipping(false);

    QPen pen;
    pen.setWidth(1);
    if(isEnabled())
    {
        pen.setColor(borderColor());
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(rect());
        pen.setWidth(1);
        painter.setPen(pen);
        painter.fillRect(rect(),backgroundColor());
        pen.setColor(textColor());
        painter.setPen(pen);
        if(!this->currentText().isEmpty())
        {
            auto y=height()/2+4;
            painter.drawText(4,y,this->currentText());
        }
    }
    else
    {
        pen.setColor(borderColor());
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(rect());
        pen.setWidth(1);
        painter.setPen(pen);
        painter.fillRect(rect(),disabledBackgroundColor());
        pen.setColor(disabledForegroundColor());
        painter.setPen(pen);
        if(!this->currentText().isEmpty())
        {
            auto y=height()/2+4;
            painter.drawText(4,y,this->currentText());
        }
    }



}

void XMatComboBox::setupProperties()
{
    Q_D(XMatComboBox);

    d->normalState->assignProperty(d->normalIcon, "color", normalColor());
    d->normalState->assignProperty(d->showPopupIcon, "color", showPopupColor());

    d->showPopupState->assignProperty(d->normalIcon, "color", normalColor());
    d->showPopupState->assignProperty(d->showPopupIcon, "color", showPopupColor());

    if (isEnabled()) {
        d->normalIcon->setColor(normalColor());
        d->showPopupIcon->setColor(showPopupColor());
    }
    else
    {
        d->normalIcon->setColor(disabledForegroundColor());
        d->showPopupIcon->setColor(disabledForegroundColor());
    }

    update();
}
