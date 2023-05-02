#ifndef BASEDATABOOLCALCWDG_H
#define BASEDATABOOLCALCWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "BaseDataBoolCalc.h"


namespace Ui {
class BaseDataBoolCalcWdg;
}
using namespace XvCore;
class BaseDataBoolCalcWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit BaseDataBoolCalcWdg(BaseDataBoolCalc *func,QWidget *parent = nullptr);
    ~BaseDataBoolCalcWdg();
protected:
    void initFrm() override;
protected slots:
    void onFuncRunUpdate() override;
    void onShow() override;
private:
    Ui::BaseDataBoolCalcWdg *ui;


};

#endif // BASEDATABOOLCALCWDG_H
