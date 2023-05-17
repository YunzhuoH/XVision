#ifndef IMAGEACQUISITION_P_H
#define IMAGEACQUISITION_P_H

#include <QDir>
#include <QString>
#include <QImage>
#include <QMetaEnum>

namespace XvCore
{
struct SDirImage
{
    SDirImage()
    {

    }
    bool update(const QString &_dir)
    {
        if(_dir.isEmpty())
        {
            return false;
        }
        QDir qDir(_dir);
        if(!qDir.exists())
        {
            return false;
        }
        lst.clear();
        dir=_dir;
        idx=0;
        auto infos = qDir.entryInfoList();
        foreach (auto info, infos)
        {
            QImage image;
            if(image.load(info.filePath()))
            {
                image.setText("Name",info.fileName());
                QMetaEnum meta = QMetaEnum::fromType<QImage::Format>();
                QString format=meta.valueToKey(image.format());
                image.setText("Format",format);
                lst.append(image);
            }
        }
        return true;
    }
    bool getCurIdxImage(QImage &img)
    {
        if(lst.count()==0)
        {
            return false;
        }
        if(idx>=lst.count())
        {
            idx=0;
        }
        img=lst.at(idx);
        idx++;
        return true;
    }

    int getIdx() const
    {
        return idx;
    }

    void setIdx(const int &_idx)
    {
       if(_idx>=lst.count())
       {
           idx=0;
       }
       else if(_idx<0)
       {
           idx=lst.count()-1;
       }
       else
       {
           idx=_idx;
       }

    }



    QString dir; //目录
    QList<QImage> lst;//图像列表
    int  idx;//当前索引
};
}


#endif // IMAGEACQUISITION_P_H
