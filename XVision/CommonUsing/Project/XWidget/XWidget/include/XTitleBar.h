#ifndef XTITLEBAR_H
#define XTITLEBAR_H

#include "XWidgetGlobal.h"

#include <QMenu>
#include <QWidget>

#include <memory>

///无边框窗口标题栏
class QMenuBar;
class XTitleBarUi;
class QHBoxLayout;
class XWIDGET_EXPORT XTitleBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool iconIsVisible READ iconIsVisible WRITE setIconVisible)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)

public:
    XTitleBar(QWidget* parent = Q_NULLPTR);
    ~XTitleBar();

    void setMenuBar(QMenuBar* menu);
    QMenuBar* menuBar() const;

    QHBoxLayout* rightLayout() const;

    void setIconVisible(bool show);
    bool iconIsVisible() const;
    void setIconSize(const QSize& size);
    const QSize& iconSize() const;
    void setMinBtnSize(int minw, int minh);
    void setMaxBtnSize(int maxw, int maxh);

signals:
    void iconSizeChanged(const QSize& size);
private slots:
    void onCloseBtn();
    void onMaximumSizeBtn();
    void onMinimumSizeBtn();

protected:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;
    void actionEvent(QActionEvent* event) override;

private:
    QRect doIconRect() const;

private:
    XTitleBarUi* ui;

    struct Impl;
    std::unique_ptr<Impl> m_impl;
#ifdef Q_OS_WIN
    friend class XWinFramelessDelegate;
#endif

};

#endif // XTITLEBAR_H
