#include "FrmVisionImage.h"
#include "ui_FrmVisionImage.h"
#include <QMutexLocker>

FrmVisionImage *FrmVisionImage::s_Instance = NULL;
FrmVisionImage *FrmVisionImage::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new FrmVisionImage();
    }
  }
  return s_Instance;
}


FrmVisionImage::FrmVisionImage(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::FrmVisionImage)
{
    ui->setupUi(this);
    initFrm();
}

FrmVisionImage::~FrmVisionImage()
{
    delete ui;
}

void FrmVisionImage::initFrm()
{
    this->setWindowIcon(QIcon(":/images/Ui/FrmVisionImage.svg"));
    this->setWindowTitle(getLang(App_Ui_FrmVisionImage,"图像"));
}
