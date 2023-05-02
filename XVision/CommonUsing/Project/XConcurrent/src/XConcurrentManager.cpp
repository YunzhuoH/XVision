#include "XConcurrentManager.h"
#include "XThread.h"

#include <QMutexLocker>
#include <QThreadPool>

/**************************************************************/
//* [XConcurrentManagerPrivate]
/**************************************************************/
class XConcurrentManagerPrivate
{
    Q_DISABLE_COPY(XConcurrentManagerPrivate)
    Q_DECLARE_PUBLIC(XConcurrentManager)

public:
    XConcurrentManagerPrivate(XConcurrentManager *q):q_ptr(q)
    {
        tempThreadPool=nullptr;
    };
    ~XConcurrentManagerPrivate(){};

    void init();
public:
    XConcurrentManager      *const q_ptr;

    QMutex                  mutex;//互斥锁
    QList<XThread*>         xThreads;//线程列表
    QThreadPool*            tempThreadPool;//临时线程池

};
void XConcurrentManagerPrivate::init()
{
    Q_Q(XConcurrentManager);
    tempThreadPool=new QThreadPool(q);
}

/**************************************************************/
//* [XConcurrentManager]
/**************************************************************/
XConcurrentManager::XConcurrentManager(QObject *parent)
    : QObject{parent},d_ptr(new XConcurrentManagerPrivate(this))
{
    d_ptr->init();
}

XConcurrentManager::~XConcurrentManager()
{

}

bool XConcurrentManager::removeThread(const XTHREAD_ID &id)
{
    Q_D(XConcurrentManager);
    QMutexLocker locker(&d->mutex);
    XThread* thTemp=nullptr;
    foreach (auto th, d->xThreads)
    {
        if(th->id()==id)
        {
           thTemp=th;
           break;
        }
    }
    locker.unlock();
    if(!thTemp)
    {
        return false;
    }
    else
    {
        d->xThreads.removeOne(thTemp);
        emit this->sgXThreadRemove(thTemp);
        thTemp->deleteLater();
        return true;
    }

}

bool XConcurrentManager::removeThread(XThread *thread)
{
    Q_D(XConcurrentManager);
    QMutexLocker locker(&d->mutex);
    bool bExist=false;
    foreach (auto th, d->xThreads)
    {
        if(th==thread)
        {
           bExist=true;
           break;
        }
    }
    locker.unlock();
    if(!bExist)
    {
        return false;
    }
    else
    {
        d->xThreads.removeOne(thread);
        emit this->sgXThreadRemove(thread);
        thread->deleteLater();
        return true;
    }
}

QList<XThread *> XConcurrentManager::threads() const
{
    Q_D(const XConcurrentManager);
    return d->xThreads;
}

QList<XThread *> XConcurrentManager::getThreadsByGroup(const XTHREAD_GROUP &group)
{
    Q_D(XConcurrentManager);
    QMutexLocker locker(&d->mutex);
    QList<XThread*> lst;
    foreach (auto th, d->xThreads)
    {
        if(th->group()==group)
        {
            lst.append(th);
        }
    }
    locker.unlock();
    return lst;
}

QList<XThread *> XConcurrentManager::getThreadsByName(const QString &name)
{
    Q_D(XConcurrentManager);
    QMutexLocker locker(&d->mutex);
    QList<XThread*> lst;
    foreach (auto th, d->xThreads)
    {
        if(th->name()==name)
        {
            lst.append(th);
        }
    }
    locker.unlock();
    return lst;
}

XThread *XConcurrentManager::getThreadsById(const XTHREAD_ID &id)
{
    Q_D(XConcurrentManager);
    foreach (auto th, d->xThreads)
    {
        if(th->id()==id)
        {
            return th;
        }
    }
    return nullptr;
}

XThread *XConcurrentManager::getThreadsByGropuName(const XTHREAD_GROUP &group, const QString &name)
{
    Q_D(XConcurrentManager);
    foreach (auto th, d->xThreads)
    {
        if(th->group()==group&&th->name()==name)
        {
            return th;
        }
    }
    return nullptr;
}

QThreadPool *XConcurrentManager::tempThreadPool() const
{
    Q_D(const XConcurrentManager);
    if(!d->tempThreadPool)
    {
        return QThreadPool::globalInstance();
    }
    else
    {
        return d->tempThreadPool;
    }
}

int XConcurrentManager::getNewThreadId()
{
    Q_D(XConcurrentManager);
    int id=0;
    auto ths=d->xThreads;
    QList<XTHREAD_ID> lst;
    foreach (auto th, ths)
    {
        int thId=th->id();
        lst.append(thId);
    }
    foreach (auto thId, lst)
    {
        if(lst.contains(id))
        {
            id++;
        }
        else
        {
            break;
        }
    }
    return id;
}


XThread* XConcurrentManager::createThreadImpl(XThread *thread, const XTHREAD_GROUP &group, const QString &name,bool groupNameRepeat,bool autoRemove)
{
    Q_D(XConcurrentManager);
    if(!thread)
    {
        return nullptr;
    }
    if(!groupNameRepeat)//检查是否名称重复
    {
        foreach (auto th, d->xThreads)
        {
            if(th->group()==group&&th->name()==name)//组和名称重复 进行删除
            {
                thread->deleteLater();
                return nullptr;
            }
        }
    }

    QMutexLocker locker(&d->mutex);

    thread->setId(getNewThreadId());
    thread->setGroup(group);
    thread->setName(name);
    thread->setObjectName("xThread_"+name);
    d->xThreads.append(thread);
    connect(thread,&XThread::destroyed,this,&XConcurrentManager::onXThreadDestroyed);
    connect(thread,&XThread::started,this,[&]()
    {
        auto objTh=sender();
        if(!objTh) return;
        auto th=qobject_cast<XThread*>(objTh);
        if(!th) return;
        emit this->sgXThreadStart(th);
    });
    connect(thread,&XThread::finished,this,[=]()
    {
        auto objTh=sender();
        if(!objTh) return;
        auto th=qobject_cast<XThread*>(objTh);
        if(!th) return;
        emit this->sgXThreadEnd(th);
        if(autoRemove)
        {
            this->removeThread(th);
        }
    });
    locker.unlock();
    emit this->sgXThreadCreate(thread);
    return thread;
}

void XConcurrentManager::onXThreadDestroyed(QObject *object)
{
    Q_D(XConcurrentManager);
    auto thread=qobject_cast<XThread*>(object);
    if(!thread) return;
    foreach (auto th, d->xThreads)
    {
        if(th==thread)
        {
            d->xThreads.removeOne(th);
            emit this->sgXThreadRemove(thread);
            break;
        }
    }
}

XConcurrentManager *XConcurrentManager::s_Instance = NULL;
XConcurrentManager *XConcurrentManager::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XConcurrentManager();
    }
  }
  return s_Instance;
}



