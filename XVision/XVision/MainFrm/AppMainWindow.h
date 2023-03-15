#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QWidget>
#include "XFramelessWidget.h"

class AppMainWindowPrivate;
class AppMainWindow : public XFramelessWidget
{
    Q_OBJECT

public:
    explicit AppMainWindow(QWidget *parent = nullptr);
    ~AppMainWindow();

protected:
    const QScopedPointer<AppMainWindowPrivate> d_ptr;
private:
     Q_DISABLE_COPY(AppMainWindow)
     Q_DECLARE_PRIVATE(AppMainWindow)
};

#endif // APPMAINWINDOW_H
