#ifndef GANGDUO_BASE_LOGSTREAM_HPP
#define GANGDUO_BASE_LOGSTREAM_HPP

#include "gangduo/base/noncopyable.hpp"
#include "gangduo/base/StringPiece.hpp"
#include "gangduo/base/Types.hpp"
#include <assert.h>
#include <string.h> // memcpy

namespace gangduo
{

namespace detail
{

const int nSmallBuffer = 4000;
const int nLargeBuffer = 4000*1000;

template<int SIZE>
class FixedBuffer: noncopyable{
public:
    FixedBuffer(): cur_(data_){
        setCookie(cookieStart);
    }
    ~FixedBuffer(){
        setCookie(cookieEnd);
    }

    void append(const char* buf, size_t len){
        if(implicit_cast<size_t>(avail()) > len){
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }

    const char* data() const { return data_; }
    int length() const { return static_cast<int>(cur_ - data_); }

    char* current() { return cur_; }
    int avail() const { return static_cast<int>(end() - cur_); }
    void add(size_t len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { memZero(data_, sizeof(data_)); }

    // for GDB?
    const char* debugString();
    void setCookie(void(*cookie)()) { cookie_ = cookie; }
    // for unit test?
    string toString() const { return string(data_, length()); }
    StringPiece toStringPiece() const { return StringPiece(data_, length()); }

private:
    const char* end() const { return data_ + sizeof(data_); }
    static void cookieStart();
    static void cookieEnd();

private:
    void (*cookie_)();
    char data_[SIZE];
    char* cur_;
};

} // namespace detail

class LogStream: noncopyable
{
public:
    using Buffer = detail::FixedBuffer<detail::nSmallBuffer>;

    void append(const char* data, int len){ buffer_.append(data, len); }
    const Buffer& buffer() const { return buffer_; }
    void resetBuffer() { buffer_.reset(); }

    // operator<<() overloads
    LogStream& operator<<(bool v){
        buffer_.append(v ? "1" : "0", 1);
        return *this;
    }

    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);

    LogStream& operator<<(const void*);

    LogStream& operator<<(float v){
        *this << static_cast<double>(v);
        return *this;
    }
    LogStream& operator<<(double v);
    LogStream& operator<<(char v){
        buffer_.append(&v, 1);
        return *this;
    }

    LogStream& operator<<(const char* str){
        if(str){
            buffer_.append(str, strlen(str));
        }else{
            buffer_.append("(nullptr)", 9);
        }
        return *this;
    }
    LogStream& operator<<(const unsigned char* str){
        return operator<<(reinterpret_cast<const char*>(str));
    }

    LogStream& operator<<(const string& str){
        buffer_.append(str.c_str(), str.size());
        return *this;
    }
    LogStream& operator<<(const StringPiece& str){
        buffer_.append(str.data(), str.size());
        return *this;
    }
    LogStream& operator<<(const Buffer& buf){
        *this << buf.toStringPiece();
        return *this;
    }

private:
    void staticCheck();
    
    template<typename T>
    void formatInteger(T);
private:
    Buffer buffer_;
    static const int nMaxNumericSize = 32;
};

class Fmt
{
public:
    template<typename T>
    Fmt(const char* fmt, T val);

    const char* data() const { return buf_; }
    int length() const { return length_; }
private:
    char buf_[32];
    int length_;
};

inline LogStream& operator<<(LogStream& ls, const Fmt& fmt){
    ls.append(fmt.data(), fmt.length());
    return ls;
}

// format quantity n in SI (k: 10e3, M: 10e6, G: 10e9, T:10e12, P: 10e15, E: 10e18).
// n >= 0
string formatSI(int64_t n);

// format quantity n in IEC(binary) (Ki: 2e10, Mi: 2e20, Gi: 2e30, Ti:2e40, Pi: 2e50, Ei: 2e60).
// n >= 0
string formatIEC(int64_t n);

} // namespace gangduo

#endif // !GANGDUO_BASE_LOGSTREAM_HPP