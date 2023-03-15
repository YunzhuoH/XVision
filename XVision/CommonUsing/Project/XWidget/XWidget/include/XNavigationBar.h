#ifndef XNAVIGATIONBAR_H
#define XNAVIGATIONBAR_H

#include "XWidgetGlobal.h"

#include <QAction>
#include <QWidget>

#include <memory>


class XNavigationSidePane;

class XWIDGET_EXPORT XNavigationBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
public:
    enum ActionPosition
    {
        Left,
        Center,
        Right
    };
    XNavigationBar(QWidget* parent);
    ~XNavigationBar();

    void addAction(QAction* action, ActionPosition pos);
    QAction* addAction(const QIcon& icon, const QString& text, ActionPosition pos);
    QAction* addAction(const QString& text, ActionPosition pos);
    void insertAction(int index, QAction* action, ActionPosition pos);
    QAction* insertAction(int index, const QIcon& icon, const QString& text, ActionPosition pos);
    QAction* insertAction(int index, const QString& text, ActionPosition pos);
    QAction* addSeparator(ActionPosition pos);
    QAction* insertSeparator(int index, ActionPosition pos);
    void addPane(QAction* action, ActionPosition pos, XNavigationSidePane* pane);
    QAction* addPane(const QIcon& icon, const QString& text, ActionPosition pos, XNavigationSidePane* pane);
    QAction* addPane(const QString& text, ActionPosition pos, XNavigationSidePane* pane);
    void insertPane(int index, QAction* action, ActionPosition pos, XNavigationSidePane* pane);
    QAction* insertPane(int index, const QIcon& icon, const QString& text, ActionPosition pos, XNavigationSidePane* pane);
    QAction* insertPane(int index, const QString& text, ActionPosition pos, XNavigationSidePane* pane);
    QAction* addHelp(const QUrl& filePath, const QIcon& icon, ActionPosition pos = Right);
    QAction* insertHelp(int index, const QUrl& filePath, const QIcon& icon, ActionPosition pos = Right);
    QAction* addLogo(const QIcon& icon, ActionPosition pos = Left);
    QAction* insertLogo(int index, const QIcon& icon, ActionPosition pos = Left);
    QAction* addUser(const QIcon& icon, const QString& text, ActionPosition pos = Right);
    QAction* insertUser(int index, const QIcon& icon, const QString& text, ActionPosition pos = Right);
    int indexOf(QAction* action) const;
    int count(ActionPosition pos) const;
    QRect actionRect(QAction* action);
    QAction* actionAt(int index, ActionPosition pos) const;
    void setIconSize(const QSize& size);
    const QSize& iconSize() const;
signals:
    void iconSizeChanged(const QSize& size);

protected:
    void actionEvent(QActionEvent* event) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
#endif // XNAVIGATIONBAR_H
