#ifndef XTHREAD_H
#define XTHREAD_H

#include "XConcurrentGlobal.h"
#include <QThread>

class XConcurrentManager;
class XThreadPrivate;
class XCONCURRENT_EXPORT XThread:public QThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(XThread)

    friend class XConcurrentManager;
protected:
    explicit XThread(std::function<void()> &&run);
    explicit XThread(std::future<void> &&run);
public:
    ~XThread();

protected:
    const QScopedPointer<XThreadPrivate> d_ptr;

public:
    ///线程ID
    XTHREAD_ID id() const;
    ///线程组ID
    XTHREAD_GROUP group() const;
    ///线程名称
    QString name() const;
    ///线程运行耗时(ms)
    double runElapsed();

    ///设置消息
    void setMsg(const QString &msg);
    ///获取消息
    QString msg() const;

    ///是否可以停止
    bool isCanStop();
    ///线程停止
    bool stop();
    ///设置停止回调函数
    template <typename Function, typename... Args>
    void setStop(Function &&f, Args &&... args);

protected:
    ///设置ID
    void setId(const XTHREAD_ID &id);
    ///设置线程组ID
    void setGroup(const XTHREAD_GROUP &group);
    ///设置名称
    void setName(const QString &name);

    ///创建线程(function)
    template <typename Function, typename... Args>
    [[nodiscard]] static XThread *createByFunction(Function &&f, Args &&... args);

    ///创建线程(future)
    template <typename Function, typename... Args>
    [[nodiscard]] static XThread *createByFuture(Function &&f, Args &&... args);
private:
    ///运行私有化
    void run() override;
    ///私有创建函数(function)
    [[nodiscard]] static XThread *createThreadByFunctionImpl(std::function<void()> &&run);
    ///私有创建函数(future)
    [[nodiscard]] static XThread *createThreadByFutureImpl(std::future<void> &&run);
    ///设置停止函数
    void setStopImpl(std::function<void()>  &&stop);
signals:
    ///线程开始运行
    void sgXThreadRunStart(XThread*);
    ///线程结束运行
    void sgXThreadRunEnd(XThread*);

protected slots:
    ///线程开始运行
    void onXThreadRunStart();
    ///线程运行结束
    void onXThreadRunEnd();
};



template <typename Function, typename... Args>
void XThread::setStop(Function &&f, Args &&...args)
{
    return setStopImpl(std::bind(f,std::forward<Args>(args)...));
}

template <typename Function, typename... Args>
XThread *XThread::createByFunction(Function &&f, Args &&... args)
{
    return createThreadByFunctionImpl(std::bind(f,std::forward<Args>(args)...));
}

template <typename Function, typename... Args>
XThread *XThread::createByFuture(Function &&f, Args &&... args)
{
    using DecayedFunction = typename std::decay<Function>::type;
    auto threadFunction =
        [f = static_cast<DecayedFunction>(std::forward<Function>(f))](auto &&... largs) mutable -> void
        {
            (void)std::invoke(std::move(f), std::forward<decltype(largs)>(largs)...);
        };

    return createThreadByFutureImpl(std::async(std::launch::deferred,
                                       std::move(threadFunction),
                                       std::forward<Args>(args)...));
}


#endif // XTHREAD_H
