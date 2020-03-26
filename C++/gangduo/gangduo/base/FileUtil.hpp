#ifndef GANGDUO_BASE_FILEUTIL_HPP
#define GANGDUO_BASE_FILEUTIL_HPP

#include "gangduo/base/noncopyable.hpp"
#include "gangduo/base/StringPiece.hpp"
#include <sys/types.h> // type off_t -- offset

namespace gangduo
{

namespace FileUtil
{

class ReadSmallFile: noncopyable{
public:
    ReadSmallFile(StringArg filename);
    ~ReadSmallFile();

    template<typename String>
    int readToString(
        int maxSize,
        String* content,
        int64_t* fileSize,
        int64_t* modifyTime,
        int64_t* createTime);

    int readToBuffer(int* size);

    const char* buffer() const { return buf_; }

    static const int nBufferSize = 64*1024;
private:
    int fd_;
    int err_;
    char buf_[nBufferSize];
};

template<typename String>
int readFile(
        StringArg filename,
        int maxSize,
        String* content,
        int64_t* fileSize,
        int64_t* modifyTime,
        int64_t* createTime){
    ReadSmallFile file(filename);
    return file.readToString(maxSize, content, fileSize, modifyTime, createTime);
}

class AppendFile: noncopyable{
public:
    explicit AppendFile(StringArg filename);
    ~AppendFile();

    void append(const char* logline, size_t len);

    void flush();

    off_t writtenBytes() const { return writtenBytes_; }

private:
    size_t write(const char* logline, size_t len);
    
private:
    FILE* fp_;
    char buffer_[64*1024];
    off_t writtenBytes_;
};

} // namespace FileUtil

} // namespace gangduo

#endif // !GANGDUO_BASE_FILEUTIL_HPP