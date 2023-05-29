#include "HardWareInfo.h"

HardWareInfo::HardWareInfo()
{

}

bool HardWareInfo::getMemUsage(double &nMemTotal,double &nMemUsed)
{
#if defined(Q_OS_LINUX)
    QProcess process;
    process.start("free -m"); //使用free完成获取
    process.waitForFinished();
    process.readLine();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");//将连续空格替换为单个空格 用于分割
    auto lst = str.split(" ");
    if(lst.size() > 6)
    {
        nMemTotal = lst[1].toDouble();
        nMemUsed = nMemTotal-lst[6].toDouble();
        return true;
    }
    else
    {
        return false;
    }
#else
    MEMORYSTATUSEX memsStat;
        memsStat.dwLength = sizeof(memsStat);
        if(!GlobalMemoryStatusEx(&memsStat))//如果获取系统内存信息不成功，就直接返回
        {
            return false;
        }
        double nMemFree = memsStat.ullAvailPhys/( 1024.0*1024.0 );
        nMemTotal = memsStat.ullTotalPhys/( 1024.0*1024.0 );
        nMemUsed= nMemTotal- nMemFree;
        return true;
#endif
}
bool HardWareInfo::getNetUsage()
{
#if defined(Q_OS_LINUX)
    QProcess process;
    process.start("cat /proc/net/dev"); //读取文件/proc/net/dev获取网络收发包数量，再除取样时间得到网络速度
    process.waitForFinished();
    process.readLine();
    process.readLine();
    while(!process.atEnd())
    {
        QString str = process.readLine();
        str.replace("\n","");
        str.replace(QRegExp("( ){1,}")," ");
        auto lst = str.split(" ");
        if(lst.size() > 9 && lst[0] == "enp2s0:")
        {
            double recv = 0;
            double send = 0;
            if(lst.size() > 1)
                recv = lst[1].toDouble();
            if(lst.size() > 9)
                send = lst[9].toDouble();
            m_recv_bytes__ = recv;
            m_send_bytes__ = send;
        }
    }
#endif
    return true;
}
#if defined(Q_OS_WIN32)
__int64 Filetime2Int64(const FILETIME* ftime)
{
    LARGE_INTEGER li;
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

__int64 CompareFileTime(FILETIME preTime,FILETIME nowTime)
{
    return Filetime2Int64(&nowTime) - Filetime2Int64(&preTime);
}
#endif
bool HardWareInfo::getCpuUsage(double &nCpuRate)
{
    nCpuRate = -1;
#if defined(Q_OS_LINUX)
    QProcess process;
    process.start("cat /proc/stat");
    process.waitForFinished();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
    auto lst = str.split(" ");
    if(lst.size() > 3)
    {
        double use = lst[1].toDouble() + lst[2].toDouble() + lst[3].toDouble();
        double total = 0;
        for(int i = 1;i < lst.size();++i)
            total += lst[i].toDouble();
        if(total - m_cpu_total__ > 0)
        {
            m_cpu_total__ = total;
            m_cpu_use__ = use;
            nCpuRate = (use - m_cpu_use__) / (total - m_cpu_total__) * 100.0;
            return true;
        }
    }
#else
    HANDLE hEvent;
        bool res;
        static FILETIME preIdleTime;
        static FILETIME preKernelTime;
        static FILETIME preUserTime;
        FILETIME idleTime;
        FILETIME kernelTime;
        FILETIME userTime;
        res = GetSystemTimes(&idleTime,&kernelTime,&userTime);
        preIdleTime = idleTime;
        preKernelTime = kernelTime;
        preUserTime = userTime;
        hEvent = CreateEvent(nullptr,FALSE,FALSE,nullptr);//初始值为nonsignaled
        WaitForSingleObject(hEvent,500);//等待500毫秒
        res = GetSystemTimes(&idleTime,&kernelTime,&userTime);
        long long idle = CompareFileTime(preIdleTime,idleTime);
        long long kernel = CompareFileTime(preKernelTime,kernelTime);
        long long user = CompareFileTime(preUserTime,userTime);
        nCpuRate =ceil( 100.0*( kernel + user - idle ) / ( kernel + user ) );
#endif
    return true;
}
bool HardWareInfo::getDiskSpeed()
{
#if defined(Q_OS_LINUX)
    QProcess process;
    process.start("iostat -k -d");
    process.waitForFinished();
    process.readLine();
    process.readLine();
    process.readLine();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
    auto lst = str.split(" ");
    if(lst.size() > 5)
    {
        m_disk_read__ = lst[4].toDouble();
        m_disk_write__ = lst[5].toDouble();
        return true;
    }
#endif
    return false;
}
bool HardWareInfo::getdiskSpace(unsigned long &lFreeAll,unsigned long &lTotalAll)
{
#if defined(Q_OS_LINUX)
    QProcess process;
    process.start("df -k");
    process.waitForFinished();
    process.readLine();
    while(!process.atEnd())
    {
        QString str = process.readLine();
        if(str.startsWith("/dev/sda"))
        {
            str.replace("\n","");
            str.replace(QRegExp("( ){1,}")," ");
            auto lst = str.split(" ");

            lFreeAll += lst[2].toDouble()/1024.0;
            lTotalAll += lst[3].toDouble()/1024.0+lFreeAll;
        }
    }
#else

    static char path[_MAX_PATH];//存储当前系统存在的盘符
    int curdrive = _getdrive();
    lFreeAll = 0UL;
    lTotalAll = 0UL;
    for(int drive = 1; drive <= curdrive; drive++ )//遍历所有盘符
    {
        if( !_chdrive( drive ) )
        {
            sprintf(path, "%c:\\", drive + 'A' - 1 );
            ULARGE_INTEGER caller, total, free;
            WCHAR wszClassName[_MAX_PATH];
            memset(wszClassName,0,sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP,0,path,strlen(path)+1,wszClassName,
                sizeof(wszClassName)/sizeof(wszClassName[0]));
            if (GetDiskFreeSpaceEx(wszClassName, &caller, &total, &free) == 0)
            {
                return false;
            }

            double dTepFree = free.QuadPart/( 1024.0*1024.0 );
            double dTepTotal = total.QuadPart/( 1024.0*1024.0 );
            lFreeAll += ceil(dTepFree);
            lTotalAll += ceil(dTepTotal);
        }
    }
#endif
    return true;
}

bool HardWareInfo::getPathSpace(const QString & path)
{
#if defined(Q_OS_LINUX)
    struct statfs diskInfo;//需要#include "sys/statfs.h"
    statfs(path.toUtf8().data(), &diskInfo);
 #endif
    return true;
}
