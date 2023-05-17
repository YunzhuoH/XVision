#include "ImageAcquisition.h"
#include "ImageAcquisitionWdg.h"

#include "ImageAcquisition_p.h"

using namespace XvCore;


ImageAcquisition::ImageAcquisition(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="ImageAcquisition";
    _funcName=getLang("XvFuncSystem_ImageAcquisition_Name","图像采集");
    _funcType=EXvFuncType::ImageAcquisition;

    param=new ImageAcquisitionParam();
    result=new ImageAcquisitionResult();

    m_sDirImage=new SDirImage();
}

ImageAcquisition::~ImageAcquisition()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
    if(m_sDirImage)
    {
        delete m_sDirImage;
        m_sDirImage=nullptr;
    }
}

bool ImageAcquisition::upDateLocalAcq()
{
    switch (m_AcqType)
    {
    case AcqType::File:
    {

    }
        break;
    case AcqType::Dir:
    {

    }
        break;
    case AcqType::Camera:
    {
        return false;
    }
        break;
    }
    return true;
}

void ImageAcquisition::setOutputImage(const QImage &img)
{
    result->outputImage->setValue(img);
    result->outputImageWidth->setValue(img.width());
    result->outputImageHeight->setValue(img.height());
    result->outputImageDepth->setValue(img.depth());
    result->outputImageMsg->setValue(result->outputImage->toString());
}

void ImageAcquisition::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new ImageAcquisitionWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus ImageAcquisition::run()
{
    switch (m_AcqType)
    {
    case AcqType::File:
    {
        QImage image;
        if(!image.load(m_strLocalFile))
        {
            this->setRunMsg(getLang("XvFuncSystem_ImageAcquisition_RunError1","读取文件图像失败"));
            return EXvFuncRunStatus::Error;
        }
        image.setText("Name",QFileInfo(m_strLocalFile).fileName());
        QMetaEnum meta = QMetaEnum::fromType<QImage::Format>();
        QString format=meta.valueToKey(image.format());
        image.setText("Format",format);

        setOutputImage(image);
    }
        break;
    case AcqType::Dir:
    {
        if(m_sDirImage->dir!=m_strLocalDir)
        {
           bool bRet= m_sDirImage->update(m_strLocalDir);
           if(!bRet)
           {
               this->setRunMsg(getLang("XvFuncSystem_ImageAcquisition_RunError2","刷新目录图像失败"));
               return EXvFuncRunStatus::Error;
           }
        }
        QImage img;
        bool bRet=m_sDirImage->getCurIdxImage(img);
        if(!bRet)
        {
            this->setRunMsg(getLang("XvFuncSystem_ImageAcquisition_RunError3","获取目录图像失败"));
            return EXvFuncRunStatus::Error;
        }
        setOutputImage(img);
    }
        break;
    case AcqType::Camera:
    {
        this->setRunMsg("xie.y:相机采集未实现");
        return EXvFuncRunStatus::Error;
    }
        break;
    }
    this->setRunMsg(getLang("XvFuncSystem_ImageAcquisition_RunOk","获取图像成功"));
    return EXvFuncRunStatus::Ok;
}
