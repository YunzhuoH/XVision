#include "XMatDrawer.h"
#include "XMatDrawer_p.h"
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QLinearGradient>
#include <QtWidgets/QVBoxLayout>
#include "XMatDrawer_internal.h"

/*!
 *  \class XMatDrawerPrivate
 *  \internal
 */

/*!
 *  \internal
 */
XMatDrawerPrivate::XMatDrawerPrivate(XMatDrawer *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
XMatDrawerPrivate::~XMatDrawerPrivate()
{
}

/*!
 *  \internal
 */
void XMatDrawerPrivate::init()
{
    Q_Q(XMatDrawer);

    widget       = new XMatDrawerWidget(q);
    stateMachine = new XMatDrawerStateMachine(widget, q);
    window       = new QWidget;
    width        = 250;

    clickToClose = false;
    autoRaise    = true;
    closed       = true;
    overlay      = true;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(window);
    widget->setLayout(layout);
    widget->setFixedWidth(width+16);
    widget->setParent(q);

    stateMachine->start();
    QCoreApplication::processEvents();
}

/*!
 *  \class XMatDrawer
 */

XMatDrawer::XMatDrawer(QWidget *parent,DrawerDir dir)
    : XMatOverlayWidget(parent),
      d_ptr(new XMatDrawerPrivate(this)),
      m_dir(dir)
{
    d_func()->init();
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

XMatDrawer::~XMatDrawer()
{
}


XMatDrawer::DrawerDir XMatDrawer::drawerDir() const
{
    return  m_dir;
}


void XMatDrawer::setDrawerWidth(int width)
{
    Q_D(XMatDrawer);
    d->width = width;
    d->widget->setFixedWidth(width+16);
    d->stateMachine->updatePropertyAssignments();

}

int XMatDrawer::drawerWidth() const
{
    Q_D(const XMatDrawer);

    return d->width;
}

void XMatDrawer::setDrawerLayout(QLayout *layout)
{
    Q_D(XMatDrawer);

    d->window->setLayout(layout);
}

QLayout *XMatDrawer::drawerLayout() const
{
    Q_D(const XMatDrawer);

    return d->window->layout();
}

void XMatDrawer::setClickOutsideToClose(bool state)
{
    Q_D(XMatDrawer);

    d->clickToClose = state;
}

bool XMatDrawer::clickOutsideToClose() const
{
    Q_D(const XMatDrawer);
    return d->clickToClose;
}

void XMatDrawer::setAutoRaise(bool state)
{
    Q_D(XMatDrawer);

    d->autoRaise = state;
}

bool XMatDrawer::autoRaise() const
{
    Q_D(const XMatDrawer);

    return d->autoRaise;
}

void XMatDrawer::setOverlayMode(bool value)
{
    Q_D(XMatDrawer);

    d->overlay = value;

    update();
}

bool XMatDrawer::overlayMode() const
{
    Q_D(const XMatDrawer);

    return d->overlay;
}

bool XMatDrawer::isCloseState()
{
    Q_D(XMatDrawer);
    return d->stateMachine->isInClosedState();
}

void XMatDrawer::openDrawer()
{
    Q_D(XMatDrawer);

    emit d->stateMachine->signalOpen();

    if (d->autoRaise) {
       raise();
    }
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setAttribute(Qt::WA_NoSystemBackground, false);
}

void XMatDrawer::closeDrawer()
{
    Q_D(XMatDrawer);

    emit d->stateMachine->signalClose();

    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);

}

bool XMatDrawer::event(QEvent *event)
{
     Q_D(XMatDrawer);
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        if (!d->overlay)
        {
            switch (m_dir)
            {
            case XMatDrawer::Left:
            {
                auto rect= QRect(QPoint(0,0),QSize(d->widget->rect().width()-16,d->widget->rect().height()));
                setMask(QRegion(rect));
            }
                break;
            case XMatDrawer::Right:
            {
                auto parWdg=parentWidget();
                if(parWdg)
                {
                    auto dx=parWdg->width()-d->widget->width()+16;
                    auto rect= QRect(QPoint(dx,0),d->widget->rect().size());
                    setMask(QRegion(rect));
                }
            }
                break;
            }

        }
        break;
    default:
        break;
    }
    return XMatOverlayWidget::event(event);
}

bool XMatDrawer::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(XMatDrawer);

    switch (event->type())
    {
    case QEvent::MouseButtonPress: {
        QMouseEvent *mouseEvent;
        if ((mouseEvent = static_cast<QMouseEvent *>(event))) {
            const bool canClose = d->clickToClose || d->overlay;
            QRect rect=d->widget->geometry();
             switch (m_dir)
             {
             case XMatDrawer::Left:
                 if (!rect.adjusted(0,0,-16,0).contains(mouseEvent->pos()) && canClose)
                 {
                    closeDrawer();
                 }
                 break;
             case XMatDrawer::Right:
                 if (!rect.contains(mouseEvent->pos()) && canClose)
                 {
                    closeDrawer();
                 }
                 break;
             }


        }

        break;
    }
    case QEvent::Move:
    {
        QLayout *lw = d->widget->layout();
        if (lw && 16 != lw->contentsMargins().right()) {
            lw->setContentsMargins(0, 0, 16, 0);
        }
    }
    case QEvent::Resize: {
        QLayout *lw = d->widget->layout();
        if (lw && 16 != lw->contentsMargins().right()) {
            lw->setContentsMargins(0, 0, 16, 0);
        }
        d->stateMachine->updatePropertyAssignments();
        d->widget->updateOffset();
        break;
    }
    default:
        break;
    }
    return XMatOverlayWidget::eventFilter(obj, event);
}

void XMatDrawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(XMatDrawer);

    if (!d->overlay || d->stateMachine->isInClosedState()) {
        return;
    }
    QPainter painter(this);
    painter.setOpacity(d->stateMachine->opacity());
    painter.fillRect(rect(), Qt::SolidPattern);
}
