#ifndef XLOGGER_H
#define XLOGGER_H

#include "XLogGlobal.h"
#include <QObject>

#define XLog XLogger::getInstance()
///日志类型宏定义
#define LType       XLogger::ELogType   ///日志类型

#define LTrace      XLogger::Trace      ///追踪类型
#define LDebug      XLogger::Debug      ///调试类型
#define LInfo       XLogger::Info       ///信息类型
#define LEvent      XLogger::Event      ///事件类型
#define LWarn       XLogger::Warn       ///警告类型
#define LError      XLogger::Error      ///错误类型
#define LCritical   XLogger::Critical   ///致命类型
///日志添加宏定义
#define Log(msg,type,...)  XLog->log(msg,type,(true,##__VA_ARGS__),__FILE__,__FUNCTION__)                       ///日志添加    (默认发送信号)
#define Log_Trace(msg,...)  XLog->log(msg,XLogger::Trace,(false,##__VA_ARGS__),__FILE__,__FUNCTION__)           ///追踪日志添加(默认不发送信号)
#define Log_Debug(msg,...)  XLog->log(msg,XLogger::Debug,(false,##__VA_ARGS__),__FILE__,__FUNCTION__)           ///调试日志添加(默认不发送信号)
#define Log_Info(msg,...)  XLog->log(msg,XLogger::Info,(true,##__VA_ARGS__),__FILE__,__FUNCTION__)              ///信息日志添加(默认发送信号)
#define Log_Event(msg,...)  XLog->log(msg,XLogger::Event,(true,##__VA_ARGS__),__FILE__,__FUNCTION__)            ///事件日志添加(默认发送信号)
#define Log_Warn(msg,...)  XLog->log(msg,XLogger::Warn,(true,##__VA_ARGS__),__FILE__,__FUNCTION__)              ///警告日志添加(默认发送信号)
#define Log_Error(msg,...)  XLog->log(msg,XLogger::Error,(true,##__VA_ARGS__),__FILE__,__FUNCTION__)            ///错误日志添加(默认发送信号)
#define Log_Critical(msg,...)  XLog->log(msg,XLogger::Critical,(true,##__VA_ARGS__),__FILE__,__FUNCTION__)      ///致命日志添加(默认发送信号)


///日志定义
#define SIGNAL_LOGGER_NAME "SignalLogger"
#define SIGNAL_PATTERN "[%Y-%m-%d %H:%M:%S.%e] %v"

#define FILE_LOGGER_NAME "FileLogger"
#define FILELOGGER_STARTHOUR 0
#define FILELOGGER_STARTMIN 0
#define FILELOGGER_PATTERN "[%Y-%m-%d %H:%M:%S.%e] [%l] [P-%P T-%t] %v"


#define XLOG_LEVEL_TRACE 0
#define XLOG_LEVEL_DEBUG 1
#define XLOG_LEVEL_INFO 2
#define XLOG_LEVEL_EVENT 3
#define XLOG_LEVEL_WARN 4
#define XLOG_LEVEL_ERROR 5
#define XLOG_LEVEL_CRITICAL 6


/*
 * XLogger:单例日志管理类
 * XLogger:存在两个日志器
 * SignalLogger:信号日志器，调用log插入日志时发送信号(可选)(不记录文件名和函数)
 * FileLogger:文件日志，调用log插入日志时记录到本地文件夹
*/

class XLoggerPrivate;
class XLOG_EXPORT XLogger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int flushMs READ flushMs WRITE setFlushMs)
    Q_PROPERTY(QString fileLogPattern READ fileLogPattern WRITE setFileLogPattern)
    Q_PROPERTY(QString signalLogPattern READ signalLogPattern WRITE setSignalLogPattern)
    Q_PROPERTY(XLogger::ELogType signalLevel READ signalLevel WRITE setSignalLevel)
//*[单例及构造]*
public:
    ///获取单例
    static XLogger* getInstance();
private:
    explicit XLogger();
    Q_DISABLE_COPY(XLogger)
    static XLogger* s_Instance;

    ~XLogger();



 //*[公共接口]*
public:

    enum ELogType : int
    {
        Trace = XLOG_LEVEL_TRACE,
        Debug = XLOG_LEVEL_DEBUG,
        Info = XLOG_LEVEL_INFO,
        Event=XLOG_LEVEL_EVENT,
        Warn = XLOG_LEVEL_WARN,
        Error = XLOG_LEVEL_ERROR,
        Critical = XLOG_LEVEL_CRITICAL,
    };
    Q_ENUM(ELogType)
    ///初始化日志
    /// logDirName:日志目录名称
    /// logFormatName:日志名称格式
    /// startHour:每日日志新建时
    /// startMin:每日日志新建分
    void init(QString logDirName="Log",QString logFormatName="%Y_%m_%d.log",int startHour=FILELOGGER_STARTHOUR,int startMin=FILELOGGER_STARTMIN);

 /*日志格式*/
    ///信号日志格式
    QString signalLogPattern() const;
    ///设置信号日志格式
    void setSignalLogPattern(QString pattern);

     ///文件日志格式
    QString fileLogPattern() const;
    ///设置文件日志格式
    void setFileLogPattern(QString pattern);

/*更新时间(ms)*/
    ///flushMs:日志更新毫秒
    int flushMs() const;
    ///设置文件日志更新毫秒
    void setFlushMs(int ms);


 /*日志输出等级*/
    ///信号日志等级
    XLogger::ELogType signalLevel() const;
    ///设置信号日志等级
    void setSignalLevel(const XLogger::ELogType &type);
 //*[信号和槽]*
signals:
    ///日志信号:
    /// log:添加的日志内容
    /// logType:日志类型
    void signalLog(const QString &log,const XLogger::ELogType &logType);

public slots:
/*日志插入*/
    /// \brief log:日志记录
    /// \param logMsg:日志信息
    /// \param logType:日志类型
    /// \param bSignalLog:是否发送signalLog信号
    /// \param sourceFile:源文件名称
    /// \param funcName:函数名
    void log(const QString &logMsg,const ELogType &logType=ELogType::Info,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = "");
/*类型日志插入*/
    inline void trace(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Trace,bSignalLog,sourceFile,funcName);}
    inline void debug(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Debug,bSignalLog,sourceFile,funcName);}
    inline void info(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Info,bSignalLog,sourceFile,funcName);}
    inline void event(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Event,bSignalLog,sourceFile,funcName);}
    inline void warn(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Warn,bSignalLog,sourceFile,funcName);}
    inline void error(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Error,bSignalLog,sourceFile,funcName);}
    inline void critical(const QString &logMsg,bool bSignalLog=true,const QString &sourceFile="",const QString& funcName = ""){ return log(logMsg,ELogType::Critical,bSignalLog,sourceFile,funcName);}


 //*[私有类]*
protected:
    const QScopedPointer<XLoggerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(XLogger)

};

#endif // XLOGGER_H
