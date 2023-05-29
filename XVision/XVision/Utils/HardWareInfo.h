#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H
#include <QObject>
 #include <QTimer>
 #include <QProcess>
 #include <QDebug>
 #include <QString>
 #if defined(Q_OS_LINUX)
 #include "sys/statfs.h"
 #else
 #pragma comment(lib,"Kernel32.lib")
 #pragma comment(lib,"Psapi.lib")
 #include <windows.h>
 #include <tlhelp32.h>
 #include<direct.h>
 #include<winternl.h>
 #include <psapi.h>
 //#include <atlconv.h>
 #include <cmath>
 #include <string.h>
 #endif


class HardWareInfo
{
 public:
     explicit HardWareInfo();
 public:
     bool getMemUsage(double &nMemTotal,double &nMemUsed);
     bool getNetUsage();
     bool getDiskSpeed();
     bool getCpuUsage(double &nCpuRate);
     bool getdiskSpace(unsigned long &lFreeAll,unsigned long &lTotalAll);
     bool getPathSpace(const QString & path);

};

#endif // HARDWAREINFO_H
