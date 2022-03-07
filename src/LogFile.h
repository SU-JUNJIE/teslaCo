#ifndef __LOGFILE__H__
#define __LOGFILE__H__

#include "Noncopyable.h"
#include <string>

namespace tesla {

class LogFile : public Noncopyable {
public:
    LogFile(std::string basename);
    ~LogFile();

    void persist(const char *data, size_t length);
    void flush();

private:
    std::string getFileName();
    static const int kMaxFileSize = 1024 * 1024 * 1024;

    std::string basename_;
    int byte_writed_;
    FILE* fp_;
};

}

#endif  //!__LOGFILE__H__