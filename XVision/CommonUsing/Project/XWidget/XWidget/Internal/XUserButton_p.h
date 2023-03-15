#pragma once

#include <memory>

#include "XToolButton_p.h"

class QStyleOptionToolButton;

class XUserButton : public XToolButton
{
    Q_OBJECT
public:
    XUserButton(QWidget* parent = nullptr);
    ~XUserButton();

protected:
    void paintEvent(QPaintEvent*) override;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    QRect doTextRect(const QStyleOptionToolButton& opt) const;
    QRect doIconRect(const QStyleOptionToolButton& opt) const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
