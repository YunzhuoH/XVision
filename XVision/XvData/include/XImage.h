#ifndef XIMAGE_H
#define XIMAGE_H

#include "XObject.h"
#include <QImage>

#define XImageType "XImage"
class XVDATA_EXPORT XImage:public XObject
{
public:
    XImage(const QString &objectName,const QImage &value=QImage(),XObjectSet* parObjectSet=nullptr,const QString &dispalyName="");
    XImage(const QImage &value);
    XImage();
    ~XImage();
    static QString type() { return XImageType;}
    XObject *clone() override { return new XImage(*this);}
public://重载
    QString toString() const override;
    QString typeName() override { return XImageType;}
    bool getData(XObject *object) override;
    bool setData(XObject *object) override;

public://*[数据操作]*
    //设置数据
    void setValue(const QImage &value);
    //获取数据
    QImage value() const
    {
        return _value;
    }

protected:
//*[数据区]*
    ///图像
    QImage _value;

};



#endif // XIMAGE_H
