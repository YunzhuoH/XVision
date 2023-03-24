#ifndef FRMVISIONIMAGE_H
#define FRMVISIONIMAGE_H

#include "BaseWidget.h"

namespace Ui {
class FrmVisionImage;
}
#define UiVisionImage FrmVisionImage::getInstance()

class FrmVisionImage : public BaseWidget
{
    Q_OBJECT

public:
    static FrmVisionImage* getInstance();
private:
    explicit FrmVisionImage(QWidget *parent = nullptr);
    ~FrmVisionImage();
    Q_DISABLE_COPY(FrmVisionImage)

protected:
    void initFrm() override;

private:
    Ui::FrmVisionImage *ui;
    static FrmVisionImage* s_Instance;


};

#endif // FRMVISIONIMAGE_H
