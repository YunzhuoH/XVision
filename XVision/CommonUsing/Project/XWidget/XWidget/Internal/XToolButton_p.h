#pragma once

#include <QToolButton>

#include <memory>

class XToolButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(bool showToolTips READ showToolTips WRITE setShowToolTips)
public:
    XToolButton(QWidget* parent);
    ~XToolButton();

    void setIcon(const QIcon& icon);
    void setShowToolTips(bool show);
    bool showToolTips() const;
    void setSelected(bool select);

protected:
    bool event(QEvent* e) override;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    void initStyleOption(QStyleOptionToolButton* option) const override;
#else
    void paintEvent(QPaintEvent*) override;
#endif

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
