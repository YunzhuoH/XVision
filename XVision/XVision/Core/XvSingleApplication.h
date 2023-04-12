#ifndef XVSINGLEAPPLICATION_H
#define XVSINGLEAPPLICATION_H

#include <QApplication>
#include "singleapplication.h"

class XvSingleApplication:public SingleApplication
{
    Q_OBJECT
public:
    XvSingleApplication(int &argc, char **argv);
    //app初始化
    void init();
    //app反初始化
    void uninit();
    //是否初始化完成
    bool isInit();

    //app运行
    int run();

protected:
    ///是否初始化完成
    bool m_bInitFinish;
};



#endif // XVSINGLEAPPLICATION_H
