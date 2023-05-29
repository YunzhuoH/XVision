#ifndef HMODELMATCHWDG_H
#define HMODELMATCHWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "HModelMatch.h"


namespace Ui {
class HModelMatchWdg;
}
using namespace XvCore;
class HModelMatchWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit HModelMatchWdg(HModelMatch *func,QWidget *parent = nullptr);
    ~HModelMatchWdg();
protected:
    void initFrm() override;
protected slots:
    void onShow() override;
private:
    Ui::HModelMatchWdg *ui;


};


#endif // HMODELMATCHWDG_H
