#ifndef FRMMAINWORK_H
#define FRMMAINWORK_H

#include <QWidget>

namespace Ui {
class FrmMainWork;
}

class FrmMainWork : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMainWork(QWidget *parent = nullptr);
    ~FrmMainWork();

private:
    Ui::FrmMainWork *ui;
};

#endif // FRMMAINWORK_H
