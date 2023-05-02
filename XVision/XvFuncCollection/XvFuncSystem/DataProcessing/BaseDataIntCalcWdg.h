#ifndef BASEDATAINTCALCWDG_H
#define BASEDATAINTCALCWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "BaseDataIntCalc.h"


namespace Ui {
class BaseDataIntCalcWdg;
}
using namespace XvCore;
class BaseDataIntCalcWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit BaseDataIntCalcWdg(BaseDataIntCalc *func,QWidget *parent = nullptr);
    ~BaseDataIntCalcWdg();
protected:
    void initFrm() override;
protected slots:
    void onFuncRunUpdate() override;
    void onShow() override;
private:
    Ui::BaseDataIntCalcWdg *ui;


};

#endif // BASEDATAIntCALCWDG_H
