#ifndef XLOGSIGNALSINK_H
#define XLOGSIGNALSINK_H

#include "spdlog/common.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/details/synchronous_factory.h"
#include "XLogger.h"

template<typename Mutex>
class XLogSignalSink: public spdlog::sinks::base_sink <Mutex>
{
public:
    XLogSignalSink(XLogger* logger):m_xLogger(logger){};

    ~XLogSignalSink()
    {
        flush_();
    }

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        if(m_xLogger)
        {
            spdlog::memory_buf_t formatted;
            spdlog::sinks:: base_sink<Mutex>::formatter_->format(msg, formatted);
            spdlog::string_view_t str = spdlog::string_view_t(formatted.data(), formatted.size());
            QString log=QString::fromUtf8(str.data(), static_cast<int>(str.size())).trimmed();
            XLogger::ELogType type=(XLogger::ELogType )msg.level;
            emit m_xLogger->signalLog(log,type);
        }

    }

    void flush_() override {}
private:
    XLogger* m_xLogger;
};

#include "spdlog/details/null_mutex.h"
#include <mutex>
using XLogSignalSink_MT = XLogSignalSink<std::mutex>;///多线程
using XLogSignalSink_ST = XLogSignalSink<spdlog::details::null_mutex>;///单线程

template<typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<spdlog::logger> XSignalLogger_MT(const std::string &logger_name,XLogger *xLogger)
{
    return Factory::template create<XLogSignalSink_MT>(logger_name,xLogger);
}

template<typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<spdlog::logger> XSignalLogger_ST(const std::string &logger_name,XLogger *xLogger)
{
    return Factory::template create<XLogSignalSink_ST>(logger_name,xLogger);
}

#endif // XLOGSIGNALSINK_H
