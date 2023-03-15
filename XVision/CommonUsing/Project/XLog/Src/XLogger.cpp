#include "XLogger.h"
#include "XLogSignalSink.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <QMutexLocker>

/****************************************/
class XLoggerPrivate
{
    Q_DISABLE_COPY(XLoggerPrivate)
    Q_DECLARE_PUBLIC(XLogger)

public:
    XLoggerPrivate(XLogger *q):q_ptr(q)
    {
        flushMs=500;
    };
    virtual ~XLoggerPrivate(){};
public:
    XLogger                                 *const q_ptr;///XLogger
    int                                     flushMs;    ///flush冲洗毫秒(总体)
    std::shared_ptr<spdlog::logger>         fileLogger;///每日日志文件logger
    std::shared_ptr<spdlog::logger>         signalLogger;///XLogSignalSink日志
    std::string                             fileLogPattern;///每日日志文件格式
    std::string                             signalLogPattern;///XLogSignalSink日志文件格式
    spdlog::level::level_enum               signalLevel;///XLogSignalSink日志输出等级

};
/****************************************/




/****************************************/
XLogger::XLogger()
    :d_ptr(new XLoggerPrivate(this))
{
    Q_D(XLogger);
    d->signalLogger=XSignalLogger_MT(SIGNAL_LOGGER_NAME,this);
    d->signalLevel=spdlog::level::trace;
    d->signalLogger->set_level(d->signalLevel);///设置最低等级输出，外部可更改
    d->signalLogPattern=SIGNAL_PATTERN;
    d->signalLogger->set_pattern(d->signalLogPattern);  ///设置日志格式

    spdlog::flush_every(std::chrono::milliseconds(d->flushMs));///设置日志刷新时间间隔
}
XLogger::~XLogger()
{
    spdlog::drop_all();
}

void XLogger::init(QString logDirName,QString logFormatName, int startHour, int startMin)
{
    Q_D(XLogger);
    d->fileLogger= spdlog::daily_logger_format_mt(FILE_LOGGER_NAME, logDirName.toStdString()+"/"+logFormatName.toStdString(), startHour, startMin);
    d->fileLogger->set_level(spdlog::level::trace);///设置最低等级输出，外部不可更改
    d->fileLogPattern=FILELOGGER_PATTERN;
    d->fileLogger->set_pattern(d->fileLogPattern);///设置日志格式,外部可更改
}

QString XLogger::signalLogPattern() const
{
    Q_D(const XLogger);
    return QString::fromStdString(d->signalLogPattern);
}

void XLogger::setSignalLogPattern(QString pattern)
{
    Q_D(XLogger);
    d->signalLogPattern=pattern.toStdString();
    d->signalLogger->set_pattern(d->signalLogPattern);
}

QString XLogger::fileLogPattern() const
{
    Q_D(const XLogger);
    return QString::fromStdString(d->fileLogPattern);
}

void XLogger::setFileLogPattern(QString pattern)
{
    Q_D(XLogger);
    if(d->fileLogger==nullptr)
    {
        init();
    }
    d->fileLogPattern=pattern.toStdString();
    d->fileLogger->set_pattern(d->fileLogPattern);
}

int XLogger::flushMs() const
{
   Q_D(const XLogger);
   return d->flushMs;
}

void XLogger::setFlushMs(int ms)
{
    if(ms>0)
    {
       Q_D(XLogger);
       d->flushMs=ms;
       spdlog::flush_every(std::chrono::milliseconds(d->flushMs));
    }
}

XLogger::ELogType XLogger::signalLevel() const
{
    Q_D(const XLogger);
    XLogger::ELogType type=( XLogger::ELogType)d->signalLevel;
    return type;
}

void XLogger::setSignalLevel(const ELogType &type)
{
    Q_D(XLogger);
    spdlog::level::level_enum level=(spdlog::level::level_enum)type;
    d->signalLevel=level;
    d->signalLogger->set_level(d->signalLevel);

}

void XLogger::log(const QString &logMsg, const ELogType &logType, bool bXLogSignals,const QString &sourceFile,const QString& funcName)
{
    Q_D(XLogger);
    if(d->fileLogger==nullptr)
    {
        init();
    }
    spdlog::level::level_enum level=( spdlog::level::level_enum)logType;
    QString _log=logMsg;
    QString strTemp;
    if(!sourceFile.isEmpty())
    {
        QString fileName = sourceFile;
#if defined(XLOG_COMPILE_MSVC)
        int first = sourceFile.lastIndexOf ("\\");
        fileName = sourceFile.right(sourceFile.length ()-first-1);
#else
        int first = sourceFile.lastIndexOf ("/");
        fileName = sourceFile.right(sourceFile.length ()-first-1);
#endif
        strTemp="<"+fileName+">";
    }
    if(!funcName.isEmpty())
    {
        strTemp+="<"+funcName+">";
    }
    if(!strTemp.isEmpty())
    {
        _log=strTemp+" "+_log;
    }
    d->fileLogger->log(level,_log.toStdString());
    if(bXLogSignals)
    {
        d->signalLogger->log(level,logMsg.toStdString());
    }
}



XLogger *XLogger::s_Instance = NULL;
XLogger *XLogger::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XLogger();
    }
  }
  return s_Instance;
}
/****************************************/
