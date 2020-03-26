#ifndef GANGDUO_BASE_STRINGPIECE_HPP
#define GANGDUO_BASE_STRINGPIECE_HPP

#include <string.h>
#include <iosfwd>
#include "gangduo/base/Types.hpp"

namespace gangduo
{

class StringArg
{
public:
    StringArg(const char* str):str_(str){}
    StringArg(const string& str):str_(str.c_str()){}
    const char* c_str() const { return str_; }
private:
    const char* str_;
};

class StringPiece
{
public:
    StringPiece()
        :ptr_(nullptr), length_(0) {}
    StringPiece(const char* str)
        :ptr_(str), length_(static_cast<int>(strlen(ptr_))) {}
    StringPiece(const unsigned char* str)
        :ptr_(reinterpret_cast<const char*>(str)),
         length_(static_cast<int>(strlen(ptr_))) {}
    StringPiece(const string& str) // data() is non-null terminated, while c_str() is.
        :ptr_(str.data()), length_(static_cast<int>(str.size())) {}
    StringPiece(const char* offset, int len)
        :ptr_(offset), length_(len) {}

    const char* data() const { return ptr_; }
    int size() const { return length_; }
    bool empty() const { return length_ == 0; }
    const char* begin() const { return ptr_; }
    const char* end() const { return ptr_ + length_; }
    void clear() { ptr_ = nullptr; length_ = 0; }
    void set(const char* buffer, int len) { ptr_ = buffer; length_ = len; }
    void set(const char* str) {
        ptr_ = str;
        length_ = static_cast<int>(strlen(str));
    }
    void set(const void* buffer, int len){
        ptr_ = reinterpret_cast<const char*>(buffer);
        length_ = len;
    }

    char operator[](int i) const { return ptr_[i]; }

    void remove_prefix(int n){  // no boundary check
        ptr_ += n;
        length_ -= n;
    }

    void remove_suffix(int n){
        length_ -= n;
    }

    bool operator==(const StringPiece& rhs) const{
        return ((length_ == rhs.length_) && 
                (memcmp(ptr_, rhs.ptr_, length_) == 0));
    }

    bool operator!=(const StringPiece& rhs) const{
        return !(*this == rhs);
    }

    bool operator<(const StringPiece& rhs) const{
        int r = memcmp(ptr_, rhs.ptr_, length_ < rhs.length_ ? length_ : rhs.length_);
        return ((r < 0) || ((r == 0) && (length_ < rhs.length_)));
    }

    bool operator<=(const StringPiece& rhs) const{
        return !(rhs < *this);
    }

    bool operator>(const StringPiece& rhs) const{
        return rhs < *this;
    }

    bool operator>=(const StringPiece& rhs) const{
        return !(*this < rhs);
    }

    int compare(const StringPiece& rhs) const{
        int r = memcmp(ptr_, rhs.ptr_, length_ < rhs.length_ ? length_ : rhs.length_);
        if(r == 0){
            if(length_ < rhs.length_){
                r = -1;
            }else if(length_ > rhs.length_){
                r = 1;
            }
        }
        return r;
    }

    string as_string() const{
        return string(data(), length_);
    }

    bool start_with(const StringPiece& s) const{
        return ((length_ >= s.length_) && (memcmp(ptr_, s.ptr_, s.length_) == 0));
    }

private:
    const char* ptr_;
    int         length_;
};

} // namespace gangduo

// traits... ?
#ifdef HAVE_TYPE_TRAITS
template<> 
struct __type_traits<gangduo::StringPiece>{
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivia_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
};
#endif
// for log-use
std::ostream& operator<<(std::ostream& os, const gangduo::StringPiece& s);

#endif // !GANGDUO_BASE_STRINGPIECE_HPP