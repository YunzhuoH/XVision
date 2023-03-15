#ifndef XDRAWERITEMWIDGET_H
#define XDRAWERITEMWIDGET_H

#include "XWidgetGlobal.h"

#include <QWidget>

class XDrawerWidget;

class XWIDGET_EXPORT XDrawerItemWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
public:
    void setWidget(QWidget* widget);
    QWidget* widget() const;
    void setTitle(const QString& title);
    QString title() const;
    bool isExpand() const;
    void setExpand(bool expand);
    QAction* addAction(const QIcon& icon, const QString& text);
    QAction* addAction(const QIcon& icon);
    QAction* addAction(const QString& text);
    QAction* insertAction(int index, const QIcon& icon, const QString& text);
    QAction* insertAction(int index, const QString& text);
    void removeAction(QAction* action);
    int count() const;
    int indexOf(QAction* action);
    QAction* actionAt(int index);
    void setIconSize(const QSize& size);
    const QSize& iconSize() const;
signals:
    void expandChanged(bool expand);
    void titleClicked(bool expand);
    void iconSizeChanged(const QSize& size);

protected:
    XDrawerItemWidget(const QString& title, XDrawerWidget* parent);
    ~XDrawerItemWidget();

private slots:
    void onClicked();
    void resizeEvent(QResizeEvent* event);

private:
    int suggestSize() const;
    void setSuggestSize(int size);
    void insertAction(int index, QAction* action);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;

    friend class XDrawerWidget;
};
#endif  //XDRAWERITEMWIDGET_H
