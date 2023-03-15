#include "XMatCircularProgress_internal.h"

/*!
 *  \class XMatCircularProgressDelegate
 *  \internal
 */

XMatCircularProgressDelegate::XMatCircularProgressDelegate(XMatCircularProgress *parent)
    : QObject(parent),
      m_progress(parent),
      m_dashOffset(0),
      m_dashLength(89),
      m_angle(0)
{
    Q_ASSERT(parent);
}

XMatCircularProgressDelegate::~XMatCircularProgressDelegate()
{
}
