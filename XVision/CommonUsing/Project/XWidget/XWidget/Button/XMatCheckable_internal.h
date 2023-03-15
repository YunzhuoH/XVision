#ifndef XMATCHECKABLE_INTERNAL_H
#define XMATCHECKABLE_INTERNAL_H

#include <QWidget>
#include <QColor>
#include <QIcon>

class XMatCheckable;

class XMatCheckableIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    XMatCheckableIcon(const QIcon &icon, XMatCheckable *parent);
    ~XMatCheckableIcon();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    inline void setIcon(const QIcon &icon);
    inline QIcon icon() const;

    inline void setColor(const QColor &color);
    inline QColor color() const;

    inline void setIconSize(qreal size);
    inline qreal iconSize() const;

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatCheckableIcon)

    XMatCheckable *const m_checkable;
    QColor                     m_color;
    QIcon                      m_icon;
    qreal                      m_iconSize;
    qreal                      m_opacity;
};

inline void XMatCheckableIcon::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

inline QIcon XMatCheckableIcon::icon() const
{
    return m_icon;
}

inline void XMatCheckableIcon::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor XMatCheckableIcon::color() const
{
    return m_color;
}

inline void XMatCheckableIcon::setIconSize(qreal size)
{
    m_iconSize = size;
    update();
}

inline qreal XMatCheckableIcon::iconSize() const
{
    return m_iconSize;
}

inline void XMatCheckableIcon::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

inline qreal XMatCheckableIcon::opacity() const
{
    return m_opacity;
}

#endif // XMATCHECKABLE_INTERNAL_H
