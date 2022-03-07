#include "Mutex.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "Thread.h"

using namespace tesla;

Mutex mutex;

int count = 0;

void func(void) {
    //MutexGuard lock(mutex);
    for (int i = 0; i < 100000000;i++) {
        count++;
      
    }
    
}

int main () {

    Thread t1(func, "1");
    Thread t2(func, "2");


    t1.start();
    t2.start();


    t1.join();
    t2.join();


    std::cout << "count = " << count << std::endl;
    return 0;
}