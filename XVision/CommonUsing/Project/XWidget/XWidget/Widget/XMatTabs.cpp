#include "XMatTabs.h"
#include "XMatTabs_p.h"
#include <QtWidgets/QHBoxLayout>
#include <QPainter>
#include "XMatTabs_internal.h"
#include "XMatStyleDef.h"

/*!
 *  \XMatTabsPrivate
 *  \internal
 */

XMatTabsPrivate::XMatTabsPrivate(XMatTabs *q)
    : q_ptr(q)
{
    inkColor=QColor(Qt::white);
    backgroundColor=C_XMatThemeColor;
    textColor=C_XMatFontdColor;
}

XMatTabsPrivate::~XMatTabsPrivate()
{
}

void XMatTabsPrivate::XMatTabsPrivate::init()
{
    Q_Q(XMatTabs);

    inkBar         = new XMatTabsInkBar(q);
    tabLayout      = new QHBoxLayout;
    rippleStyle    = XMatCommonDef::RippleStyle::CenteredRipple;
    tab            = -1;
    showHalo       = true;


    q->setLayout(tabLayout);


    tabLayout->setSpacing(0);
    tabLayout->setContentsMargins(0,0,0,0);
}

/*!
 *  \XMatTabs
 */

XMatTabs::XMatTabs(QWidget *parent)
    : QWidget(parent),
      d_ptr(new XMatTabsPrivate(this))
{
    d_func()->init();
}

XMatTabs::~XMatTabs()
{
}


void XMatTabs::setHaloVisible(bool value)
{
    Q_D(XMatTabs);

    d->showHalo = value;
    updateTabs();
}

bool XMatTabs::isHaloVisible() const
{
    Q_D(const XMatTabs);

    return d->showHalo;
}

void XMatTabs::setRippleStyle(XMatCommonDef::RippleStyle style)
{
    Q_D(XMatTabs);

    d->rippleStyle = style;
    updateTabs();
}

XMatCommonDef::RippleStyle XMatTabs::rippleStyle() const
{
    Q_D(const XMatTabs);

    return d->rippleStyle;
}

void XMatTabs::setInkColor(const QColor &color)
{
    Q_D(XMatTabs);

    d->inkColor = color;


    d->inkBar->update();
    update();
}

QColor XMatTabs::inkColor() const
{
    Q_D(const XMatTabs);

   return d->inkColor;
}

void XMatTabs::setBackgroundColor(const QColor &color)
{
    Q_D(XMatTabs);

    d->backgroundColor = color;


    updateTabs();
    update();
}

QColor XMatTabs::backgroundColor() const
{
    Q_D(const XMatTabs);

    return d->backgroundColor;
}

void XMatTabs::setTextColor(const QColor &color)
{
    Q_D(XMatTabs);

    d->textColor = color;


    updateTabs();
    update();
}

QColor XMatTabs::textColor() const
{
    Q_D(const XMatTabs);

    return d->textColor;
}

void XMatTabs::setCurrentTab(XMatTab *tab)
{
    Q_D(XMatTabs);

    setCurrentTab(d->tabLayout->indexOf(tab));
}

void XMatTabs::setCurrentTab(int index)
{
    Q_D(XMatTabs);

    setTabActive(d->tab, false);
    d->tab = index;
    setTabActive(index, true);
    d->inkBar->animate();

    emit currentChanged(index);
}

XMatTab* XMatTabs::addTab(const QString &text, const QIcon &icon)
{
    Q_D(XMatTabs);

    XMatTab *tab = new XMatTab(this);
    tab->setText(text);
    tab->setHaloVisible(isHaloVisible());
    tab->setRippleStyle(rippleStyle());

    if (!icon.isNull()) {
        tab->setIcon(icon);
        tab->setIconSize(QSize(22, 22));
    }

    d->tabLayout->addWidget(tab);

    if (-1 == d->tab) {
        d->tab = 0;
        d->inkBar->refreshGeometry();
        d->inkBar->raise();
        tab->setActive(true);
    }
    return tab;
}

int XMatTabs::currentIndex() const
{
    Q_D(const XMatTabs);

    return d->tab;
}

void XMatTabs::setTabsMinimumHeight(int minh)
{
    Q_D(XMatTabs);
    this->setMinimumHeight(minh);
    XMatTab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<XMatTab *>(item->widget())))
        {
            tab->setMinimumHeight(minh);
        }
    }

}

void XMatTabs::setTabsMaximumHeight(int maxh)
{
    Q_D(XMatTabs);
    this->setMaximumHeight(maxh);
    XMatTab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<XMatTab *>(item->widget())))
        {
            tab->setMaximumHeight(maxh);
        }
    }
}

void XMatTabs::setTabActive(int index, bool active)
{
    Q_D(XMatTabs);

    XMatTab *tab;

    if (index > -1) {
        tab = static_cast<XMatTab *>(d->tabLayout->itemAt(index)->widget());
        if (tab) {
            tab->setActive(active);
        }
    }
}

void XMatTabs::updateTabs()
{
    Q_D(XMatTabs);

    XMatTab *tab;
    for (int i = 0; i < d->tabLayout->count(); ++i) {
        QLayoutItem *item = d->tabLayout->itemAt(i);
        if ((tab = static_cast<XMatTab *>(item->widget()))) {
            tab->setRippleStyle(d->rippleStyle);
            tab->setHaloVisible(d->showHalo);
            tab->setBackgroundColor(backgroundColor());
            tab->setForegroundColor(textColor());
        }
    }
}

/*!
 *  \class XMatTab
 */

XMatTab::XMatTab(XMatTabs *parent)
    : XMatFlatButton(parent),
      m_tabs(parent),
      m_active(false)
{
    Q_ASSERT(parent);

    if(parent)
    {
        setMinimumHeight(parent->minimumHeight());
        setMaximumHeight(parent->maximumHeight());
    }

    QFont f(font());
    f.setStyleName("Normal");
    setFont(f);

    setCornerRadius(0);
    setBackgroundMode(Qt::OpaqueMode);
    setBaseOpacity(0.25);

    connect(this, SIGNAL(clicked(bool)), this, SLOT(activateTab()));
}

XMatTab::~XMatTab()
{
}

QSize XMatTab::sizeHint() const
{
    return XMatFlatButton::sizeHint();

    /*SRC:
    if (icon().isNull()) {
        return XMatFlatButton::sizeHint();
    } else {
        return QSize(40, iconSize().height()+46);
    }
    */
}

void XMatTab::activateTab()
{
    m_tabs->setCurrentTab(this);
}

void XMatTab::paintForeground(QPainter *painter)
{
    painter->setPen(foregroundColor());

    /*SRC:
    if (!icon().isNull()) {
        painter->translate(0, 12);
    }
    */

    QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
    QSize base(size()-textSize);

    QRect textGeometry(QPoint(base.width(), base.height())/2, textSize);

    painter->drawText(textGeometry, Qt::AlignCenter, text());

    if (!icon().isNull())
    {
        const QSize &size = iconSize();
        QRect iconRect;
        if(text().isEmpty())
        {
            iconRect=QRect(QPoint((width()-size.width())/2, (height()-size.height())/2), size);
        }
        else
        {
            iconRect=QRect(QPoint(textGeometry.left()-size.width()-5,  (height()-size.height())/2), size);
        }

        QPixmap pixmap = icon().pixmap(iconSize());
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), painter->pen().color());
        painter->drawPixmap(iconRect, pixmap);
    }

    if (!m_active)
    {
        /*SRC:
        if (!icon().isNull()) {
           painter->translate(0, -12);
        }
        */
        QBrush overlay;
        overlay.setStyle(Qt::SolidPattern);
        overlay.setColor(backgroundColor());
        painter->setOpacity(0.36);
        painter->fillRect(rect(), overlay);
    }
}
