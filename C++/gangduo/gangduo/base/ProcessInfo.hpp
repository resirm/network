#ifndef GANGDUO_BASE_PROCESSINFO_HPP
#define GANGDUO_BASE_PROCESSINFO_HPP

#include "gangduo/base/StringPiece.hpp"
#include "gangduo/base/Types.hpp"
#include "gangduo/base/Timestamp.hpp"

#include <vector>
#include <sys/types.h>

namespace gangduo
{

namespace ProcessInfo
{
    pid_t pid();
    string pidString();
    uid_t uid();
    string username();
    uid_t euid();
    Timestamp startTime();
    int clockTicksPerSecond();
    int pageSize();
    bool isDebugBuild();

    string hostname();
    string procname();
    StringPiece procname(const string& stat);

    // read /proc/self/status
    string procStatus();

    // read /proc/self/stat
    string procStat();

    // read /proc/self/task/tid/stat
    string threadStat();

    // read /proc/self/exe
    string exePath();

    int openedFiles();
    int maxOpenFiles();

    struct CpuTime
    {
        double userSeconds;
        double systemSeconds;

        CpuTime(): userSeconds(0.0), systemSeconds(0.0) { }
    
        double total() const { return userSeconds + systemSeconds; }
    };
    CpuTime cpuTime();

    int numThreads();
    std::vector<pid_t> threads();

} // namespace ProcessInfo

} // namespace gangduo

#endif // !GANGDUO_BASE_PROCESSINFO_HPP