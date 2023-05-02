#ifndef BASEDATASTRINGPROCESSWDG_H
#define BASEDATASTRINGPROCESSWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "BaseDataStringProcess.h"

namespace Ui {
class BaseDataStringProcessWdg;
}

class BaseDataStringProcessWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit BaseDataStringProcessWdg(BaseDataStringProcess *func,QWidget *parent = nullptr);
    ~BaseDataStringProcessWdg();
protected:
    void initFrm() override;
protected slots:
    void onFuncRunUpdate() override;
    void onShow() override;
private:
    Ui::BaseDataStringProcessWdg *ui;


};

#endif // BASEDATASTRINGPROCESSWDG_H
