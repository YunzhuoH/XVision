#ifndef XDRAWERITEMTITLE_H
#define XDRAWERITEMTITLE_H

#include <QIcon>
#include <QPushButton>

#include <memory>

class XDrawerItemWidget;

class XDrawerItemTitle : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
public:
    XDrawerItemTitle(XDrawerItemWidget* parent);
    ~XDrawerItemTitle();

    void setExpand(bool expand);
    bool isExpand() const;
    void insertAction(int index, QAction* action);
    QAction* actionAt(int index) const;
    int indexOf(QAction* action) const;
    void setIconSize(const QSize& size);
    const QSize& iconSize() const;
signals:
    void iconSizeChanged(const QSize& size);

protected:
    void paintEvent(QPaintEvent* event) override;
    void actionEvent(QActionEvent* event) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
#endif //XDRAWERITEMTITLE_H
