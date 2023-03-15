#pragma once

#include <QWidget>

#include <functional>
#include <memory>

#ifdef Q_OS_WIN

using MSG = struct tagMSG;
class XWinFramelessDelegate : public QObject
{
    Q_OBJECT

public:
    XWinFramelessDelegate(QWidget* parent, const QWidgetList& moveBars);
    XWinFramelessDelegate(QWidget* parent, QWidget* title);
    ~XWinFramelessDelegate();

    void addMoveBar(QWidget* w);
    void removeMoveBar(QWidget* w);
#if defined(XWIDGET_COMPILE_NOT_MSVC) //Mingw情况下才编译
    bool shadowless() const;
    void setShadowless(bool flag);
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#else
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#endif
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
#if defined(XWIDGET_COMPILE_NOT_MSVC)  //Mingw情况下才编译
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
#endif
private:
#if defined(XWIDGET_COMPILE_NOT_MSVC)  //Mingw情况下才编译
    void region(const QPoint& cursorGlobalPoint);
#endif
    void setWindowLong();
    void showSystemMenu(const QPoint& pos);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool onNCTitTest(MSG* msg, long* result);
#else
    bool onNCTitTest(MSG* msg, qintptr* result);
#endif
private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
    friend class XWindowEventFilter_Win;
};
#endif
