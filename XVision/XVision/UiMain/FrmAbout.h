#ifndef FRMABOUT_H
#define FRMABOUT_H

#include <QWidget>
#include "XFramelessDialog.h"

namespace Ui {
class FrmAbout;
}

class FrmAbout : public XFramelessDialog
{
    Q_OBJECT

public:
    explicit FrmAbout(QWidget *parent = nullptr);
    ~FrmAbout();

private:
    Ui::FrmAbout *ui;
};

#endif // FRMABOUT_H
