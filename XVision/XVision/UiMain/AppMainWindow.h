#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QWidget>
#include "XFramelessWidget.h"

class AppMainWindowPrivate;
class XvSingleApplication;
class AppMainWindow : public XFramelessWidget
{
    Q_OBJECT

public:
    explicit AppMainWindow(XvSingleApplication *app=nullptr,QWidget *parent = nullptr);
    ~AppMainWindow();

public:
    bool addToolBarAction(QAction *act);
protected:
    const QScopedPointer<AppMainWindowPrivate> d_ptr;
private:
     Q_DISABLE_COPY(AppMainWindow)
     Q_DECLARE_PRIVATE(AppMainWindow)

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    XvSingleApplication* m_app;
};

#endif // APPMAINWINDOW_H
