#ifndef GANGDUO_BASE_LOGGING_HPP
#define GANGDUO_BASE_LOGGING_HPP

#include "gangduo/base/LogStream.hpp"
#include "gangduo/base/Timestamp.hpp" // empty!

namespace gangduo
{

class TimeZone; // forward declaration

class Logger
{
public:
    enum class LogLevel 
    {  // scoped enumeration
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };

    class SourceFile
    {
    public:
        template<int N>
        SourceFile(const char (&arr)[N]): data_(arr), size_(N-1){
            const char* slash = strrchr(data_, '/'); // find last '/'
            if(slash){
                data_ = slash + 1;
                size_ -= static_cast<int>(data_ - arr);
            }
        }

        explicit SourceFile(const char* filename):data_(filename){
            const char* slash = strrchr(data_, '/'); // find last '/'
            if(slash){
                data_ = slash + 1;
            }
            size_ = static_cast<int>(strlen(data_));
        }

        const char* data_;
        int size_;
    };

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, LogLevel level);
    Logger(SourceFile file, int line, LogLevel level, const char* func);
    Logger(SourceFile file, int line, bool toAbort);
    ~Logger();

    LogStream& stream() { return impl_.stream_; }

    static LogLevel logLevel();
    static void setLogLevel(LogLevel level);

    using OutputFunc = void(*)(const char* msg, int len);
    using FlushFunc = void(*)();
    static void setOutput(OutputFunc);
    static void setFlush(FlushFunc);
    static void setTimeZone(const TimeZone& tz);

private:
    class Impl
    {
    public:
        using LogLevel = Logger::LogLevel;
        Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
        void formatTime();
        void finish();

        Timestamp time_;
        LogStream stream_;
        LogLevel level_;
        int line_;
        SourceFile basename_;
    };

    Impl impl_;
};

} // namespace gangduo

#endif // !GANGDUO_BASE_LOGGING_HPP