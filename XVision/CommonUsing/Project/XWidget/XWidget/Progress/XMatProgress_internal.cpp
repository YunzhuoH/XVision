#include "XMatProgress_internal.h"

/*!
 *  \class XMatProgressDelegate
 *  \internal
 */

XMatProgressDelegate::XMatProgressDelegate(XMatProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_offset(0)
{
    Q_ASSERT(parent);
}

XMatProgressDelegate::~XMatProgressDelegate()
{
}
