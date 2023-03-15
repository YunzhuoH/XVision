#ifndef XNAVIGATIONSIDEPANE_H
#define XNAVIGATIONSIDEPANE_H

#include "XWidgetGlobal.h"

#include <QScrollArea>

#include <memory>

class XNavigationBar;

class XWIDGET_EXPORT XNavigationSidePane : public QWidget
{
    Q_OBJECT

public:
    enum class DockArea
    {
        Left,
        Top,
        Right,
        Bottom
    };
    explicit XNavigationSidePane(XNavigationBar* parent);
    XNavigationSidePane(DockArea area, XNavigationBar* parent);
    ~XNavigationSidePane();

    void setDockArea(DockArea area);
    DockArea dockArea() const;
    void setWidget(QWidget* widget);
    QWidget* widget() const;
    QScrollArea* viewContainer() const;
    void setTitleBarVisible(bool visible);
    bool titleBarIsVisible() const;
    void setTitle(const QString& text);
    QString title() const;
    void setPopup(bool popup);
    bool popup() const;
signals:
    void paneClosed();

protected:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    QSize sizeHint() const override;
    bool eventFilter(QObject* o, QEvent* e) override;
    void mousePressEvent(QMouseEvent* event) override;

    virtual QPoint smartPosition(DockArea area) const;
    virtual QSize smartSize(DockArea area) const;

    void setNavigationBar(XNavigationBar* bar);
    XNavigationBar* navigationBar() const;

private:
    void bindAction(QAction* action);
    void paintShadow(int shadowWidth);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;

    friend class XNavigationBar;
};

#endif // XNAVIGATIONSIDEPANE_H
