#ifndef XNAVIGATIONIMAGEBUTTON_P_H
#define XNAVIGATIONIMAGEBUTTON_P_H


#include "XToolButton_p.h"

#include <memory>

class XNavigationImageButton : public XToolButton
{
    Q_OBJECT

public:
    XNavigationImageButton(QWidget* parent);
    ~XNavigationImageButton();

protected:
    void paintEvent(QPaintEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
    QSize sizeHint() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
#endif //XNAVIGATIONIMAGEBUTTON_P_H
