#include "XFramelessDelegate_p.h"

#include <QApplication>
#include <QBackingStore>
#include <QDebug>
#include <QElapsedTimer>
#include <QEvent>
#include <QLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPlatformSurfaceEvent>
#include <QResizeEvent>
#include <QStyleOption>
#include <qdrawutil.h>
#include <qmath.h>

#include <assert.h>



struct XFramelessDelegate::Impl
{
    QWidget* parent { nullptr };

    enum Direction
    {
        NONE,
        UP    = 1,
        DOWN  = 2,
        LEFT  = 4,
        RIGHT = 8
    };

    Q_DECLARE_FLAGS(Directions, Direction)
    Directions direction;
    QCursor cursorShape(Directions direction)
    {
        if ((direction.testFlag(UP) && direction.testFlag(RIGHT)) || (direction.testFlag(DOWN) && direction.testFlag(LEFT)))
            return QCursor(Qt::SizeBDiagCursor);
        else if ((direction.testFlag(UP) && direction.testFlag(LEFT)) || (direction.testFlag(DOWN) && direction.testFlag(RIGHT)))
            return QCursor(Qt::SizeFDiagCursor);
        else if (direction.testFlag(UP) || direction.testFlag(DOWN))
            return QCursor(Qt::SizeVerCursor);
        else if (direction.testFlag(LEFT) || direction.testFlag(RIGHT))
            return QCursor(Qt::SizeHorCursor);
        else
            return QCursor();
    }
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QPoint mousePressPos;
#else
    QPointF mousePressPos;
#endif
    QElapsedTimer moveBarElapsedTimer;
    bool mousePressed { false };
    QWidgetList moveBars;
    bool shadowless { false };
    int margin = 8;
    int framelessMouseHandleWidth { 0 };

    struct MoveBar
    {
        bool mousePressed { false };
        QPoint mousePosRange;
    } moveBarInfo;
};



void releaseHover(QWidget* w)
{
    auto children = w->children();
    for (auto& child : children)
    {
        if (child->isWidgetType())
        {
            auto widget = qobject_cast<QWidget*>(child);
            if (widget)
            {
                if (widget->underMouse())
                {
                    QEvent* e = new QEvent(QEvent::Leave);
                    qApp->sendEvent(widget, e);
                    widget->repaint();
                }
                releaseHover(widget);
            }
        }
    }
}

XFramelessDelegate::XFramelessDelegate(QWidget* parent, const QWidgetList& moveBars)
    : QObject(parent), m_impl(std::make_unique<Impl>())
{
    m_impl->direction |= XFramelessDelegate::Impl::Direction::NONE;
    m_impl->parent = parent;
    assert(parent);
    parent->installEventFilter(this);
    parent->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    parent->setAttribute(Qt::WA_TranslucentBackground);
    parent->setAttribute(Qt::WA_Hover);

    m_impl->moveBars = moveBars;
    for (auto& w : moveBars)
    {
        if (w)
        {
            w->installEventFilter(this);
        }
    }
}

XFramelessDelegate::XFramelessDelegate(QWidget* parent, QWidget* title) : XFramelessDelegate(parent, QWidgetList() << title) {}

XFramelessDelegate::~XFramelessDelegate() {}

void XFramelessDelegate::addMoveBar(QWidget* widget)
{
    if (!widget)
        return;
    if (m_impl->moveBars.contains(widget))
        return;
    m_impl->moveBars.append(widget);
    widget->installEventFilter(this);
}

void XFramelessDelegate::removeMoveBar(QWidget* widget)
{
    if (!widget)
        return;
    m_impl->moveBars.removeOne(widget);
    widget->removeEventFilter(this);
}

void XFramelessDelegate::setShadowless(bool flag)
{
    m_impl->shadowless = flag;
    m_impl->parent->setAttribute(Qt::WA_TranslucentBackground, !flag);
    m_impl->margin                    = flag ? 0 : 8;
    m_impl->framelessMouseHandleWidth = flag ? 5 : 0;
    if (!m_impl->parent->isMaximized())
    {
        m_impl->parent->setContentsMargins(m_impl->margin, m_impl->margin, m_impl->margin, m_impl->margin);
    }
}

bool XFramelessDelegate::shadowless() const { return m_impl->shadowless; }

bool XFramelessDelegate::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == m_impl->parent)
    {
        switch (event->type())
        {
        case QEvent::HoverMove:
            mouseMoveEvent((QMouseEvent*)event);
            break;

        case QEvent::MouseButtonPress:
            mousePressEvent((QMouseEvent*)event);
            break;

        case QEvent::MouseButtonRelease:
            mouseReleaseEvent((QMouseEvent*)event);
            break;

        case QEvent::MouseButtonDblClick:
            mouseDoubleClickEvent((QMouseEvent*)event);
            break;
        case QEvent::Resize:
            resizeEvent((QResizeEvent*)event);
            break;
        case QEvent::Paint:
            paintEvent((QPaintEvent*)event);
            break;
        case QEvent::StyleChange:
            styleChangeEvent(event);
            break;
        case QEvent::WindowActivate:
        case QEvent::WindowDeactivate:
            updateLayout();
            break;
        case QEvent::PlatformSurface:
            platformSurfaceEvent((QPlatformSurfaceEvent*)event);
            break;
        default:
            break;
        }
    }

    auto moveBar = qobject_cast<QWidget*>(obj);
    if (m_impl->moveBars.contains(moveBar))
    {
        if (obj == m_impl->parent)
        {
            if (m_impl->direction != XFramelessDelegate::Impl::NONE)
                return false;
        }
        switch (event->type())
        {

        case QEvent::MouseButtonPress:
            {
                auto e = (QMouseEvent*)event;
                if (e->button() == Qt::LeftButton)
                {
                    m_impl->moveBarInfo.mousePressed  = true;
                    m_impl->moveBarInfo.mousePosRange = QCursor::pos() - m_impl->parent->pos();
                    m_impl->moveBarElapsedTimer.restart();
                    moveBar->grabMouse();
                }
                break;
            }

        case QEvent::MouseButtonRelease:
            {
                auto e = (QMouseEvent*)event;
                if (e->button() == Qt::LeftButton)
                {
                    m_impl->moveBarInfo.mousePressed = false;
                    moveBar->releaseMouse();
                }
                break;
            }

        case QEvent::MouseButtonDblClick:
            {
                if (m_impl->parent->maximumSize() == m_impl->parent->minimumSize())
                    break;
                if (m_impl->parent->windowState().testFlag(Qt::WindowMaximized) ||
                    m_impl->parent->windowState().testFlag(Qt::WindowFullScreen))
                    m_impl->parent->showNormal();
                else
                    m_impl->parent->showMaximized();
                break;
            }

        case QEvent::MouseMove:
            {
                if (m_impl->moveBarInfo.mousePressed && m_impl->direction == XFramelessDelegate::Impl::NONE)
                {
                    if (m_impl->moveBarElapsedTimer.elapsed() < 50)
                        return false;
                    if (m_impl->parent->windowState().testFlag(Qt::WindowMaximized) ||
                        m_impl->parent->windowState().testFlag(Qt::WindowFullScreen))
                    {
                        if (QCursor::pos().y() < 5)
                            return false;
                        m_impl->parent->showNormal();
                        m_impl->moveBarInfo.mousePosRange = QPoint(moveBar->width() / 2, moveBar->height() / 2);
                    }
                    else
                    {
                        m_impl->parent->move(QCursor::pos() - m_impl->moveBarInfo.mousePosRange);
                        if (QCursor::pos().y() < 5)
                        {
                            if (m_impl->parent->maximumSize() == m_impl->parent->minimumSize())
                                break;
                            this->metaObject()->invokeMethod(m_impl->parent, "showMaximized", Qt::QueuedConnection);
                        }
                    }
                }
                break;
            }
        case QEvent::Resize:
            {
                QResizeEvent* evt = dynamic_cast<QResizeEvent*>(event);
                if (evt)
                {
                    m_impl->moveBarInfo.mousePosRange = QPoint(evt->size().width() / 2, evt->size().height() / 2);
                }
                break;
            }
        default:
            break;
        }
    }
    return false;
}

void XFramelessDelegate::resizeEvent([[maybe_unused]] QResizeEvent* e)
{
    if (m_impl->parent->windowState().testFlag(Qt::WindowMaximized) || m_impl->parent->windowState().testFlag(Qt::WindowFullScreen))
        m_impl->parent->setContentsMargins(QMargins(0, 0, 0, 0));
    else
    {
        m_impl->parent->setContentsMargins(QMargins(m_impl->margin, m_impl->margin, m_impl->margin, m_impl->margin));
    }
    updateLayout();
}

void XFramelessDelegate::mousePressEvent(QMouseEvent* e)
{
    if (m_impl->direction != XFramelessDelegate::Impl::NONE && e->button() == Qt::LeftButton)
    {
        m_impl->mousePressed = true;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        m_impl->mousePressPos = e->globalPos();
#else
        m_impl->mousePressPos = e->globalPosition();
#endif
    }
}

void XFramelessDelegate::mouseMoveEvent(QMouseEvent*)
{
    if (!m_impl->mousePressed)
    {
        if (!(m_impl->parent->windowState().testFlag(Qt::WindowMaximized) || m_impl->parent->windowState().testFlag(Qt::WindowFullScreen)))
        {
            auto old = m_impl->direction;
            region(QCursor::pos());
            if (old != m_impl->direction)
            {
                if (m_impl->direction !=XFramelessDelegate::Impl::NONE)
                {
                    if (shadowless())
                        m_impl->parent->grabMouse();
                }
                else
                {
                    if (shadowless())
                    {
                        m_impl->parent->releaseMouse();
                        releaseHover(m_impl->parent);
                    }
                }
            }
        }
    }
    else
    {
        const auto& gloPoint = QCursor::pos();
        const auto& rect     = m_impl->parent->rect();
        const auto& tl       = m_impl->parent->mapToGlobal(rect.topLeft());
        const auto& rb       = m_impl->parent->mapToGlobal(rect.bottomRight());
        if (m_impl->direction != XFramelessDelegate::Impl::NONE)
        {
            QRect rMove(tl, rb);
            auto minSize     = m_impl->parent->minimumSizeHint().expandedTo(m_impl->parent->minimumSize());
            auto maxSize     = m_impl->parent->maximumSize();
            auto smartResize = [&](XFramelessDelegate::Impl::Direction direction)
            {
                switch (direction)
                {
                case XFramelessDelegate::Impl::LEFT:
                    rMove.setX(std::max(tl.x() - (maxSize.width() - rect.width()),
                                        std::min(rb.x() - minSize.width(), gloPoint.x() - m_impl->margin)));
                    break;
                case XFramelessDelegate::Impl::RIGHT:
                    rMove.setWidth(std::min(maxSize.width(), std::max(gloPoint.x() - tl.x() + m_impl->margin, minSize.width())));
                    break;
                case XFramelessDelegate::Impl::UP:
                    rMove.setY(std::max(tl.y() - (maxSize.height() - rect.height()),
                                        std::min(rb.y() - minSize.height(), gloPoint.y() - m_impl->margin)));
                    break;
                case XFramelessDelegate::Impl::DOWN:
                    rMove.setHeight(std::min(maxSize.height(), std::max(gloPoint.y() - tl.y() + m_impl->margin, minSize.height())));
                    break;
                default:
                    break;
                }
                m_impl->parent->setGeometry(rMove);
            };

            if (m_impl->direction.testFlag(XFramelessDelegate::Impl::LEFT))
                smartResize(XFramelessDelegate::Impl::LEFT);
            else if (m_impl->direction.testFlag(XFramelessDelegate::Impl::RIGHT))
                smartResize(XFramelessDelegate::Impl::RIGHT);

            if (m_impl->direction.testFlag(XFramelessDelegate::Impl::UP))
                smartResize(XFramelessDelegate::Impl::UP);
            else if (m_impl->direction.testFlag(XFramelessDelegate::Impl::DOWN))
                smartResize(XFramelessDelegate::Impl::DOWN);
        }
    }
}

void XFramelessDelegate::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_impl->mousePressed = false;
        if (m_impl->direction !=XFramelessDelegate::Impl::NONE)
        {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            region(e->globalPos());
#else
            region(e->globalPosition().toPoint());
#endif
            if (m_impl->direction == XFramelessDelegate::Impl::NONE)
            {
                if (m_impl->shadowless)
                {
                    m_impl->parent->releaseMouse();
                    releaseHover(m_impl->parent);
                }
            }
        }
    }
}

void XFramelessDelegate::mouseDoubleClickEvent([[maybe_unused]] QMouseEvent* e) {}

void XFramelessDelegate::paintEvent([[maybe_unused]] QPaintEvent* e)
{
    QImage image(m_impl->parent->width(), m_impl->parent->height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::NoBrush);
    QPainter p;
    p.begin(&image);
    QStyleOption opt;
    opt.initFrom(m_impl->parent);

    if (m_impl->parent->windowState().testFlag(Qt::WindowMaximized) || m_impl->parent->windowState().testFlag(Qt::WindowFullScreen))
        paintShadow(p, 0);
    else
    {
        int lm = 0;
        if (m_impl->parent->layout())
        {
            int left, top, right, bottom;
            m_impl->parent->layout()->getContentsMargins(&left, &top, &right, &bottom);
            lm = std::max(std::max(left, top), std::max(right, bottom));
        }
        paintShadow(p, m_impl->margin + lm);
        opt.rect = QRect(
            m_impl->margin, m_impl->margin, m_impl->parent->width() - 2 * m_impl->margin, m_impl->parent->height() - 2 * m_impl->margin);
    }
    p.end();
    p.begin(&image);
    m_impl->parent->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, m_impl->parent);
    p.end();
    QPainter painter(m_impl->parent);
    int left = 0, top = 0, right = 0, bottom = 0;
    if (m_impl->parent->layout())
        m_impl->parent->layout()->getContentsMargins(&left, &top, &right, &bottom);
    painter.fillRect(QRect(m_impl->margin + left,
                           m_impl->margin + top,
                           m_impl->parent->width() - m_impl->margin * 2 - left - right,
                           m_impl->parent->height() - m_impl->margin * 2 - top - bottom),
                     opt.palette.window());
    painter.drawImage(0, 0, image);
}

void XFramelessDelegate::paintShadow(QPainter& painter, int shadowWidth)
{
    if (m_impl->shadowless)
        return;
    if (!shadowWidth)
        return;
    auto w = m_impl->parent;
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor color(0, 0, 0, 20);
    for (int i = 0; i < shadowWidth; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(
            shadowWidth - i, shadowWidth - i, w->width() - (shadowWidth - i) * 2, w->height() - (shadowWidth - i) * 2, 0, Qt::RelativeSize);
        auto v = log((i + 1) / (float)shadowWidth) / log(0.5);
        color.setAlpha(v * 20);
        painter.setPen(color);
        painter.drawPath(path);
    }
    painter.restore();
}

void XFramelessDelegate::styleChangeEvent([[maybe_unused]] QEvent* e) { updateLayout(); }

void XFramelessDelegate::platformSurfaceEvent(QPlatformSurfaceEvent* e)
{
    if (e->surfaceEventType() == QPlatformSurfaceEvent::SurfaceCreated)
    {
        if (m_impl->parent->maximumHeight() != QWIDGETSIZE_MAX || m_impl->parent->maximumWidth() != QWIDGETSIZE_MAX)
        {
            m_impl->parent->setWindowFlags(m_impl->parent->windowFlags() & ~Qt::WindowMaximizeButtonHint);
        }
    }
}

void XFramelessDelegate::region(const QPoint& cursorGlobalPoint)
{
    const auto& rect = m_impl->parent->rect();
    const auto& tl   = m_impl->parent->mapToGlobal(rect.topLeft());
    const auto& rb   = m_impl->parent->mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    m_impl->direction = XFramelessDelegate::Impl::NONE;

    if (x <= tl.x() + m_impl->margin + m_impl->framelessMouseHandleWidth && x >= tl.x())
    {
        if (m_impl->parent->minimumWidth() != m_impl->parent->maximumWidth())
            m_impl->direction |= XFramelessDelegate::Impl::LEFT;
    }
    if (x <= rb.x() && x >= rb.x() - m_impl->margin - m_impl->framelessMouseHandleWidth)
    {
        if (m_impl->parent->minimumWidth() != m_impl->parent->maximumWidth())
            m_impl->direction |= XFramelessDelegate::Impl::RIGHT;
    }
    if (y >= tl.y() && y <= tl.y() + m_impl->margin + m_impl->framelessMouseHandleWidth)
    {
        if (m_impl->parent->minimumHeight() != m_impl->parent->maximumHeight())
            m_impl->direction |= XFramelessDelegate::Impl::UP;
    }
    if (y <= rb.y() && y >= rb.y() - m_impl->margin - m_impl->framelessMouseHandleWidth)
    {
        if (m_impl->parent->minimumHeight() != m_impl->parent->maximumHeight())
            m_impl->direction |= XFramelessDelegate::Impl::DOWN;
    }
    m_impl->parent->setCursor(m_impl->cursorShape(m_impl->direction));
}

void XFramelessDelegate::updateLayout()
{
    if (m_impl->parent->layout())
    {
        QStyleOption opt;
        opt.initFrom(m_impl->parent);

        auto rect = m_impl->parent->style()->subElementRect(QStyle::SE_FrameContents, &opt, m_impl->parent);
        if (!rect.isValid())
            return;
        int left, top, right = 0, bottom = 0;
        left   = rect.x();
        top    = rect.y();
        right  = m_impl->parent->width() - left - rect.width();
        bottom = m_impl->parent->height() - top - rect.height();
        if (!m_impl->parent->isMaximized())
            m_impl->parent->layout()->setContentsMargins(left, top, right, bottom);
        else
            m_impl->parent->layout()->setContentsMargins(0, 0, 0, 0);
    }
}
