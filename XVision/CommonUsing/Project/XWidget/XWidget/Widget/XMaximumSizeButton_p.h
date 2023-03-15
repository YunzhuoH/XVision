#ifndef XMAXIMUMSIZEBUTTON_H
#define XMAXIMUMSIZEBUTTON_H
#include <QPushButton>

class XMaximumSizeButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(bool maximumsized READ maximumSized WRITE setMaximumSized)
public:
    XMaximumSizeButton(QWidget* parent);
    ~XMaximumSizeButton();

    void setMaximumSized(bool max);
    bool maximumSized() const;

private:
    bool m_maxsized;
};
#endif //XMAXIMUMSIZEBUTTON_H
