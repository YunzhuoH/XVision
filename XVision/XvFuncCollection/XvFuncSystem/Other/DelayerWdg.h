#ifndef DELAYERWDG_H
#define DELAYERWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "Delayer.h"


namespace Ui {
class DelayerWdg;
}
using namespace XvCore;
class DelayerWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit DelayerWdg(Delayer *func,QWidget *parent = nullptr);
    ~DelayerWdg();
protected:
    void initFrm() override;
protected slots:
    void onShow() override;
private:
    Ui::DelayerWdg *ui;


};

#endif // DELAYERWDG_H
