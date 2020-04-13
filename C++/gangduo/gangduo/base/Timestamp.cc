#include "gangduo/base/Timestamp.hpp"

#include <sys/time.h>
#include <stdio.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif // !__STDC_FORMAT_MACROS

#include <inttypes.h>

namespace gangduo
{

static_assert(sizeof(Timestamp) == sizeof(int64_t),
            "Timestamp should be the same size as int64_t");

string Timestamp::toString() const{
    char buf[32] = {0};
    int64_t seconds = microSecondsSinceEpoch_ / nMicroSecondsPerSecond;
    int64_t microseconds = microSecondsSinceEpoch_ % nMicroSecondsPerSecond;
    snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
    return buf;
}

string Timestamp::toFormattedString(bool showMicroseconds) const{
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / nMicroSecondsPerSecond);
    struct tm tm_time;
    gmtime_r(&seconds, &tm_time);

    if(showMicroseconds){
        int microseconds = static_cast<int>(microSecondsSinceEpoch_ % nMicroSecondsPerSecond);
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                microseconds);
    }else{
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;
}

Timestamp Timestamp::now(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    return Timestamp(seconds * nMicroSecondsPerSecond + tv.tv_usec);
}

} // namespace gangduo