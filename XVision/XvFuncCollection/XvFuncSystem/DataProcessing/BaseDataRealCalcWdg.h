#ifndef BASEDATAREALCALCWDG_H
#define BASEDATAREALCALCWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "BaseDataRealCalc.h"


namespace Ui {
class BaseDataRealCalcWdg;
}
using namespace XvCore;
class BaseDataRealCalcWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit BaseDataRealCalcWdg(BaseDataRealCalc *func,QWidget *parent = nullptr);
    ~BaseDataRealCalcWdg();
protected:
    void initFrm() override;
protected slots:
    void onFuncRunUpdate() override;
    void onShow() override;
private:
    Ui::BaseDataRealCalcWdg *ui;

};

#endif // BASEDATAREALCALCWDG_H
