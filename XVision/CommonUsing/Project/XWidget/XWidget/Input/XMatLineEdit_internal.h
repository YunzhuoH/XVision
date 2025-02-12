﻿#ifndef XMATLINEEDIT_INTERNAL_H
#define XMATLINEEDIT_INTERNAL_H

#include <QStateMachine>
#include <QtWidgets/QWidget>
#include "XMatLineEdit.h"

class QPropertyAnimation;
class XMatLineEditLabel;

class XMatLineEditStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    XMatLineEditStateMachine(XMatLineEdit *parent);
    ~XMatLineEditStateMachine();

    void setLabel(XMatLineEditLabel *label);

    inline void setProgress(qreal progress);
    inline qreal progress() const;

public slots:
    void setupProperties();

private:
    Q_DISABLE_COPY(XMatLineEditStateMachine)

    XMatLineEdit *const m_textField;
    QState              *const m_normalState;
    QState              *const m_focusedState;
    XMatLineEditLabel  *m_label;
    QPropertyAnimation        *m_offsetAnimation;
    QPropertyAnimation        *m_colorAnimation;
    qreal                      m_progress;
};

inline void XMatLineEditStateMachine::setProgress(qreal progress)
{
    m_progress = progress;
    m_textField->update();
}

inline qreal XMatLineEditStateMachine::progress() const
{
    return m_progress;
}

class XMatLineEditLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal scale WRITE setScale READ scale)
    Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    XMatLineEditLabel(XMatLineEdit *parent);
    ~XMatLineEditLabel();

    inline void setScale(qreal scale);
    inline qreal scale() const;

    inline void setOffset(const QPointF &pos);
    inline QPointF offset() const;

    inline void setColor(const QColor &color);
    inline QColor color() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatLineEditLabel)

    XMatLineEdit *const m_textField;
    qreal                      m_scale;
    qreal                      m_posX;
    qreal                      m_posY;
    QColor                     m_color;
};

inline void XMatLineEditLabel::setScale(qreal scale)
{
    m_scale = scale;
    update();
}

inline qreal XMatLineEditLabel::scale() const
{
    return m_scale;
}

inline void XMatLineEditLabel::setOffset(const QPointF &pos)
{
    m_posX = pos.x();
    m_posY = pos.y();
    update();
}

inline QPointF XMatLineEditLabel::offset() const
{
    return QPointF(m_posX, m_posY);
}

inline void XMatLineEditLabel::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor XMatLineEditLabel::color() const
{
    return m_color;
}

#endif // XMATLINEEDIT_INTERNAL_H
