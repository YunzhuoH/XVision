#ifndef IMAGEACQUISITION_H
#define IMAGEACQUISITION_H

#include "XVFuncSystemGlobal.h"
#include "XvFunc.h"
#include "XLanguage.h"

class ImageAcquisitionWdg;
namespace XvCore
{
class ImageAcquisitionParam:public XvBaseParam
{
public:
    ImageAcquisitionParam()
    {

    }
public:


};



class ImageAcquisitionResult:public XvBaseResult
{
public:
    ImageAcquisitionResult()
    {
        acqType=new XInt("acqType",0,this,getLang("XvFuncSystem_ImageAcquisition_AcqType","采集类型"));
        acqLocalPath=new XString("acqLocalPath","",this,getLang("XvFuncSystem_ImageAcquisition_AcqLocalPath","本地路径"));
        outputImage=new XImage("outputImage",QImage(),this,getLang("XvFuncSystem_ImageAcquisition_OutputImage","输出图像"));
        outputImageMsg=new XString("outputImageMsg","",this,getLang("XvFuncSystem_ImageAcquisition_OutputImageMsg","输出图像信息"));
        outputImageWidth=new XInt("outputImageWidth",0,this,getLang("XvFuncSystem_ImageAcquisition_OutputImageWidth","输出图像宽度"));
        outputImageHeight=new XInt("outputImageHeight",0,this,getLang("XvFuncSystem_ImageAcquisition_OutputImageHeight","输出图像高度"));
        outputImageDepth=new XInt("outputImageDepth",0,this,getLang("XvFuncSystem_ImageAcquisition_OutputImageDepth","输出图像深度"));
    }
public:
    XInt *acqType=nullptr;
    XString *acqLocalPath=nullptr;

    XImage *outputImage=nullptr;
    XString *outputImageMsg=nullptr;
    XInt   *outputImageWidth=nullptr;
    XInt   *outputImageHeight=nullptr;
    XInt   *outputImageDepth=nullptr;

};
struct SDirImage;
class XVFUNCSYSTEM_EXPORT ImageAcquisition:public XvFunc
{
    Q_OBJECT
    friend class ImageAcquisitionWdg;
public:
    Q_INVOKABLE explicit ImageAcquisition(QObject *parent = nullptr);
    ~ImageAcquisition();
public:
    //采集类型
    enum AcqType
    {
        File=0,
        Dir=1,
        Camera=2,
    };
    Q_ENUMS(AcqType);
    AcqType acqType() const {return m_AcqType;}
    void setAcqType(AcqType type)
    {
        m_AcqType=type;
        result->acqType->setValue(type);
        switch (m_AcqType)
        {
        case AcqType::File:
            result->acqLocalPath->setValue(m_strLocalFile);
            break;
        case AcqType::Dir:
            result->acqLocalPath->setValue(m_strLocalDir);
            break;
        case AcqType::Camera:
            result->acqLocalPath->setValue("");
            break;
        }
    }
public:
    ///本地路径
    QString localFlie() const { return m_strLocalFile; }
    void setLocalFile(const QString &path)
    {
        m_strLocalFile=path;
        result->acqLocalPath->setValue(m_strLocalFile);
    }
    ///本地目录
    QString localDir() const { return m_strLocalDir; }
    void setLocalDir(const QString &dir)
    {
        m_strLocalDir=dir;
        result->acqLocalPath->setValue(m_strLocalDir);
    }

protected:
    ///设置输出的图像
    void setOutputImage(const QImage &img);
public slots:
    void onShowFunc() override;
protected:
    QPixmap funcIcon() override { return QPixmap(":/images/ImageAcquisition.svg");}
    EXvFuncRunStatus run() override;
    XvBaseParam *getParam() const override { return param;};
    XvBaseResult *getResult() const override { return result;};
protected:
    ImageAcquisitionParam *param=nullptr;
    ImageAcquisitionResult *result=nullptr;
    ImageAcquisitionWdg* m_frm=nullptr;
    AcqType             m_AcqType=AcqType::File;
    QString             m_strLocalFile="";//本地路径
    QString             m_strLocalDir="";//本地目录
    SDirImage*          m_sDirImage=nullptr;
};
}

#endif // IMAGEACQUISITION_H
