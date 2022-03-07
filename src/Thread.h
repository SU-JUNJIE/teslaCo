#ifndef _TESLA_THREAD_H_
#define _TESLA_THREAD_H_

#include "Noncopyable.h"
#include <functional>

namespace tesla {
class Thread : public Noncopyable {
public:
	typedef std::function<void (void)> Func;
	Thread(Func cb, std::string name = "");
	~Thread();

	bool isStarted();
	void start();
	void join();
	const std::string& getName() const;
	
	static pid_t CurrentThreadTid();
private:
	static void* threadFuncInternal(void* arg);
	bool started_;
	bool joined_;
	pthread_t tid_;
	std::string name_;
	Func cb_;
};

}

#endif 
