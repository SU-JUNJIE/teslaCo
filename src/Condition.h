#ifndef __TESLA__CONDITION__H__
#define __TESLA__CONDITION__H__

#include "Mutex.h"
#include "Noncopyable.h"
#include <pthread.h>

namespace tesla {

class Condition : public Noncopyable {
public:
    Condition(Mutex &mutex);
    ~Condition();

    void wait();
    bool wait_seconds(time_t seconds);
    void notify();
    void notifyAll();

private:
    Mutex& mutex_;
    pthread_cond_t cond_;
};

}

#endif  //!__CONDITION__H__