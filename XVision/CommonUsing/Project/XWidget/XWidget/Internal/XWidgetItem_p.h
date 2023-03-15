#pragma once

#include <QWidget>

#include <memory>

class XWidgetItem : public QObject
{
    Q_OBJECT
public:
    XWidgetItem(QAction* action, Qt::Orientation orientation, const QSize& iconSize = QSize(16, 16), QWidget* parent = nullptr);
    ~XWidgetItem();

    void release();

    QAction* action() const;
    QWidget* widget() const;
    bool isCustomWidget() const;
signals:
    void iconSizeChanged(const QSize& size);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

typedef std::shared_ptr<XWidgetItem> XWidgetItemPtr;
