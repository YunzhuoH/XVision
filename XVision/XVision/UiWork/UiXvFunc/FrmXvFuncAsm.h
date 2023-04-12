#ifndef FRMXVFUNCASM_H
#define FRMXVFUNCASM_H

#include "BaseWidget.h"


#include <QVBoxLayout>
#include "XMatDrawer.h"
#include "XvCoreDef.h"
#include "FrmXvFuncType.h"

namespace Ui {
class FrmXvFuncAsm;
}

class FrmXvFuncAsm : public BaseWidget
{
    Q_OBJECT

public:
    explicit FrmXvFuncAsm(QWidget *parent = nullptr);
    ~FrmXvFuncAsm();
    void setDrawerParWidget(QWidget* drawerParWidget);

protected slots:
    void onShowXvFuncTypeDrawer(const QRect &rect,const XvCore::EXvFuncType &type);

public:
    bool eventFilter(QObject *watched, QEvent *event) override;
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
protected:
    void initFrm() override;

private:
    Ui::FrmXvFuncAsm *ui;
    //抽屉显示父窗口
    QWidget* m_drawerParWidget=nullptr;
    ///当前单类型算子抽屉(临时抽屉)
    XMatDrawer* m_drawerCurSingleTypeXvFuncs=nullptr;
    ///单类型算子抽屉
    QMap<XvCore::EXvFuncType,XMatDrawer*> m_mapXMatDrawerType;
    ///所有算子抽屉
    XMatDrawer* m_drawerAllTypeXvFuncs=nullptr;



};

#endif // FRMXVFUNCASM_H
