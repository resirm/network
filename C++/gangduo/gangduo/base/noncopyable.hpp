#ifndef GANGDUO_BASE_NONCOPYABLE_HPP
#define GANGDUO_BASE_NONCOPYABLE_HPP

namespace gangduo
{

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

} // namespace gangduo

#endif // !GANGDUO_BASE_NONCOPYABLE_HPP