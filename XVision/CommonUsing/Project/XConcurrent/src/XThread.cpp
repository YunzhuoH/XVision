#include "XThread.h"
#include <QTimer>

/**************************************************************/
//* [XThreadPrivate]
/**************************************************************/
class XThreadPrivate
{
    Q_DISABLE_COPY(XThreadPrivate)
    Q_DECLARE_PUBLIC(XThread)

public:
    XThreadPrivate(XThread *q):q_ptr(q)
    {
        id=-1;
        group="";
        name="";

        runElapsed=0;

    };
    ~XThreadPrivate(){};

public:    //属性
    XTHREAD_ID          id;//线程id
    XTHREAD_GROUP       group;//线程组id
    QString             name;//线程名称
    QString             msg;//线程消息
public:    //数据
    XThread                     *const q_ptr;
    std::function<void()>       runFunc;            //运行回调函数
    std::future<void>           runFuture;          //运行Future
    std::function<void()>       stop;               //停止回调函数
    QElapsedTimer               runTimer;           //运行计时器
    double                      runElapsed;         //运行耗时
};


/**************************************************************/
//* [XThread]
/**************************************************************/
XThread::XThread(std::function<void()> &&run)
    :d_ptr(new XThreadPrivate(this))
{
    Q_D(XThread);
    d->runFunc=std::move(run);
    connect(this,&XThread::started,this,&XThread::onXThreadRunStart);
    connect(this,&XThread::finished,this,&XThread::onXThreadRunEnd);
}

XThread::XThread(std::future<void> &&run)
    :d_ptr(new XThreadPrivate(this))
{
    Q_D(XThread);
    d->runFuture=std::move(run);
    connect(this,&XThread::started,this,&XThread::onXThreadRunStart);
    connect(this,&XThread::finished,this,&XThread::onXThreadRunEnd);

}

XThread::~XThread()
{
    requestInterruption();
    quit();
    wait();
}




void XThread::run()
{
    Q_D(XThread);
    if(d->runFunc)
    {
        d->runFunc();
    }
    if(d->runFuture.valid())
    {
        d->runFuture.share().get();
    }

}
bool XThread::stop()
{
    Q_D(XThread);
    if(d->stop)
    {
       d->stop();
       return true;
    }
    else
    {
        return false;
    }
}


XThread *XThread::createThreadByFunctionImpl(std::function<void()> &&run)
{
    return new XThread(std::move(run));
}

XThread *XThread::createThreadByFutureImpl(std::future<void> &&run)
{
    return new XThread(std::move(run));
}

void XThread::setStopImpl(std::function<void()>  &&stop)
{
    Q_D(XThread);
    d->stop=std::move(stop);
}


///开始运行 进行计时
void XThread::onXThreadRunStart()
{
    Q_D(XThread);
    d->runTimer.start();
    emit this->sgXThreadRunStart(this);
}
///运行结束 更新计时
void XThread::onXThreadRunEnd()
{
   Q_D(XThread);
   d->runElapsed=(d->runTimer.nsecsElapsed()*1.0)/1000/1000;
   d->runTimer.restart();
   emit this->sgXThreadRunEnd(this);
}
///运行耗时获取:
/// 运行时更新获取
double XThread::runElapsed()
{
   Q_D(XThread);
   if(isRunning())
   {
      d->runElapsed=(d->runTimer.nsecsElapsed()*1.0)/1000/1000;
   }
   return d->runElapsed;
}

void XThread::setMsg(const QString &msg)
{
    Q_D(XThread);
    d->msg=msg;
}

QString XThread::msg() const
{
    Q_D(const XThread);
    return d->msg;
}

bool XThread::isCanStop()
{
    Q_D(XThread);
    if(d->stop)
    {
       return true;
    }
    else
    {
       return false;
    }
}






XTHREAD_ID XThread::id() const
{
    Q_D(const XThread);
    return d->id;
}

XTHREAD_GROUP XThread::group() const
{
    Q_D(const XThread);
    return d->group;
}

QString XThread::name() const
{
    Q_D(const XThread);
    return d->name;
}

void XThread::setId(const XTHREAD_ID &id)
{
    Q_D(XThread);
    d->id=id;
}

void XThread::setGroup(const XTHREAD_GROUP &group)
{
    Q_D(XThread);
    d->group=group;
}

void XThread::setName(const QString &name)
{
    Q_D(XThread);
    d->name=name;
}







