#ifndef GANGDUO_BASE_TYPES_HPP
#define GANGDUO_BASE_TYPES_HPP

#include <stdint.h>
#include <string.h>
#include <string>

#ifndef NDEBUG
#include <assert.h>
#endif

namespace gangduo
{

using std::string;

inline void memZero(void *p, size_t n){
    memset(p, 0, n);
}

template<typename To, typename From>
inline To implicit_cast(const From& f){
    return f;
}

template<typename To, typename From>
inline To down_cast(From* f){
    if(false){
        implicit_cast<From*, To>(nullptr);
    }
#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
    assert(f == nullptr || dynamic_cast<To>(f) != nullptr);
#endif
    return static_cast<To>(f);
}

} // namespace gangduo

#endif // !GANGDUO_BASE_TYPES_HPP