#ifndef XVSINGLEAPPLICATION_H
#define XVSINGLEAPPLICATION_H

#include <QApplication>
#include "singleapplication.h"

class AppMainWindow;
class XvSingleApplication:public SingleApplication
{
    Q_OBJECT
public:
    XvSingleApplication(int &argc, char **argv);
    //app初始化
    bool init();
    //app反初始化
    bool uninit();
    //app运行
    int run();

protected:
    AppMainWindow* m_appMainWindow=nullptr;
};

#endif // XVSINGLEAPPLICATION_H
