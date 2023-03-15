#pragma once

#include <QStyleOption>
#include <QWidget>

class XSeparator : public QWidget
{
    Q_OBJECT

public:
    XSeparator(Qt::Orientation orientation, QWidget* parent = nullptr);
    ~XSeparator();

    Qt::Orientation orientation() const;

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent*) override;
    void initStyleOption(QStyleOption* opt) const;

public slots:
    void setOrientation(Qt::Orientation orientation);

private:
    Qt::Orientation m_orientation;
};
