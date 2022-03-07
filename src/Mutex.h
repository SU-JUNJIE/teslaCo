#ifndef __TESLA__MUTEX__H__
#define __TESLA__MUTEX__H__

#include <pthread.h>
#include "Noncopyable.h"

namespace tesla
{

class Mutex : public Noncopyable {
friend class Condition;
public:
    Mutex();
    ~Mutex();
    void lock();
    void unlock();

private:
    pthread_mutex_t* getMutex();
    pthread_mutex_t mutex_;
};


class MutexGuard {
public:
    MutexGuard(Mutex &mutex);
    ~MutexGuard();

private:
    Mutex &mutex_;
};

}

#endif  