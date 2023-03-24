#include "XMatCheckBox.h"
#include "XMatCheckBox_p.h"
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include "XMatCheckable_internal.h"
#include "XMatStyleDef.h"
/*!
 *  \class XMatCheckBoxPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatCheckBoxPrivate::XMatCheckBoxPrivate(XMatCheckBox *q)
    : XMatCheckablePrivate(q)
{
    checkedColor=C_XMatThemeColor;
    uncheckedColor=QColor(60,60,60);
    textColor=C_XMatFontdColor;
    disabledColor=C_XMatDisableForegroundColor;

}

/*!
 *  \internal
 */
XMatCheckBoxPrivate::~XMatCheckBoxPrivate()
{
}

/*!
 *  \internal
 */
void XMatCheckBoxPrivate::init()
{
    Q_Q(XMatCheckBox);

    checkedIcon->setIcon(QIcon(":/images/CheckBox24px.svg"));
    uncheckedIcon->setIcon(QIcon(":/images/CheckBoxOutlineBlank24px.svg"));
    checkedState->assignProperty(checkedIcon, "iconSize", 24);
    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(300);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(1300);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    q->setText("XMatCheckBox");
}

/*!
 *  \class XMatCheckBox
 */

XMatCheckBox::XMatCheckBox(QWidget *parent)
    : XMatCheckable(*new XMatCheckBoxPrivate(this), parent)
{
    d_func()->init();
}

XMatCheckBox::~XMatCheckBox()
{
}

