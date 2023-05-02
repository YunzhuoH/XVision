#ifndef BASEDATAWRITERWDG_H
#define BASEDATAWRITERWDG_H

#include "BaseSystemFuncWdg.h"
#include "BaseDataWriter.h"

namespace Ui {
class BaseDataWriterWdg;
}
using namespace XvCore;
class BaseDataWriterWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit BaseDataWriterWdg(BaseDataWriter *fun,QWidget *parent = nullptr);
    ~BaseDataWriterWdg();

protected:
    void initFrm() override;
protected slots:
    void onShow() override;
private:
    Ui::BaseDataWriterWdg *ui;



};

#endif // BASEDATAWRITERWDG_H
