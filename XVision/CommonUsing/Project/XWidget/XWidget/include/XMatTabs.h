#ifndef XMATTABS_H
#define XMATTABS_H

#include "XWidgetGlobal.h"
#include <QWidget>
#include <QIcon>
#include "XMatCommonDef.h"

class XMatTabsPrivate;
class XMatTab;

class XWIDGET_EXPORT XMatTabs : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(XMatCommonDef::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
public:
    explicit XMatTabs(QWidget *parent = 0);
    ~XMatTabs();
public:



    void setHaloVisible(bool value);
    bool isHaloVisible() const;

    void setRippleStyle(XMatCommonDef::RippleStyle style);
    XMatCommonDef::RippleStyle rippleStyle() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void addTab(const QString &text, const QIcon &icon = QIcon());

    void setCurrentTab(XMatTab *tab);
    void setCurrentTab(int index);

    int currentIndex() const;

    void setTabsMinimumHeight(int minh);
    void setTabsMaximumHeight(int maxh);
signals:
    void currentChanged(int);

protected:
    void setTabActive(int index, bool active = true);
    void updateTabs();

    const QScopedPointer<XMatTabsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatTabs)
    Q_DECLARE_PRIVATE(XMatTabs)
};

#endif // XMATTABS_H
