#ifndef __LOG__H__
#define __LOG__H__

#include <string>
#include <map>
#include <sstream>
#include <sys/types.h>
#include <time.h>
#include <memory>
#include <vector>

#include "Condition.h"
#include "CountDownLatch.h"
#include "Mutex.h"
#include "Singleton.h"
#include "Thread.h"
#include "Timestamp.h"

namespace tesla {

enum class LogLevel {
	DEBUG,
	INFO,
	WARN,
	ERROR,
	FATAL, 
};

class LogEvent {
    friend class Logger;
    friend class LogWrapper;

public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(Timestamp timestamp, pid_t tid, LogLevel logLevel,
             const char *file_name, int line);
    std::ostream &getStream();

private:
    Timestamp timestamp_;
    pid_t tid_;
    LogLevel logLevel_;
    std::ostringstream content_;
    std::string file_name_;
    int line_;
};


class LogWrapper {
public:
    LogWrapper(LogEvent::ptr event);
    ~LogWrapper();
    std::ostream &getStream();

private:
    LogEvent::ptr event_;
};

class LogAppender {
public:
	typedef std::shared_ptr<LogAppender> ptr;

	virtual ~LogAppender() {}
	virtual void append(const std::string& log) = 0;

};

class ConsoleAppender : public LogAppender {
public:
	void append(const std::string& log) override;
};

static const size_t kLogBufferSize = 1024 * 1024 * 10;

class LogBuffer : public Noncopyable {
public:
    LogBuffer(size_t total =  kLogBufferSize);
    ~LogBuffer();
    void clear();
    void append(const char *data, size_t len);
    const char *data() const;
    size_t length() const;
    size_t available() const;

private:
    char* data_;
    const size_t total_;
    size_t available_;
    size_t cur_;
};

class AsyncFileAppender : public LogAppender {
public:
    AsyncFileAppender(std::string basename, time_t persist_period = 3);
    ~AsyncFileAppender();
    void append(const std::string& log) override;
    void start();
    void stop();

private:
    void threadFunc();

    bool started_;
    bool running_;
    time_t persist_period_;
    std::string basename_;
    Mutex mutex_;
    Condition cond_;
    CountDownLatch countdown_latch_;
    Thread persist_thread_;
    std::unique_ptr<LogBuffer> cur_buffer_;
    std::vector<std::unique_ptr<LogBuffer>> buffers_;
};



class Logger {
friend class Singleton<Logger>;
public:
    void log(LogEvent::ptr event);
    void addAppender(const std::string, LogAppender::ptr appender);
    void delAppender(const std::string name);
    void clearAppender();

    static void setLogLevel(LogLevel logLevel);
    static LogLevel getLogLevel();

protected:
    virtual std::string format(LogEvent::ptr event);

private:
    Logger();
    virtual ~Logger(){};
    Mutex mutex_;
    std::map<std::string, LogAppender::ptr> appenders_;
};

template class Singleton<Logger>;


}

#define LOG_DEBUG tesla::LogWrapper(tesla::LogEvent::ptr(new tesla::LogEvent(tesla::Timestamp::now(), tesla::Thread::CurrentThreadTid(), tesla::LogLevel::DEBUG, \
									__FILE__, __LINE__))).getStream()

#define LOG_INFO  tesla::LogWrapper(tesla::LogEvent::ptr(new tesla::LogEvent(tesla::Timestamp::now(), tesla::Thread::CurrentThreadTid(), tesla::LogLevel::INFO, \
									__FILE__, __LINE__))).getStream()

#define LOG_WARN  tesla::LogWrapper(tesla::LogEvent::ptr(new tesla::LogEvent(tesla::Timestamp::now(), tesla::Thread::CurrentThreadTid(), tesla::LogLevel::WARN, \
									__FILE__, __LINE__))).getStream()

#define LOG_ERROR tesla::LogWrapper(tesla::LogEvent::ptr(new tesla::LogEvent(tesla::Timestamp::now(), tesla::Thread::CurrentThreadTid(), tesla::LogLevel::ERROR, \
									__FILE__, __LINE__))).getStream()

#define LOG_FATAL tesla::LogWrapper(tesla::LogEvent::ptr(new tesla::LogEvent(tesla::Timestamp::now(), tesla::Thread::CurrentThreadTid(), tesla::LogLevel::FATAL, \
									__FILE__, __LINE__))).getStream()


#endif  //!__LOG__H__