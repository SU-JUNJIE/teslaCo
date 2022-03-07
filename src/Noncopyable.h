#ifndef _TESLA_NON_COPYABLE_H_
#define _TESLA_NON_COPYABLE_H_

namespace tesla {

class Noncopyable {
public:
	Noncopyable(const Noncopyable& rhs) = delete;
	Noncopyable& operator=(const Noncopyable& rhs) = delete;

protected:
	Noncopyable() = default;
	~Noncopyable() = default;

};

}

#endif
