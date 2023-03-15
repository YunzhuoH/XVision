#ifndef XDRAWERWIDGET_H
#define XDRAWERWIDGET_H

#include "XWidgetGlobal.h"

#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QMap>
#include <QMouseEvent>
#include <QPushButton>
#include <QScrollArea>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>

class XDrawerItemWidget;
class XWIDGET_EXPORT XDrawerWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool exclusive READ exclusive WRITE setExclusive)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
public:
    explicit XDrawerWidget(QWidget* parent = nullptr);
    ~XDrawerWidget();

    XDrawerItemWidget* addWidget(const QString& title, QWidget* widget);
    XDrawerItemWidget* insertWidget(int index, const QString& title, QWidget* widget);
    void removeItem(XDrawerItemWidget* item);
    int indexOf(XDrawerItemWidget* item) const;
    XDrawerItemWidget* item(int index) const;
    int count() const;
    void setExclusive(bool exclusive);
    bool exclusive() const;
    void setSizes(const QList<int>& sizes);
    void setIconSize(const QSize& size);
    const QSize& iconSize() const;
signals:
    void itemExpandChanged(XDrawerItemWidget* item, bool expand);
    void itemTitleClicked(XDrawerItemWidget* item, bool expand);
    void iconSizeChanged(const QSize& size);
public slots:
    void expandAll();
    void collapseAll();

protected:
    bool isAllCollapsed() const;
    int totalSize(const QList<int>& sizes) const;
    void showEvent(QShowEvent* event) override;
private slots:
    void childExpandChanged(XDrawerItemWidget* item, bool expand);
    void doResize();
    void onItemExpand(bool expand);
    void onItemClicked(bool expand);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
#endif //XDRAWERWIDGET_H
