
#include "XSeparator_p.h"
#include "XToolButton_p.h"
#include "XWidgetItem_p.h"

#include <QWidgetAction>

inline void setToolButtonProperty(QAction* action, XToolButton* btn)
{
    auto setToolButtonStyle = [](QAction* action, XToolButton* btn)
    {
        if (action->icon().isNull())
            btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
        else if (action->text().isEmpty())
            btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        else
            btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    };
    btn->setDefaultAction(action);
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    btn->setObjectName(action->objectName());
    if (btn->parent())
        btn->setVisible(action->isVisible());
    setToolButtonStyle(action, btn);
    QObject::connect(action,
                     &QAction::changed,
                     btn,
                     [=]()
                     {
                         setToolButtonStyle(action, btn);
                         if (btn->parent())
                             btn->setVisible(action->isVisible());
                     });
    QObject::connect(action, &QObject::objectNameChanged, btn, [=](const QString& name) { btn->setObjectName(name); });
};

inline void setWidgetProperty(QAction* action, QWidget* widget)
{
    QObject::connect(action,
                     &QAction::changed,
                     widget,
                     [=]()
                     {
                         if (widget->parent())
                             widget->setVisible(action->isVisible());
                     });
    QObject::connect(action, &QObject::objectNameChanged, widget, [=](const QString& name) { widget->setObjectName(name); });
}

struct XWidgetItem::Impl
{
    QAction* action { nullptr };
    QWidget* widget { nullptr };
    bool customWidget { false };
};

XWidgetItem::XWidgetItem(QAction* action, Qt::Orientation orientation, const QSize& iconSize, QWidget* parent)
    : QObject(parent), m_impl(std::make_unique<Impl>())
{
    m_impl->action = action;

    auto wa = qobject_cast<QWidgetAction*>(action);
    if (wa && wa->defaultWidget())
    {
        m_impl->customWidget = true;
        m_impl->widget       = wa->defaultWidget();
        if (auto btn = qobject_cast<XToolButton*>(m_impl->widget); btn)
        {
            setToolButtonProperty(action, btn);
            btn->setIconSize(iconSize);
            connect(this, &XWidgetItem::iconSizeChanged, btn, &XToolButton::setIconSize);
        }
        else
            setWidgetProperty(action, m_impl->widget);
    }
    else
    {
        if (action->isSeparator())
        {
            m_impl->widget = new XSeparator(orientation, parent);
            m_impl->widget->setObjectName(action->objectName());
            QObject::connect(
                action, &QObject::objectNameChanged, m_impl->widget, [=](const QString& name) { m_impl->widget->setObjectName(name); });
        }
        else
        {
            auto btn = new XToolButton(parent);
            setToolButtonProperty(action, btn);
            m_impl->widget = btn;
            btn->setIconSize(iconSize);
            connect(this, &XWidgetItem::iconSizeChanged, btn, &XToolButton::setIconSize);
        }
    }
}

XWidgetItem::~XWidgetItem()
{
    if (!m_impl->customWidget && m_impl->widget)
        delete m_impl->widget;
}

void XWidgetItem::release()
{
    m_impl->action = nullptr;
    m_impl->widget = nullptr;
}

QAction* XWidgetItem::action() const { return m_impl->action; }

QWidget* XWidgetItem::widget() const { return m_impl->widget; }

bool XWidgetItem::isCustomWidget() const { return m_impl->customWidget; }
