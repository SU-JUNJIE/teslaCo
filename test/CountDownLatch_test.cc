#include "CountDownLatch.h"
#include <iostream>
#include  "Thread.h"
#include <vector>
#include <memory>
#include <algorithm>



tesla::CountDownLatch c(10);

void func () {
    std::cout << "child thread finished" << std::endl;
    c.countDown();

}

void pvStart (std::shared_ptr<tesla::Thread> p) {
    p->start();

}


void pvJoin (std::shared_ptr<tesla::Thread> p) {
    p->join();

}



int main () {

    std::vector<std::shared_ptr<tesla::Thread>> pv;

    for (int i = 0; i < 10; i++) {
        pv.push_back(std::make_shared<tesla::Thread>(func));
    }

    for_each(pv.begin(), pv.end(), pvStart);
    
    c.wait();
    std::cout << "i am main func" << std::endl;

    for_each(pv.begin(), pv.end(), pvJoin);
    

    return 0;
}
