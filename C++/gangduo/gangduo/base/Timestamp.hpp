#ifndef GANGDUO_BASE_TIMESTAMP_HPP
#define GANGDUO_BASE_TIMESTAMP_HPP

#include "gangduo/base/copyable.hpp"
#include "gangduo/base/Types.hpp"

namespace gangduo
{

class Timestamp: public copyable
{
public:
    Timestamp():microSecondsSinceEpoch_(0) {}

    explicit Timestamp(int64_t microSecondsSinceEpochArg)
        :microSecondsSinceEpoch_(microSecondsSinceEpochArg) {}
    
    void swap(Timestamp& rhs){
        std::swap(microSecondsSinceEpoch_, rhs.microSecondsSinceEpoch_);
    }

    string toString() const;
    string toFormattedString(bool showMicroSeconds = true) const;

    bool valid() const { return microSecondsSinceEpoch_ > 0; }

    int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
    time_t secondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch_ / nMicroSecondsPerSecond);
    }

    static Timestamp now();
    static Timestamp invalid() { return Timestamp(); }

    static Timestamp fromUnixTime(time_t t){
        return fromUnixTime(t, 0);
    }

    static Timestamp fromUnixTime(time_t t, int microseconds){
        return Timestamp(static_cast<int64_t>(t) * nMicroSecondsPerSecond + microseconds);
    }

    static const int nMicroSecondsPerSecond = 1000*1000;
private:
    int64_t microSecondsSinceEpoch_;
};

inline bool operator==(Timestamp lhs, Timestamp rhs){
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline bool operator<(Timestamp lhs, Timestamp rhs){
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator!=(Timestamp lhs, Timestamp rhs){
    return !(lhs == rhs);
}

inline bool operator<=(Timestamp lhs, Timestamp rhs){
    return !(rhs < lhs);
}

inline bool operator>(Timestamp lhs, Timestamp rhs){
    return rhs < lhs;
}

inline bool operator>=(Timestamp lhs, Timestamp rhs){
    return !(lhs < rhs);
}

inline double timeDifference(Timestamp high, Timestamp low){
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::nMicroSecondsPerSecond;
}

inline Timestamp addTime(Timestamp timestamp, double seconds){
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::nMicroSecondsPerSecond);
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

} // namespace gangduo

#endif // !GANGDUO_BASE_TIMESTAMP_HPP