#ifndef XMATTABS_INTERNAL_H
#define XMATTABS_INTERNAL_H

#include "XMatOverlayWidget.h"


class QPropertyAnimation;
class XMatTabs;

class XMatTabsInkBar : public XMatOverlayWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

public:
    XMatTabsInkBar(XMatTabs *parent);
    ~XMatTabsInkBar();

    inline void setTweenValue(qreal value);
    inline qreal tweenValue() const;

    void refreshGeometry();
    void animate();

protected:
    bool eventFilter(QObject *obj, QEvent *event)  Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatTabsInkBar)

    XMatTabs     *const m_tabs;
    QPropertyAnimation *const m_animation;
    QRect                     m_geometry;
    QRect                     m_previousGeometry;
    qreal                     m_tween;
};

inline void XMatTabsInkBar::setTweenValue(qreal value)
{
    m_tween = value;
    refreshGeometry();
}

inline qreal XMatTabsInkBar::tweenValue() const
{
    return m_tween;
}



#endif // XMATTABS_INTERNAL_H
