#include "XWindowEventFilter_Win.h"
#include "XFramelessDelegate_win.h"

#include <QApplication>

#ifdef Q_OS_WIN
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
bool XWindowEventFilter_Win::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
#else
bool XWindowEventFilter_Win::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
#endif
{

    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_NCHITTEST)
    {
        auto w = QWidget::find(reinterpret_cast<WId>(msg->hwnd));
        if (w && w->window() && w->window() != w)
        {
            auto d = w->window()->findChild<XWinFramelessDelegate*>();
            if (d && d->onNCTitTest(msg, result))
            {
                *result = HTTRANSPARENT;
                return true;
            }
            return false;
        }
    }
    return false;
}
#endif // Q_OS_WIN
