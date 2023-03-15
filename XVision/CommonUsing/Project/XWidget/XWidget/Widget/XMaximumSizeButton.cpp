#include "XMaximumSizeButton_p.h"

#include <QStyle>

XMaximumSizeButton::XMaximumSizeButton(QWidget* parent) : QPushButton(parent), m_maxsized(false) {}

XMaximumSizeButton::~XMaximumSizeButton() {}

void XMaximumSizeButton::setMaximumSized(bool max)
{
    this->style()->unpolish(this);
    m_maxsized = max;
    this->style()->polish(this);
}

bool XMaximumSizeButton::maximumSized() const { return m_maxsized; }
