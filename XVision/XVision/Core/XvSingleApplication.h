#ifndef XVSINGLEAPPLICATION_H
#define XVSINGLEAPPLICATION_H

#include <QApplication>
#include "singleapplication.h"

class XvSingleApplicationPrivate;
class XvSingleApplication:public SingleApplication
{
    Q_OBJECT
public:
    XvSingleApplication(int &argc, char **argv);
    ~XvSingleApplication();
    //app初始化
    void init();
    //app反初始化
    void uninit();
    //是否初始化完成
    bool isInit();
    //是否正在运行
    bool isRunning() { return m_bIsRunning;};
    //app运行
    int run();

    ///获取软件运行时间
    qint64 getAppRunTime();
protected:
    ///是否初始化完成
    bool m_bInitFinish;
    ///是否正在运行
    bool m_bIsRunning;

protected:
    const QScopedPointer<XvSingleApplicationPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(XvSingleApplication)

};



#endif // XVSINGLEAPPLICATION_H
