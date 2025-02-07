﻿#ifndef XMATCIRCULARPROGRESS_INTERNAL_H
#define XMATCIRCULARPROGRESS_INTERNAL_H

#include <QObject>
#include "XMatCircularProgress.h"

class XMatCircularProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
    Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
    Q_PROPERTY(int angle WRITE setAngle READ angle)

public:
    XMatCircularProgressDelegate(XMatCircularProgress *parent);
    ~XMatCircularProgressDelegate();

    inline void setDashOffset(qreal offset);
    inline qreal dashOffset() const;

    inline void setDashLength(qreal length);
    inline qreal dashLength() const;

    inline void setAngle(int angle);
    inline int angle() const;

private:
    Q_DISABLE_COPY(XMatCircularProgressDelegate)

    XMatCircularProgress *const m_progress;
    qreal                             m_dashOffset;
    qreal                             m_dashLength;
    int                               m_angle;
};

inline void XMatCircularProgressDelegate::setDashOffset(qreal offset)
{
    m_dashOffset = offset;
    m_progress->update();
}

inline qreal XMatCircularProgressDelegate::dashOffset() const
{
    return m_dashOffset;
}

inline void XMatCircularProgressDelegate::setDashLength(qreal length)
{
    m_dashLength = length;
    m_progress->update();
}

inline qreal XMatCircularProgressDelegate::dashLength() const
{
    return m_dashLength;
}

inline void XMatCircularProgressDelegate::setAngle(int angle)
{
    m_angle = angle;
    m_progress->update();
}

inline int XMatCircularProgressDelegate::angle() const
{
    return m_angle;
}

#endif // XMATCIRCULARPROGRESS_INTERNAL_H
