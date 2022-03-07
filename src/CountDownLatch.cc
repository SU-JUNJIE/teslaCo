#include "CountDownLatch.h"

namespace tesla
{
    CountDownLatch::CountDownLatch(int count):mutex_(),cond_(mutex_),count_(count) {}
    
    void CountDownLatch::wait() {
        MutexGuard lock(mutex_);
        while(count_ > 0) {
            cond_.wait();
        }
    
    }

    void CountDownLatch::countDown() {
        MutexGuard lock(mutex_);
        --count_;
        if(count_ == 0) {
            cond_.notifyAll();
        }
    }

    int CountDownLatch::getCount() const {
        MutexGuard lock(mutex_);
        return count_;
    }

} // namespace tesla
