#ifndef XMATDRAWER_H
#define XMATDRAWER_H


#include "XMatOverlayWidget.h"

class XMatDrawerPrivate;
class XMatDrawerStateMachine;

class XWIDGET_EXPORT XMatDrawer : public XMatOverlayWidget
{
    Q_OBJECT

public:
    enum DrawerDir
    {
        Left,
        Right,
    };

    explicit XMatDrawer(QWidget *parent = 0,DrawerDir dir=DrawerDir::Left);
    ~XMatDrawer();

    DrawerDir drawerDir() const;

    void setDrawerWidth(int width);
    int drawerWidth() const;

    void setDrawerHeight(int height);
    int drawerHeight() const;

    void setDrawerOffsetY(int offsetY);
    int drawerOffsetY() const;

    void setDrawerLayout(QLayout *layout);
    QLayout *drawerLayout() const;

    void setClickOutsideToClose(bool state);
    bool clickOutsideToClose() const;

    void setAutoRaise(bool state);
    bool autoRaise() const;

    void setOverlayMode(bool value);
    bool overlayMode() const;

    bool isCloseState();
public slots:
    void openDrawer();
    void closeDrawer();
protected:
    void updateMask();
protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatDrawerPrivate> d_ptr;
private:
    DrawerDir m_dir;
private:
    Q_DISABLE_COPY(XMatDrawer)
    Q_DECLARE_PRIVATE(XMatDrawer)
};

#endif // XMATDRAWER_H
