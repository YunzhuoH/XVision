#ifndef XMATSUSPENDWIDGET_INTERNAL_H
#define XMATSUSPENDWIDGET_INTERNAL_H

#include <QWidget>

class QStackedLayout;
class XMatSuspendWidget;
class XMatSuspendWidgetWindow;

class XMatSuspendWidgetProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

    enum TransparencyMode {
        Transparent,
        SemiTransparent,
        Opaque,
    };

public:
    XMatSuspendWidgetProxy(XMatSuspendWidgetWindow *source,
                          QStackedLayout *layout,
                          XMatSuspendWidget *widget,
                          QWidget *parent = 0);
    ~XMatSuspendWidgetProxy();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected slots:
    void makeOpaque();
    void makeTransparent();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatSuspendWidgetProxy)

    XMatSuspendWidgetWindow *const m_source;
    QStackedLayout         *const m_layout;
    XMatSuspendWidget       *const m_widget;
    qreal                         m_opacity;
    TransparencyMode              m_mode;
};

inline qreal XMatSuspendWidgetProxy::opacity() const
{
    return m_opacity;
}

class XMatSuspendWidgetWindow : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit XMatSuspendWidgetWindow(XMatSuspendWidget *widget, QWidget *parent = 0);
    ~XMatSuspendWidgetWindow();

    void setOffset(int offset);
    int offset() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(XMatSuspendWidgetWindow)

    XMatSuspendWidget *const m_widget;
};

#endif // XMATSUSPENDWIDGET_INTERNAL_H
