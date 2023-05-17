#ifndef FRMXVFUNCRESULT_H
#define FRMXVFUNCRESULT_H

#include "BaseWidget.h"

#define UiXvFuncResult FrmXvFuncResult::getInstance()

namespace XvCore
{
class XvFunc;
}
namespace Ui {
class FrmXvFuncResult;
}

class FrmXvFuncResult : public BaseWidget
{
    Q_OBJECT
public:
    static FrmXvFuncResult* getInstance();

private:
    explicit FrmXvFuncResult(QWidget *parent = nullptr);
    ~FrmXvFuncResult();
     Q_DISABLE_COPY(FrmXvFuncResult)

protected:
    void initFrm() override;

protected slots:
    ///更新算子
    void onUpdateXvFunc(XvCore::XvFunc* func);

    ///更新算子结果
    void onUpdateXvFuncResult();
private:
    Ui::FrmXvFuncResult *ui;
    static FrmXvFuncResult* s_Instance;
    XvCore::XvFunc* m_curFunc=nullptr;

};

#endif // FRMXVFUNCRESULT_H
