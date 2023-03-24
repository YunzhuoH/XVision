#ifndef WDGITEMXVFUNC_H
#define WDGITEMXVFUNC_H

#include "BaseWidget.h"
#include "XvFuncDef.h"


namespace Ui {
class WdgItemXvFunc;
}

class WdgItemXvFunc : public BaseWidget
{
    Q_OBJECT

public:
    explicit WdgItemXvFunc(const XvCore::XvFuncBaseInfo &info,QWidget *parent = nullptr);
    ~WdgItemXvFunc();
    // BaseWidget interface
protected:
    void initFrm() override;
signals:
    void xvFuncDrag(QString role);
protected slots:
    void onXvFunc();
private:
    Ui::WdgItemXvFunc *ui;
    XvCore::XvFuncBaseInfo m_xvFuncInfo;


};

#endif // WDGITEMXVFUNC_H
