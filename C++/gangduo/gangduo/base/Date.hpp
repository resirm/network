#ifndef GANGDUO_BASE_DATE_HPP
#define GANGDUO_BASE_DATE_HPP

#include "gangduo/base/copyable.hpp"
#include "gangduo/base/Types.hpp"

struct tm;

namespace gangduo
{

class Date: public copyable{
public:
    struct YearMonthDay{
        int year;
        int month;
        int day;
    };

    static const int nDaysPerWeek = 7;
    static const int nJulianDayOf1970_01_01;

    Date(): julianDayNumber_(0) {}

    Date(int year, int month, int day);

    explicit Date(int julianDayNum):julianDayNumber_(julianDayNum) {}

    explicit Date(const struct tm&);

    void swap(Date& rhs){
        std::swap(julianDayNumber_, rhs.julianDayNumber_);
    }

    bool valid() const { return julianDayNumber_ > 0; }

    string toIsoString() const;

    struct YearMonthDay yearMonthDay() const;

    int year() const { return yearMonthDay().year; }

    int month() const { return yearMonthDay().month; }

    int day() const { return yearMonthDay().day; }

    int weekDay() const{
        return (julianDayNumber_ + 1) % nDaysPerWeek;
    }

    int julianDayNumber() const { return julianDayNumber_; }

private:
    int julianDayNumber_;
};

inline bool operator==(Date lhs, Date rhs){
    return lhs.julianDayNumber() == rhs.julianDayNumber();
}

inline bool operator<(Date lhs, Date rhs){
    return lhs.julianDayNumber() < rhs.julianDayNumber();
}

inline bool operator!=(Date lhs, Date rhs){
    return !(lhs == rhs);
}

inline bool operator<=(Date lhs, Date rhs){
    return !(rhs < lhs);
}

inline bool operator>(Date lhs, Date rhs){
    return rhs < lhs;
}

inline bool operator>=(Date lhs, Date rhs){
    return !(lhs < rhs);
}

} // namespace gangduo

#endif // !GANGDUO_BASE_DATE_HPP