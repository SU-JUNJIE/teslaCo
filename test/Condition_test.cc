#include "Condition.h"
#include "Thread.h"
#include <unistd.h>
#include <vector>
#include <memory>
#include <iostream>

int main()
{
  
    tesla::Mutex mutex;
    tesla::Condition cond(mutex);

    std::vector<std::shared_ptr<tesla::Thread>> v;

    for (int i = 0; i < 100; i++) {
        v.push_back(std::make_shared<tesla::Thread>([&mutex,&cond,i](){
                tesla::MutexGuard guard(mutex);
                if(cond.wait_seconds(2)) {
                    std::cout << "timeout, id = "<< i<<std::endl;
                }else {
                    std::cout << "wait up,id = "<< i<<std::endl;
                }
                
            }));

    }

    for(auto& p : v) {
        p->start();
    }

	sleep(2);
	cond.notifyAll();
	sleep(2);
	
    return 0;
}