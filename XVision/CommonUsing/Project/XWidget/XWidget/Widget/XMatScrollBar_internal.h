#ifndef XMATSCROLLBAR_INTERNAL_H
#define XMATSCROLLBAR_INTERNAL_H

#include <QStateMachine>
#include "XMatScrollBar.h"

class XMatScrollBarStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    XMatScrollBarStateMachine(XMatScrollBar *parent);
    ~XMatScrollBarStateMachine();

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

private:
    Q_DISABLE_COPY(XMatScrollBarStateMachine)

    XMatScrollBar *const m_scrollBar;
    QState              *const m_focusState;
    QState              *const m_blurState;
    qreal                m_opacity;
};

inline void XMatScrollBarStateMachine::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_scrollBar->update();
}

inline qreal XMatScrollBarStateMachine::opacity() const
{
    return m_opacity;
}

#endif // XMATSCROLLBAR_INTERNAL_H
