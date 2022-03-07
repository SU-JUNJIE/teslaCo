#ifndef __SINGLETON__H__
#define __SINGLETON__H__

#include "Noncopyable.h"



namespace tesla {

template<class T>
class Singleton {
public:
    ~Singleton() {}
    static T* getInstance() {
        static T instance_;
        return &instance_;
    }
private:
    Singleton(){}
    Singleton(const Singleton &){}
    Singleton &operator=(const Singleton &);
};

}



#endif  //!__SINGLETON__H__