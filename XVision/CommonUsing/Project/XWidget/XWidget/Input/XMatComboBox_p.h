#ifndef XMATCOMBOBOX_P_H
#define XMATCOMBOBOX_P_H

#include <QtGlobal>
#include <QColor>
#include "XMatComboBox.h"


class QStateMachine;
class QState;
class QSignalTransition;
class XMatRippleOverlay;
class XMatComboBoxIcon;//ComboBox图标

class XMatComboBoxPrivate
{
    Q_DISABLE_COPY(XMatComboBoxPrivate)
    Q_DECLARE_PUBLIC(XMatComboBox)

public:
    XMatComboBoxPrivate(XMatComboBox *q);
    virtual ~XMatComboBoxPrivate();

    void init();

    XMatComboBox                      *const q_ptr;
    XMatRippleOverlay                 *rippleOverlay;
    XMatComboBoxIcon                  *normalIcon;//常规图标
    XMatComboBoxIcon                  *showPopupIcon;//下拉图标

    QStateMachine                      *stateMachine;
    QState                             *normalState;
    QState                             *showPopupState;
  //  QState                             *disabledState;

    QSignalTransition                  *normalTransition;
    QSignalTransition                  *showPopupTransition;
    XMatCommonDef::RippleStyle        rippleStyle;
    QColor                            normalColor;//常规图标颜色
    QColor                            showPopupColor;//下拉图标颜色
    QColor                            backgroundColor;//背景颜色
    QColor                            borderColor;//边框颜色
    QColor                            textColor;//字体颜色
    QColor                            disabledForegroundColor;//失能控件背景颜色
    QColor                            disabledBackgroundColor;//失能控件字体颜色

    qreal                             fontSize;
};

#endif // XMATCOMBOBOX_P_H
