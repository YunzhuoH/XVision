#ifndef XCONCURRENTMANAGER_H
#define XCONCURRENTMANAGER_H

#include "XConcurrentGlobal.h"
#include <QObject>
#include <QtConcurrent>
#include "XThread.h"

#define XConcurrentMgr XConcurrentManager::getInstance()

class QThreadPool;
class XThread;
class XConcurrentManagerPrivate;
class XCONCURRENT_EXPORT XConcurrentManager : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(XConcurrentManager)
    //单例/构造析构
public:
    static XConcurrentManager *getInstance();
protected:
    const QScopedPointer<XConcurrentManagerPrivate> d_ptr;
private:
    explicit XConcurrentManager(QObject *parent = nullptr);
    ~XConcurrentManager();
    static XConcurrentManager* s_Instance;

/*---------------------XThreads常驻线程---------------------*/
public:
 //[*线程创建/销毁*]
    ///创建线程
    /// groupNameRepeat:是否允许同组线程名称重复
    /// autoRemove:线程结束自动删除
    template <typename Function, typename... Args>
    XThread* createThreadByFunction(const XTHREAD_GROUP &group,const QString &name,bool groupNameRepeat,bool autoRemove,Function &&f, Args &&... args);

    ///创建线程
    /// groupNameRepeat:是否允许同组线程名称重复
    /// autoRemove:线程结束自动删除
    template <typename Function, typename... Args>
    XThread* createThreadByFuture(const XTHREAD_GROUP &group,const QString &name,bool groupNameRepeat,bool autoRemove,Function &&f, Args &&... args);

    ///通过ID删除线程
    bool removeThread(const XTHREAD_ID &id);
    ///线程删除
    bool removeThread(XThread* thread);

//[*线程获取*]
    ///获取线程列表
    QList<XThread*> threads() const;
    ///获取组线程
    QList<XThread*> getThreadsByGroup(const XTHREAD_GROUP &group);
    ///通过名称获取线程
    QList<XThread*> getThreadsByName(const QString &name);
    ///通过ID获取线程
    XThread* getThreadsById(const XTHREAD_ID &id);
    ///通过组和名称获取线程
    XThread* getThreadsByGropuName(const XTHREAD_GROUP &group,const QString &name);

/*---------------------临时线程池---------------------*/
public:
 //[*临时线程创建*]
    template <class Function, class ...Args>
    [[nodiscard]]
    auto run(Function &&f, Args &&...args)
    {
        return QtConcurrent::run(tempThreadPool(), std::forward<Function>(f),
                                 std::forward<Args>(args)...);
    }

    template <typename Sequence, typename MapFunctor>
    QFuture<void> map(Sequence &&sequence, MapFunctor &&map)
    {
        return QtConcurrent::map(tempThreadPool(), sequence.begin(), sequence.end(),
                        std::forward<MapFunctor>(map));
    }
    template <typename Iterator, typename MapFunctor>
    QFuture<void> map(Iterator begin, Iterator end, MapFunctor &&map)
    {
        return QtConcurrent::map(tempThreadPool(), begin, end, std::forward<MapFunctor>(map));
    }


//[*线程池获取*]
    QThreadPool* tempThreadPool() const;
private:
    //获取新线程Id
    int getNewThreadId();
    ///私有线程创建
    XThread* createThreadImpl(XThread* thread,const XTHREAD_GROUP &group,const QString &name,bool groupNameRepeat,bool autoRemove);

signals:    //信号
    void sgXThreadCreate(XThread* thread);//线程创建
    void sgXThreadRemove(XThread* thread);//线程删除

    void sgXThreadStart(XThread* thread );//线程开始运行
    void sgXThreadEnd(XThread* thread);//线程运行结束

protected slots://槽函数
    ///线程销毁事件
    void onXThreadDestroyed(QObject *object);

};

template <typename Function, typename... Args>
XThread *XConcurrentManager::createThreadByFunction(const XTHREAD_GROUP &group,const QString &name,bool groupNameRepeat,bool autoRemove,Function &&f, Args &&... args)
{
    XThread* th=XThread::createByFunction(std::move(f),std::forward<Args>(args)...);
    return createThreadImpl(th,group,name,groupNameRepeat,autoRemove);
}
template <typename Function, typename... Args>
XThread *XConcurrentManager::createThreadByFuture(const XTHREAD_GROUP &group,const QString &name,bool groupNameRepeat,bool autoRemove,Function &&f, Args &&... args)
{
    XThread* th=XThread::createByFuture(std::move(f),std::forward<Args>(args)...);
    return createThreadImpl(th,group,name,groupNameRepeat,autoRemove);
}
#endif // XCONCURRENTMANAGER_H
