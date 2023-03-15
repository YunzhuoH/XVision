#ifndef XMATFLATBUTTON_H
#define XMATFLATBUTTON_H

#include "XWidgetGlobal.h"
#include "XMatCommonDef.h"
#include <QPushButton>
#include <QScopedPointer>


class XMatFlatButtonPrivate;

class XWIDGET_EXPORT XMatFlatButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor rippleColor WRITE setRippleColor READ rippleColor)
    Q_PROPERTY(QColor overlayColor WRITE setOverlayColor READ overlayColor)
    Q_PROPERTY(QColor disabledForegroundColor WRITE setDisabledForegroundColor READ disabledForegroundColor)
    Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)
    Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)
    Q_PROPERTY(bool haloVisible WRITE setHaloVisible READ haloVisible)
    Q_PROPERTY(XMatCommonDef::OverlayStyle overlayStyle WRITE setOverlayStyle READ overlayStyle)
    Q_PROPERTY(XMatCommonDef::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)
    Q_PROPERTY(FlatButtonIconPlacement iconPlacement WRITE setIconPlacement READ iconPlacement)
    Q_PROPERTY(qreal cornerRadius WRITE setCornerRadius READ cornerRadius)
    Q_PROPERTY(qreal baseOpacity WRITE setBaseOpacity READ baseOpacity)
    Q_PROPERTY(Qt::BGMode backgroundMode WRITE setBackgroundMode READ backgroundMode)
    Q_PROPERTY(bool hasFixedRippleRadius WRITE setHasFixedRippleRadius READ hasFixedRippleRadius)
    Q_PROPERTY(qreal fixedRippleRadius WRITE setFixedRippleRadius READ fixedRippleRadius)
    Q_PROPERTY(Qt::Alignment textAlignment WRITE setTextAlignment READ textAlignment)
public:
    enum FlatButtonPreset {
           FlatPreset,
           CheckablePreset
       };
       Q_ENUM(FlatButtonPreset)

       enum FlatButtonIconPlacement {
           LeftIcon,
           RightIcon
       };
        Q_ENUM(FlatButtonIconPlacement)

    explicit XMatFlatButton(QWidget *parent = 0, FlatButtonPreset preset = FlatButtonPreset::FlatPreset);
    explicit XMatFlatButton(const QString &text, QWidget *parent = 0, FlatButtonPreset preset = FlatButtonPreset::FlatPreset);
    ~XMatFlatButton();

    void applyPreset(FlatButtonPreset preset);

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setRippleColor(const QColor &color);
    QColor rippleColor() const;

    void setOverlayColor(const QColor &color);
    QColor overlayColor() const;

    void setDisabledForegroundColor(const QColor &color);
    QColor disabledForegroundColor() const;

    void setDisabledBackgroundColor(const QColor &color);
    QColor disabledBackgroundColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setHaloVisible(bool visible);
    bool haloVisible() const;

    void setOverlayStyle(XMatCommonDef::OverlayStyle style);
    XMatCommonDef::OverlayStyle overlayStyle() const;

    void setRippleStyle(XMatCommonDef::RippleStyle style);
    XMatCommonDef::RippleStyle rippleStyle() const;

    void setIconPlacement(FlatButtonIconPlacement placement);
    FlatButtonIconPlacement iconPlacement() const;

    void setCornerRadius(qreal radius);
    qreal cornerRadius() const;

    void setBackgroundMode(Qt::BGMode mode);
    Qt::BGMode backgroundMode() const;

    void setBaseOpacity(qreal opacity);
    qreal baseOpacity() const;

    void setCheckable(bool value);

    void setHasFixedRippleRadius(bool value);
    bool hasFixedRippleRadius() const;

    void setFixedRippleRadius(qreal radius);
    qreal fixedRippleRadius() const;

    void setTextAlignment(Qt::Alignment alignment);
    Qt::Alignment textAlignment() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    enum {
        IconPadding = 12
    };

    XMatFlatButton(XMatFlatButtonPrivate &d, QWidget *parent = 0,FlatButtonPreset preset = FlatButtonPreset::FlatPreset);

    void checkStateSet() Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void paintBackground(QPainter *painter);
    virtual void paintHalo(QPainter *painter);
    virtual void paintForeground(QPainter *painter);

    virtual void updateClipPath();

    const QScopedPointer<XMatFlatButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatFlatButton)
    Q_DECLARE_PRIVATE(XMatFlatButton)
};


#endif // XMATFLATBUTTON_H
