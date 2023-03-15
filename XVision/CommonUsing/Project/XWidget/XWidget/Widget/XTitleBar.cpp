
#include "XTitleBar.h"
#include "XWidgetItem_p.h"
#include "XUtil_p.h"


#include <QMenuBar>
#include <QPainter>
#include <QPointer>
#include <QResizeEvent>
#include <QStyleOption>
#include <QHBoxLayout>
#include <QToolButton>
#include <QCoreApplication>
#include "XMaximumSizeButton_p.h"

Q_CONSTEXPR int leftMargin   = 5;
Q_CONSTEXPR int titleSpacing = 5;

///UI界面代码
class XTitleBarUi
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *actionLayout;
    QHBoxLayout *rightLayout;
    XMaximumSizeButton *minimumSizeBtn;
    XMaximumSizeButton *maximumSizeBtn;
    QToolButton *closeBtn;

    void setupUi(QWidget *XTitleBar)
    {
        if (XTitleBar->objectName().isEmpty())
            XTitleBar->setObjectName("XTitleBar");
        XTitleBar->resize(580, 28);
        XTitleBar->setMinimumSize(QSize(0, 28));
        XTitleBar->setMaximumSize(QSize(16777215, 50));
        XTitleBar->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(XTitleBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        actionLayout = new QHBoxLayout();
        actionLayout->setSpacing(2);
        actionLayout->setObjectName("actionLayout");
        actionLayout->setContentsMargins(5, -1, -1, -1);
        horizontalLayout->addLayout(actionLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);


        rightLayout=new QHBoxLayout();
        rightLayout->setSpacing(2);
        rightLayout->setObjectName("rightLayout");
        rightLayout->setContentsMargins(-1, -1, 5, -1);
        horizontalLayout->addLayout(rightLayout);

        minimumSizeBtn = new XMaximumSizeButton(XTitleBar);
        minimumSizeBtn->setObjectName("minimumSizeBtn");
        minimumSizeBtn->setMinimumSize(QSize(30, 29));
        minimumSizeBtn->setMaximumSize(QSize(30, 29));
        minimumSizeBtn->setFocusPolicy(Qt::NoFocus);
        minimumSizeBtn->setIconSize(QSize(10, 10));

        horizontalLayout->addWidget(minimumSizeBtn);

        maximumSizeBtn = new XMaximumSizeButton(XTitleBar);
        maximumSizeBtn->setObjectName("maximumSizeBtn");
        maximumSizeBtn->setMinimumSize(QSize(30, 30));
        maximumSizeBtn->setMaximumSize(QSize(30, 30));
        maximumSizeBtn->setFocusPolicy(Qt::NoFocus);
        maximumSizeBtn->setIconSize(QSize(10, 10));

        horizontalLayout->addWidget(maximumSizeBtn);

        closeBtn = new QToolButton(XTitleBar);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setMinimumSize(QSize(30, 30));
        closeBtn->setMaximumSize(QSize(30, 30));
        closeBtn->setFocusPolicy(Qt::NoFocus);
        closeBtn->setIconSize(QSize(10, 10));
        horizontalLayout->addWidget(closeBtn);

        horizontalLayout->setStretch(1, 1);

        retranslateUi(XTitleBar);

        QMetaObject::connectSlotsByName(XTitleBar);
    } // setupUi

    void retranslateUi(QWidget *XTitleBar)
    {
        XTitleBar->setWindowTitle(QCoreApplication::translate("XTitleBar", "QFramelessTitleWidget", nullptr));
        minimumSizeBtn->setText(QString());
        maximumSizeBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};


struct XTitleBar::Impl
{
    QPixmap windowIcon;
    QPointer<QMenuBar> menuBar;
    bool showIcon { true };
    QList<XWidgetItemPtr> items;
    QSize iconSize { 16, 16 };
};

/*!
    \class      XTitleBar
    \brief      XFramelessWidget 和 XFramelessDialog 的自定义标题栏.
    \note       最大化，最小化，关闭按钮等显示控制由 QWidget::windowFlags 决定，图标显示由 QWidget::windowIcon
                控制，标题栏文字由centralWidget的QWidget::windowTitle决定.
    \inherits   QWidget
    \ingroup    XWidget
    \inmodule   XWidget
    \inheaderfile XTitleBar.h

    \b          {截图:}
    \image      XTitleBarDetail.png
*/

/*!
    \property   XTitleBar::iconIsVisible
    \brief      是否显示图标.
*/

/*!
    \brief      构造函数 \a parent.
*/
XTitleBar::XTitleBar(QWidget* parent) : QWidget(parent), ui(new XTitleBarUi), m_impl(std::make_unique<Impl>())
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    ui->closeBtn->setIconSize(QSize(16,16));
    ui->closeBtn->setIcon(QIcon(":/images/Close.svg"));

    ui->minimumSizeBtn->setIconSize(QSize(14,14));
    ui->minimumSizeBtn->setIcon(QIcon(":/images/Minimize.svg"));

    ui->maximumSizeBtn->setIconSize(QSize(14,14));
    ui->maximumSizeBtn->setIcon(QIcon(":/images/Maximize.svg"));
    ui->maximumSizeBtn->setIcon(QIcon(":/images/MaximizeMax.svg"));

    connect(ui->closeBtn, &QPushButton::clicked, this, &XTitleBar::onCloseBtn);
    connect(ui->minimumSizeBtn, &QPushButton::clicked, this, &XTitleBar::onMinimumSizeBtn);
    connect(ui->maximumSizeBtn, &QPushButton::clicked, this, &XTitleBar::onMaximumSizeBtn);
    ui->maximumSizeBtn->setProperty("xwidget_maximumSizeButton", true);

    parent->installEventFilter(this);
    setAttribute(Qt::WA_StyledBackground);
}

/*!
    \brief      析构函数.
*/
XTitleBar::~XTitleBar() { delete ui; }

/*!
    \brief      设置菜单栏 \a menu, 当 \a menu 为nullptr时删除菜单栏.
    \sa         menuBar
*/
void XTitleBar::setMenuBar(QMenuBar* menu)
{
    if (menu == m_impl->menuBar)
        return;
    if (m_impl->menuBar)
    {
        m_impl->menuBar->hide();
        m_impl->menuBar->setParent(nullptr);
        m_impl->menuBar->deleteLater();
    }
    if (menu)
    {
        menu->setAutoFillBackground(false);
        menu->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
        ui->horizontalLayout->insertWidget(0, menu);
    }
    m_impl->menuBar = menu;
    update();
}

/*!
    \brief      返回菜单栏, 当菜单栏对象不存在时，自动创建并返回一个新的菜单栏.
    \sa         setMenuBar
*/
QMenuBar* XTitleBar::menuBar() const
{
    auto menuBar = m_impl->menuBar;
    if (!menuBar)
    {
        auto self = const_cast<XTitleBar*>(this);
        menuBar   = new QMenuBar(self);
        self->setMenuBar(menuBar);
    }
    return menuBar;
}

QHBoxLayout *XTitleBar::rightLayout() const
{
    return ui->rightLayout;
}



/*!
    \brief      设置是否显示图标 \a show.
    \sa         iconIsVisible()
*/
void XTitleBar::setIconVisible(bool show)
{
    m_impl->showIcon = show;
    if (show)
        ui->horizontalLayout->setContentsMargins(leftMargin + titleSpacing + m_impl->windowIcon.width(), 0, 0, 0);
    else
        ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
}

/*!
    \brief      返回是否显示图标.
    \sa         setIconVisible
*/
bool XTitleBar::iconIsVisible() const { return m_impl->showIcon; }

/*!
    \brief      设置Action图标大小 \a size.
    \sa         iconSize
*/
void XTitleBar::setIconSize(const QSize& size) { m_impl->iconSize = size; }

/*!
    \brief      返回Action图标大小.
    \sa         setIconSize
*/
const QSize& XTitleBar::iconSize() const { return m_impl->iconSize; }

void XTitleBar::setMinBtnSize(int minw, int minh)
{
    ui->minimumSizeBtn->setMinimumSize(minw,minh);
    ui->maximumSizeBtn->setMinimumSize(minw,minh);
    ui->closeBtn->setMinimumSize(minw,minh);
}

void XTitleBar::setMaxBtnSize(int maxw, int maxh)
{
    ui->minimumSizeBtn->setMaximumSize(maxw,maxh);
    ui->maximumSizeBtn->setMaximumSize(maxw,maxh);
    ui->closeBtn->setMaximumSize(maxw,maxh);
}


/*!
    \brief      响应关闭按钮.
    \sa         onMaximumSizeBtn(), onMinimumSizeBtn()
*/
void XTitleBar::onCloseBtn() { this->window()->close(); }

/*!
    \brief      响应最大化按钮.
    \sa         onCloseBtn(), onMinimumSizeBtn()
*/
void XTitleBar::onMaximumSizeBtn()
{
    if (this->window()->isMaximized() || this->window()->isFullScreen())
        this->window()->showNormal();
    else
        this->window()->showMaximized();
}

/*!
    \brief      响应最小化按钮.
    \sa         onCloseBtn(), onMaximumSizeBtn()
*/
void XTitleBar::onMinimumSizeBtn() { this->window()->showMinimized(); }
/*!
    \reimp
*/
void XTitleBar::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    const auto& iconRect = doIconRect();
    if (!m_impl->windowIcon.isNull() && m_impl->showIcon)
    {
        p.drawPixmap(iconRect, m_impl->windowIcon);
    }

    if (parentWidget())
    {
        auto text = parentWidget()->windowTitle();
        QRect rect(QPoint { 0, 0 }, opt.fontMetrics.size(Qt::TextSingleLine, text));
        if (m_impl->menuBar||ui->actionLayout->count()>0) //居中显示
        {
            rect.moveTo((width() - rect.width()) / 2, 0);
        }
        else    //左侧显示
        {
           rect.moveTo(leftMargin + iconRect.width() + titleSpacing, 0);
        }
        rect.setHeight(this->height());
        QTextOption to;
        to.setWrapMode(QTextOption::NoWrap);
        to.setAlignment(Qt::AlignCenter);
        p.setFont(this->font());
        p.setPen(this->palette().windowText().color());
        p.drawText(rect, text, to);


    }
}

/*!
    \reimp
*/
void XTitleBar::showEvent([[maybe_unused]] QShowEvent* event)
{
    auto w = qobject_cast<QWidget*>(this->parent());
    if (w)
    {
        if (!w->windowFlags().testFlag(Qt::WindowType::WindowCloseButtonHint))
            ui->closeBtn->hide();
        if (!w->windowFlags().testFlag(Qt::WindowType::WindowMinimizeButtonHint))
            ui->minimumSizeBtn->hide();
        if (!w->windowFlags().testFlag(Qt::WindowType::WindowMaximizeButtonHint))
            ui->maximumSizeBtn->hide();
        if (w->windowState().testFlag(Qt::WindowState::WindowMaximized))
            ui->maximumSizeBtn->setMaximumSized(true);
        else
            ui->maximumSizeBtn->setMaximumSized(false);
    }
}

/*!
    \reimp
*/
bool XTitleBar::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == parent())
    {
        auto w = qobject_cast<QWidget*>(this->parent());
        if (!w)
            return false;
        if (event->type() == QEvent::WindowStateChange)
        {
            auto w = qobject_cast<QWidget*>(this->parent());
            if (w)
            {
                if (w->windowState().testFlag(Qt::WindowState::WindowMaximized))
                    ui->maximumSizeBtn->setMaximumSized(true);
                else
                    ui->maximumSizeBtn->setMaximumSized(false);
            }
        }
        else if (event->type() == QEvent::WindowIconChange)
        {
            auto sizes = w->windowIcon().availableSizes();
            if (!sizes.isEmpty())
            {
                m_impl->windowIcon = w->windowIcon().pixmap(sizes.front());
#if QT_VERSION <= QT_VERSION_CHECK(5, 8, 0)
                int size = 16;
#else
                int size = this->style()->pixelMetric(QStyle::PM_TitleBarButtonIconSize);
#endif
                if (m_impl->windowIcon.height() > size)
                {
                    m_impl->windowIcon = m_impl->windowIcon.scaledToHeight(size, Qt::SmoothTransformation);
                }
                if (m_impl->showIcon)
                    ui->horizontalLayout->setContentsMargins(leftMargin + titleSpacing + m_impl->windowIcon.width(), 0, 0, 0);
            }
        }
        else if (event->type() == QEvent::WindowTitleChange)
        {
            update();
        }
        else if (event->type() == QEvent::Resize)
        {
            if (w->windowFlags().testFlag(Qt::WindowMaximizeButtonHint))
            {
                if (w->maximumSize() == w->minimumSize())
                    ui->maximumSizeBtn->hide();
                else
                    ui->maximumSizeBtn->show();
            }
        }     
    }
    return false;
}

/*!
    \reimp
*/
void XTitleBar::actionEvent(QActionEvent* event)
{
    if (event->type() == QEvent::ActionAdded)
    {
        auto item = std::make_shared<XWidgetItem>(event->action(), Qt::Horizontal, m_impl->iconSize, this);
        connect(this, &XTitleBar::iconSizeChanged, item.get(), &XWidgetItem::iconSizeChanged);
        XUtil::addItem(item, m_impl->items, event->before(), ui->actionLayout);
    }
    else
    {
        XUtil::removeItem(event->action(), m_impl->items, ui->actionLayout);
    }
}


/*!
    \brief      计算图标包围盒.
*/
QRect XTitleBar::doIconRect() const
{
    return { leftMargin, (this->height() - m_impl->windowIcon.height()) / 2, m_impl->windowIcon.width(), m_impl->windowIcon.height() };
}
