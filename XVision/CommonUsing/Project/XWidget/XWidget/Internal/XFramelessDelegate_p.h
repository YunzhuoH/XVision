#pragma once

#include <QWidget>
#include <memory>

class QPlatformSurfaceEvent;
class XFramelessDelegate : public QObject
{
    Q_OBJECT

public:
    XFramelessDelegate(QWidget* parent, const QWidgetList& moveBars);
    XFramelessDelegate(QWidget* parent, QWidget* title);
    ~XFramelessDelegate();

    void addMoveBar(QWidget* widget);
    void removeMoveBar(QWidget* widget);
    void setShadowless(bool flag);
    bool shadowless() const;

protected:
    bool eventFilter(QObject* obj, QEvent* e) override;
    void resizeEvent(QResizeEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseDoubleClickEvent(QMouseEvent* e);
    void paintEvent(QPaintEvent* e);
    void paintShadow(QPainter& p, int shadowWidth);
    void styleChangeEvent(QEvent* e);
    void platformSurfaceEvent(QPlatformSurfaceEvent* e);

private:
    void region(const QPoint& cursorGlobalPoint);
    void updateLayout();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
