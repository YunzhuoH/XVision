#ifndef XWINDOWEVENTFILTER_WIN_H
#define XWINDOWEVENTFILTER_WIN_H

#include "XWidgetGlobal.h"
#include <QAbstractNativeEventFilter>

#ifdef Q_OS_WIN
#include <qt_windows.h>
///Windows系统下的nativeEvent过滤器
class XWIDGET_EXPORT XWindowEventFilter_Win : public QAbstractNativeEventFilter
{
public:

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;
#else
    bool nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) override;
#endif

};

#endif // Q_OS_WIN

#endif // XWINDOWEVENTFILTER_WIN_H
