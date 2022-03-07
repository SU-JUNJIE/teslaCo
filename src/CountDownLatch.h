#ifndef __COUNTDOWNLATCH__H__
#define __COUNTDOWNLATCH__H__

#include "Mutex.h"
#include "Condition.h"

namespace tesla {

class CountDownLatch {
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();
    int getCount() const;

private:
    mutable Mutex mutex_;
    Condition cond_;
    int count_;
};

}

#endif  //!__COUNTDOWNLATCH__H__