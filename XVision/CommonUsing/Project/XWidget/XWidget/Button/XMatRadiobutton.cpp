#include "XMatRadioButton.h"
#include "XMatRadioButton_p.h"
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QColor>
#include "XMatCheckable_internal.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatRadioButtonPrivate
 *  \internal
 */

XMatRadioButtonPrivate::XMatRadioButtonPrivate(XMatRadioButton *q)
    : XMatCheckablePrivate(q)
{
    checkedColor=C_XMatThemeColor;
    uncheckedColor=QColor(60,60,60);
    textColor=C_XMatFontdColor;
    disabledColor=C_XMatDisableForegroundColor;
}

XMatRadioButtonPrivate::~XMatRadioButtonPrivate()
{
}

void XMatRadioButtonPrivate::init()
{
    Q_Q(XMatRadioButton);

    q->setAutoExclusive(true);

    checkedIcon->setIcon(QIcon(":/res/images/RadioButtonChecked24px.svg"));
    uncheckedIcon->setIcon(QIcon(":/res/images/RadioButtonUnChecked24px.svg"));

    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    uncheckedState->assignProperty(uncheckedIcon, "iconSize", 24);

    disabledUncheckedState->assignProperty(checkedIcon, "iconSize", 0);
    disabledUncheckedState->assignProperty(uncheckedIcon, "iconSize", 24);

    checkedState->assignProperty(uncheckedIcon, "iconSize", 0);
    checkedState->assignProperty(checkedIcon, "iconSize", 24);

    disabledCheckedState->assignProperty(uncheckedIcon, "iconSize", 0);
    disabledCheckedState->assignProperty(checkedIcon, "iconSize", 24);

    uncheckedState->assignProperty(checkedIcon, "opacity", 0);
    uncheckedState->assignProperty(uncheckedIcon, "opacity", 1);

    checkedState->assignProperty(uncheckedIcon, "opacity", 0);
    checkedState->assignProperty(checkedIcon, "opacity", 1);

    checkedIcon->setIconSize(0);

    //

    checkedState->assignProperty(checkedIcon, "color", q->checkedColor());
    checkedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());
    uncheckedState->assignProperty(uncheckedIcon, "color", q->uncheckedColor());

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "iconSize", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(250);
    stateMachine->addDefaultAnimation(animation);

    q->setText("XMatRadioButton");
}

/*!
 *  \class XMatRadioButton
 */

XMatRadioButton::XMatRadioButton(QWidget *parent)
    : XMatCheckable(*new XMatRadioButtonPrivate(this), parent)
{
    d_func()->init();
}

XMatRadioButton::~XMatRadioButton()
{
}

void XMatRadioButton::setupProperties()
{
    XMatCheckable::setupProperties();

    Q_D(XMatRadioButton);

    d->checkedState->assignProperty(d->checkedIcon, "color", checkedColor());
    d->checkedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
    d->uncheckedState->assignProperty(d->uncheckedIcon, "color", uncheckedColor());
}

