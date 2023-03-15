#ifndef XFRAMELESSDIALOG_H
#define XFRAMELESSDIALOG_H

#include "XWidgetGlobal.h"
#include <QDialog>
#include <memory>

class XTitleBar;
class XWIDGET_EXPORT XFramelessDialog:public QDialog
{
    Q_OBJECT

public:
    explicit XFramelessDialog(QWidget* parent = nullptr);
    ~XFramelessDialog();

    void setCentralWidget(QWidget* widget);
    QWidget* centralWidget() const;
    void setTitleBar(XTitleBar* titleBar);
    XTitleBar* titleBar() const;
    void addMoveBar(QWidget* moveBar);
    void removeMoveBar(QWidget* moveBar);
#ifndef Q_OS_WIN
    void setShadowless(bool flag);
    bool shadowless() const;
#endif
protected:
    void hideEvent(QHideEvent*) override;
    bool eventFilter(QObject*, QEvent*) override;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#else
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
#endif
private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
#endif // XFRAMELESSDIALOG_H
