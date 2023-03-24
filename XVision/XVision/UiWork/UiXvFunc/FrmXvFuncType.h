#ifndef FRMXVFUNCTYPE_H
#define FRMXVFUNCTYPE_H

#include "BaseWidget.h"
#include "XvFuncDef.h"

namespace Ui {
class FrmXvFuncType;
}

class FrmXvFuncType : public BaseWidget
{
    Q_OBJECT

public:
    explicit FrmXvFuncType(const XvCore::XvFuncTypeInfo &info, const QList<XvCore::XvFuncBaseInfo> &lst,QWidget *parent = nullptr);
    ~FrmXvFuncType();

protected:
    void initFrm() override;
signals:
    void closeDrawer();  
protected slots:
    void onCloseDrawer();

private:
    Ui::FrmXvFuncType *ui;
    XvCore::XvFuncTypeInfo m_typeInfo;
    QList<XvCore::XvFuncBaseInfo> m_lstXvFuncInfos;

};

#endif // FRMXVFUNCTYPE_H
