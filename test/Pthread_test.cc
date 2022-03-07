#include "Thread.h"

#include <sys/syscall.h>
#include <unistd.h>
#include <iostream>
#include "Log.h"
using namespace std;
using namespace tesla;



void func() {
	LOG_FATAL << "in thread: " << Thread::CurrentThreadTid()<<endl;
}

int main() {
	Thread t1(func, "2222");
	Thread t2(func);

	t1.start();
	t2.start();

	t1.join();	
	t2.join();
	LOG_DEBUG << "in thread: " << Thread::CurrentThreadTid()<<endl;
	LOG_DEBUG << t1.getName()<<endl;
	LOG_DEBUG << t2.getName()<<endl;
	return 0;
}
