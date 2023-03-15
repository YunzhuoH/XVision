#ifndef XMATLINEEDIT_P_H
#define XMATLINEEDIT_P_H

#include <QtGlobal>
#include <QColor>

class XMatLineEdit;
class XMatLineEditStateMachine;
class XMatLineEditLabel;

class XMatLineEditPrivate
{
    Q_DISABLE_COPY(XMatLineEditPrivate)
    Q_DECLARE_PUBLIC(XMatLineEdit)

public:
    XMatLineEditPrivate(XMatLineEdit *q);
    virtual ~XMatLineEditPrivate();

    void init();

    XMatLineEdit             *const q_ptr;
    XMatLineEditStateMachine *stateMachine;
    XMatLineEditLabel        *label;
    QColor                           textColor;
    QColor                           labelColor;
    QColor                           inkColor;
    QColor                           inputLineColor;
    QString                          labelString;
    qreal                            labelFontSize;
    bool                             showLabel;
    bool                             showInputLine;
};

#endif // XMATLINEEDIT_P_H
