#include "Log.h"
#include "Singleton.h"
#include "Thread.h"

#include <iostream>
#include <unistd.h>


using namespace std;
using namespace tesla;

void func () {
    for (int i = 0; i < 1000; i++) {
        LOG_DEBUG << "i am child thread!";
    }
}
 
int main(int , char* argv[]) {
	
	Singleton<Logger>::getInstance()->addAppender("console", LogAppender::ptr(new ConsoleAppender()));
	std::shared_ptr<AsyncFileAppender> file_appender = std::make_shared<AsyncFileAppender>(argv[0]);	
	file_appender->start();
	Singleton<Logger>::getInstance()->addAppender("file", file_appender);

    Thread t1([&](int b = 2){
        for (int i = 0; i < 1000; i++) {
        LOG_INFO << "i am child thread!"<<t1.getName();
    }
    }, "aaaa");

    Thread t2(func, "bbbb");
    Thread t3(func, "cccc");

    t1.start();
    t2.start();
    t3.start();

    t1.join();
    t2.join();
    t3.join();
	
	return 0;
}
