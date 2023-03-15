#ifndef VFUNC_T2_H
#define VFUNC_T2_H

#include "VFuncTest_A_global.h"
#include "XVFuncBase.h"
class VFUNCTEST_A_EXPORT VFunc_T2:public XvFuncBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit VFunc_T2(QObject *parent = nullptr);

    // IVFuncBase interface
protected:
    EVFucRunResult run() override;

public:
    QString m_tokenTest;
};

#endif // VFUNC_T2_H
