#ifndef XFRAMELESSWIDGET_H
#define XFRAMELESSWIDGET_H

#include "XWidgetGlobal.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QWidget>
#include <memory>

///无边框窗口-Widget
/// 使用说明:
/// 需要设置为中心widget,不然会错位ui->setupUi(this->centralWidget())
/// 设置中心Widget需要手动connect

class XNavigationBar;
class XTitleBar;
class UiXFramelessWidget;

class XWIDGET_EXPORT XFramelessWidget : public QWidget
{
    Q_OBJECT

public:
    XFramelessWidget(QWidget* parent = nullptr);
    ~XFramelessWidget();

    void setStatusBar(QStatusBar* statusBar);
    QStatusBar* statusBar() const;
    void setMenuBar(QMenuBar* menuBar);
    QMenuBar* menuBar() const;
    void setNavigationBar(XNavigationBar* menuBar);
    XNavigationBar* navigationBar() const;
    void setTitleBar(XTitleBar* titleBar);
    XTitleBar* titleBar() const;
    void setCentralWidget(QWidget* widget);
    QWidget* centralWidget() const;
    void addMoveBar(QWidget* moveBar);
    void removeMoveBar(QWidget* moveBar);
#ifndef Q_OS_WIN
    void setShadowless(bool flag);
    bool shadowless() const;
#endif
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#else
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#endif
private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
    UiXFramelessWidget* ui;

};



#endif //XFRAMELESSWIDGET_H
