#ifndef FRMVISIONWORK_H
#define FRMVISIONWORK_H

#include "BaseWidget.h"

namespace Ui {
class FrmVisionWork;
}
#define UiVisionWork FrmVisionWork::getInstance()

class FrmXvFuncAsm;
class FrmVisionWork : public BaseWidget
{
    Q_OBJECT
public:
    static FrmVisionWork* getInstance();
private:
    explicit FrmVisionWork(QWidget *parent = nullptr);
    ~FrmVisionWork();
     Q_DISABLE_COPY(FrmVisionWork)

protected:
    void initFrm() override;
private:
    Ui::FrmVisionWork *ui;
    static FrmVisionWork* s_Instance;

    FrmXvFuncAsm* m_frmXvFuncAsm=nullptr;
};

#endif // FRMVISIONWORK_H
