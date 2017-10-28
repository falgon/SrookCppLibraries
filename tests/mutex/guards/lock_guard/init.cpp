// #define SROOK_CONFIG_DISABLE_DEPRECATED_OF_ATTRIBUTE_MESSAGES 1
#include <srook/mutex.hpp>

srook::mutex m;

void lock_guard_test()
{
	{
		srook::lock_guard<srook::mutex> lock(m);
	}
	{
		m.lock();
		srook::lock_guard<srook::mutex> lock(m, srook::adopt_lock);
	}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
	{
		srook::lock_guard lock(m);
	}
	{
		srook::lock_guard lock(m, srook::adopt_lock);
	}
#endif

}

int main()
{
	lock_guard_test();
}
