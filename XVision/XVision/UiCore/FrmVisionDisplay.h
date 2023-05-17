#ifndef FRMVISIONDISPLAY_H
#define FRMVISIONDISPLAY_H

#include "BaseWidget.h"

namespace Ui {
class FrmVisionDisplay;
}
#define UiVisionDisplay FrmVisionDisplay::getInstance()

class FrmVisionDisplay : public BaseWidget
{
    Q_OBJECT

public:
    static FrmVisionDisplay* getInstance();
private:
    explicit FrmVisionDisplay(QWidget *parent = nullptr);
    ~FrmVisionDisplay();
    Q_DISABLE_COPY(FrmVisionDisplay)

protected:
    void initFrm() override;

private:
    Ui::FrmVisionDisplay *ui;
    static FrmVisionDisplay* s_Instance;


};

#endif // FRMVISIONDISPLAY_H
