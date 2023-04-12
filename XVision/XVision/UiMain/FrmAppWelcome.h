#ifndef FRMAPPWELCOME_H
#define FRMAPPWELCOME_H

#include "BaseWidget.h"

namespace Ui {
class FrmAppWelcome;
}
class XvSingleApplication;
class FrmAppWelcome : public BaseWidget
{
    Q_OBJECT

public:
    explicit FrmAppWelcome(QWidget *parent = nullptr);
    ~FrmAppWelcome();
public slots:
    void onShow();
    void onHide();
protected:
    void initFrm() override;
private:
    Ui::FrmAppWelcome *ui;
};

#endif // FRMAPPWELCOME_H
