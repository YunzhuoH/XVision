#ifndef XMATCOMBOBOX_INTERNAL_H
#define XMATCOMBOBOX_INTERNAL_H


#include <QWidget>
#include <QStateMachine>
#include <QColor>
#include <QIcon>

class XMatComboBox;
class QSequentialAnimationGroup;


class XMatComboBoxIcon : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    XMatComboBoxIcon(const QIcon &icon, XMatComboBox *parent);
    ~XMatComboBoxIcon();

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
    Q_DISABLE_COPY(XMatComboBoxIcon)

    XMatComboBox               *const m_comboBox;
    QColor                     m_color;
    QIcon                      m_icon;
    qreal                      m_iconSize;
    qreal                      m_opacity;
};


inline void XMatComboBoxIcon::setIcon(const QIcon &icon)
{
    m_icon = icon;
    update();
}

inline QIcon XMatComboBoxIcon::icon() const
{
    return m_icon;
}

inline void XMatComboBoxIcon::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor XMatComboBoxIcon::color() const
{
    return m_color;
}

inline void XMatComboBoxIcon::setIconSize(qreal size)
{
    m_iconSize = size;
    update();
}

inline qreal XMatComboBoxIcon::iconSize() const
{
    return m_iconSize;
}

inline void XMatComboBoxIcon::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

inline qreal XMatComboBoxIcon::opacity() const
{
    return m_opacity;
}

#endif // XMATCOMBOBOX_INTERNAL_H
