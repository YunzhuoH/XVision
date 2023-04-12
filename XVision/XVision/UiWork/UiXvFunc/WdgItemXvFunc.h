#ifndef WDGITEMXVFUNC_H
#define WDGITEMXVFUNC_H

#include "BaseWidget.h"
#include "XvCoreDef.h"


namespace Ui {
class WdgItemXvFunc;
}

class WdgItemXvFunc : public BaseWidget
{
    Q_OBJECT

public:
    explicit WdgItemXvFunc(const XvCore::XvFuncInfo &info,QWidget *parent = nullptr);
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
    XvCore::XvFuncInfo m_xvFuncInfo;


};

#endif // WDGITEMXVFUNC_H
