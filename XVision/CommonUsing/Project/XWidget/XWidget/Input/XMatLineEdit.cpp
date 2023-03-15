#include "XMatLineEdit.h"
#include "XMatLineEdit_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "XMatLineEdit_internal.h"
#include "XMatStyleDef.h"
#include <QDebug>

/*!
 *  \class XMatLineEditPrivate
 *  \internal
 */

XMatLineEditPrivate::XMatLineEditPrivate(XMatLineEdit *q)
    : q_ptr(q)
{
   textColor=C_XMatFontdColor;
   labelColor=C_XMatThemeColor;
   inkColor=C_XMatThemeColor;
   inputLineColor=QColor(170,170,170,170);;
}

XMatLineEditPrivate::~XMatLineEditPrivate()
{
}

void XMatLineEditPrivate::init()
{
    Q_Q(XMatLineEdit);

    stateMachine   = new XMatLineEditStateMachine(q);
    label          = 0;
    labelFontSize  = 9.5;
    showLabel      = false;
    showInputLine  = true;


    q->setFrame(false);
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setTextMargins(0, 2, 0, 4);

    q->setFont(C_XMatFont);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class XMatLineEdit
 */

XMatLineEdit::XMatLineEdit(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new XMatLineEditPrivate(this))
{
    d_func()->init();
}

XMatLineEdit::~XMatLineEdit()
{
}


void XMatLineEdit::setShowLabel(bool value)
{
    Q_D(XMatLineEdit);

    if (d->showLabel == value) {
        return;
    }

    d->showLabel = value;

    if (!d->label && value) {
        d->label = new XMatLineEditLabel(this);
        d->stateMachine->setLabel(d->label);
    }

    if (value) {
        setContentsMargins(0, 23, 0, 0);
    } else {
        setContentsMargins(0, 0, 0, 0);
    }
}

bool XMatLineEdit::hasLabel() const
{
    Q_D(const XMatLineEdit);

    return d->showLabel;
}

void XMatLineEdit::setLabelFontSize(qreal size)
{

    Q_D(XMatLineEdit);

    d->labelFontSize = size;

    if (d->label)
    {
        QFont font(d->label->font());
        font.setPointSizeF(size);
        d->label->setFont(font);
        d->label->update();
    }
}

qreal XMatLineEdit::labelFontSize() const
{
    Q_D(const XMatLineEdit);

    return d->labelFontSize;
}

void XMatLineEdit::setLabel(const QString &label)
{
    Q_D(XMatLineEdit);

    d->labelString = label;
    setShowLabel(true);
    d->label->update();
}

QString XMatLineEdit::label() const
{
    Q_D(const XMatLineEdit);

    return d->labelString;
}

void XMatLineEdit::setTextColor(const QColor &color)
{
    Q_D(XMatLineEdit);

    d->textColor = color;
    setStyleSheet(QString("QLineEdit { color: %1; }").arg(color.name()));


    d->stateMachine->setupProperties();
}

QColor XMatLineEdit::textColor() const
{
    Q_D(const XMatLineEdit);

    return d->textColor;
}

void XMatLineEdit::setLabelColor(const QColor &color)
{
    Q_D(XMatLineEdit);

    d->labelColor = color;   
    d->stateMachine->setupProperties();
}

QColor XMatLineEdit::labelColor() const
{
    Q_D(const XMatLineEdit);

    return d->labelColor;
}

void XMatLineEdit::setInkColor(const QColor &color)
{
    Q_D(XMatLineEdit);

    d->inkColor = color;


    d->stateMachine->setupProperties();
}

QColor XMatLineEdit::inkColor() const
{
    Q_D(const XMatLineEdit);

    return d->inkColor;
}

void XMatLineEdit::setInputLineColor(const QColor &color)
{
    Q_D(XMatLineEdit);

    d->inputLineColor = color;


    d->stateMachine->setupProperties();
}

QColor XMatLineEdit::inputLineColor() const
{
    Q_D(const XMatLineEdit);

     return d->inputLineColor;
}

void XMatLineEdit::setShowInputLine(bool value)
{
    Q_D(XMatLineEdit);

    if (d->showInputLine == value) {
        return;
    }

    d->showInputLine = value;
    update();
}

bool XMatLineEdit::hasInputLine() const
{
    Q_D(const XMatLineEdit);
    return d->showInputLine;
}

XMatLineEdit::XMatLineEdit(XMatLineEditPrivate &d, QWidget *parent)
    : QLineEdit(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool XMatLineEdit::event(QEvent *event)
{
    Q_D(XMatLineEdit);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        if (d->label) {
            d->label->setGeometry(rect());
        }
    }
    default:
        break;
    }
    return QLineEdit::event(event);
}

/*!
 *  \reimp
 */
void XMatLineEdit::paintEvent(QPaintEvent *event)
{
    Q_D(XMatLineEdit);

    QLineEdit::paintEvent(event);

    QPainter painter(this);

    const qreal progress = d->stateMachine->progress();

    if (text().isEmpty() && progress < 1)
    {
        painter.setOpacity(1-progress);
        painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
    }

    const int y = height()-1;
    const int wd = width()-5;

    if (d->showInputLine)
    {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(inputLineColor());

        if (!isEnabled()) 
            pen.setStyle(Qt::DashLine);

        painter.setPen(pen);
        painter.setOpacity(1);
        painter.drawLine(QLineF(2.5, y, wd, y));

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(inkColor());

        if (progress > 0)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            const int w = (1-progress)*static_cast<qreal>(wd/2);
            painter.drawRect(w+2.5, height()-2, wd-w*2, 2);
        }
    }
}
