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
    //app运行
    int run();

};

#endif // XVSINGLEAPPLICATION_H
