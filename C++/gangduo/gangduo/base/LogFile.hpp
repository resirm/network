#ifndef GANGDUO_BASE_LOGFILE_HPP
#define GANGDUO_BASE_LOGFILE_HPP

#include "gangduo/base/Types.hpp"
#include "gangduo/base/noncopyable.hpp"
#include <memory>
#include <mutex>

namespace gangduo
{

namespace FileUtil
{
class AppendFile;
} // namespace FileUtil

class LogFile: noncopyable
{
public:
    LogFile(const string& basename,
            off_t rollSize,
            bool threadSafe = true,
            int flushInterval = 3,
            int checkEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollFile();

private:
    void append_unlocked(const char* logline, int len);

    static string getLogFileName(const string& basename, time_t* now);

private:
    const string basename_;
    const off_t rollSize_;
    const int flushInterval_;
    const int checkEveryN_;

    int count_;

    std::unique_ptr<std::mutex> mutex_;
    time_t startOfPeriod_;
    time_t lastRoll_;
    time_t lastFlush_;
    std::unique_ptr<FileUtil::AppendFile> file_;

    const static int nRollPerSeconds_ = 60*60*24;
};

} // namespace gangduo

#endif // !GANGDUO_BASE_LOGFILE_HPP