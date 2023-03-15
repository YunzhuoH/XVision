#ifndef XMATPROGRESS_INTERNAL_H
#define XMATPROGRESS_INTERNAL_H

#include <QObject>
#include "XMatProgress.h"

class XMatProgressDelegate : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal offset WRITE setOffset READ offset)

public:
    XMatProgressDelegate(XMatProgress *parent);
    ~XMatProgressDelegate();

    inline void setOffset(qreal offset);
    inline qreal offset() const;

private:
    Q_DISABLE_COPY(XMatProgressDelegate)

    XMatProgress *const m_progress;
    qreal                     m_offset;
};

inline void XMatProgressDelegate::setOffset(qreal offset)
{
    m_offset = offset;
    m_progress->update();
}

inline qreal XMatProgressDelegate::offset() const
{
    return m_offset;
}

#endif // XMATPROGRESS_INTERNAL_H
