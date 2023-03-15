#ifndef XMATDRAWER_INTERNAL_H
#define XMATDRAWER_INTERNAL_H

#include <QStateMachine>
#include "XMatOverlayWidget.h"

class XMatDrawer;
class XMatDrawerWidget;

class XMatDrawerStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit XMatDrawerStateMachine(XMatDrawerWidget *drawer,
                                          XMatDrawer *parent);
    ~XMatDrawerStateMachine();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

    bool isInClosedState() const;

    void updatePropertyAssignments();

signals:
    void signalOpen();
    void signalClose();

private:
    Q_DISABLE_COPY(XMatDrawerStateMachine)

    XMatDrawerWidget *const m_drawer;
    XMatDrawer       *const m_main;
    QState                 *const m_openingState;
    QState                 *const m_openedState;
    QState                 *const m_closingState;
    QState                 *const m_closedState;
    qreal                         m_opacity;
};

inline qreal XMatDrawerStateMachine::opacity() const
{
    return m_opacity;
}


class XMatDrawerWidget : public XMatOverlayWidget
{
    Q_OBJECT
    Q_PROPERTY(QPoint offset WRITE setOffset READ offset)

public:
    explicit XMatDrawerWidget(XMatDrawer *drawer,QWidget *parent = 0);
    ~XMatDrawerWidget();

    void setOffset(QPoint offset);
    inline QPoint offset() const;

    QPoint closedOffset();
    QPoint openingOffset();

    void updateOffset();
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    QRect overlayGeometry() const Q_DECL_OVERRIDE;

private:
    QPoint  m_offset;
    XMatDrawer* m_drawer=nullptr;



};

inline QPoint XMatDrawerWidget::offset() const
{
    return m_offset;
}

#endif // XMATDRAWER_INTERNAL_H
