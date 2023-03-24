#ifndef XMATCOMBOBOX_H
#define XMATCOMBOBOX_H

#include "XWidgetGlobal.h"
#include "XMatCommonDef.h"
#include <QComboBox>
#include <QScopedPointer>


class XMatComboBoxPrivate;

class XWIDGET_EXPORT XMatComboBox : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(QColor normalColor WRITE setNormalColor READ normalColor)
    Q_PROPERTY(QColor showPopupColor WRITE setShowPopupColor READ showPopupColor)

    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)

    Q_PROPERTY(QColor disabledForegroundColor WRITE setDisabledForegroundColor READ disabledForegroundColor)
    Q_PROPERTY(QColor disabledBackgroundColor WRITE setDisabledBackgroundColor READ disabledBackgroundColor)

    Q_PROPERTY(XMatCommonDef::RippleStyle rippleStyle WRITE setRippleStyle READ rippleStyle)


public:

    explicit XMatComboBox(QWidget *parent = 0);
    ~XMatComboBox();

    void setNormalColor(const QColor &color);
    QColor normalColor() const;

    void setShowPopupColor(const QColor &color);
    QColor showPopupColor() const;


    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setBorderColor(const QColor &color);
    QColor borderColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setDisabledForegroundColor(const QColor &color);
    QColor disabledForegroundColor() const;

    void setDisabledBackgroundColor(const QColor &color);
    QColor disabledBackgroundColor() const;

    void setRippleStyle(XMatCommonDef::RippleStyle style);
    XMatCommonDef::RippleStyle rippleStyle() const;

public:
    void showPopup() override;
    void hidePopup() override;
 Q_SIGNALS:
    void cmbShowPopup();
    void cmbHidePopup();
protected:

    XMatComboBox(XMatComboBoxPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void setupProperties();

    const QScopedPointer<XMatComboBoxPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatComboBox)
    Q_DECLARE_PRIVATE(XMatComboBox)


};

#endif // XMATCOMBOBOX_H
