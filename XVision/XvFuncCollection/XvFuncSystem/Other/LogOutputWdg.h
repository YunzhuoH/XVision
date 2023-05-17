#ifndef LOGOUTPUTWDG_H
#define LOGOUTPUTWDG_H

#include <QWidget>
#include "BaseSystemFuncWdg.h"
#include "LogOutput.h"


namespace Ui {
class LogOutputWdg;
}
using namespace XvCore;
class LogOutputWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit LogOutputWdg(LogOutput *func,QWidget *parent = nullptr);
    ~LogOutputWdg();
protected:
    void initFrm() override;
protected slots:
    void onShow() override;
private:
    Ui::LogOutputWdg *ui;


};

#endif // LOGOUTPUTWDG_H
