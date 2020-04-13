#ifndef GANGDUO_BASE_CURRENTTHREAD_HPP
#define GANGDUO_BASE_CURRENTTHREAD_HPP

#include "gangduo/base/Types.hpp"

#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

namespace gangduo
{

namespace CurrentThread
{
    extern thread_local int t_cachedTid;  // all should be __thread to get better performance
    extern thread_local char t_tidString[32];
    extern thread_local int t_tidStringLength;
    extern thread_local const char* t_threadName;
    void cacheTid();

    inline int tid(){
        if(unlikely(t_cachedTid == 0)){
            cacheTid();
        }
        return t_cachedTid;
    }

    inline const char* tidString(){
        return t_tidString;
    }

    inline int tidStringLength(){
        return t_tidStringLength;
    }

    inline const char* name(){
        return t_threadName;
    }

    bool isMainThread();

    void sleepUsec(int64_t usec);

    string stackTrace(bool demangle);
} // namespace CurrentThread

} // namespace gangduo

#endif // !GANGDUO_BASE_CURRENTTHREAD_HPP