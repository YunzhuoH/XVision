#ifndef IMAGEACQUISITIONWDG_H
#define IMAGEACQUISITIONWDG_H

#include "BaseSystemFuncWdg.h"
#include "ImageAcquisition.h"

using namespace XvCore;

namespace Ui {
class ImageAcquisitionWdg;
}
class XMatTabs;
class ImageAcquisitionWdg : public BaseSystemFuncWdg
{
    Q_OBJECT

public:
    explicit ImageAcquisitionWdg(ImageAcquisition *func,QWidget *parent = nullptr);
    ~ImageAcquisitionWdg();

protected:
    void initFrm() override;
protected slots:
    void onShow() override;


private:
    Ui::ImageAcquisitionWdg *ui;
    XMatTabs* m_tabs=nullptr;
};

#endif // IMAGEACQUISITIONWDG_H
