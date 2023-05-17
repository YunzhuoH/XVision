#ifndef XMATTABS_H
#define XMATTABS_H

#include "XWidgetGlobal.h"
#include "XMatFlatButton.h"
#include <QWidget>
#include <QIcon>
#include "XMatCommonDef.h"

class XMatTab;
class XMatTabsPrivate;
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

    XMatTab* addTab(const QString &text, const QIcon &icon = QIcon());

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

class XWIDGET_EXPORT XMatTab : public XMatFlatButton
{
    Q_OBJECT

public:
    explicit XMatTab(XMatTabs *parent);
    ~XMatTab();

    inline void setActive(bool state);
    inline bool isActive() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected slots:
    void activateTab();

protected:
    void paintForeground(QPainter *painter) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatTab)

    XMatTabs *const m_tabs;
    bool                  m_active;
};

inline void XMatTab::setActive(bool state)
{
    m_active = state;
    update();
}

inline bool XMatTab::isActive() const
{
    return m_active;
}

#endif // XMATTABS_H
