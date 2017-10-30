#include <srook/mutex.hpp>

srook::mutex m1, m2;

int main()
{
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
	{
		srook::scoped_lock<srook::mutex, srook::mutex> lk{m1, m2};
	}
	{
		srook::lock(m1, m2);
		srook::scoped_lock<srook::mutex, srook::mutex> lk{srook::adopt_lock, m1, m2};
	}
	{
		srook::lock(m1, m2);
		srook::scoped_lock<srook::mutex, srook::mutex> lk{std::adopt_lock, m1, m2};
	}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
	{
		srook::scoped_lock lk{m1, m2};
	}
#endif
#elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
	{
		srook::scoped_lock<srook::mutex> lk(m1);
	}
	{
		m1.lock();
		srook::scoped_lock<srook::mutex> lk(srook::adopt_lock, m1);
	}
	{
		m1.lock();
		srook::scoped_lock<srook::mutex> lk(boost::adopt_lock, m1);
	}
#endif
}
