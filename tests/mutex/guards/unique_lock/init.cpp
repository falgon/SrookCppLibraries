// #define SROOK_CONFIG_DISABLE_DEPRECATED_OF_ATTRIBUTE_MESSAGES 1
// #define SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE 1

#include <srook/mutex.hpp>

srook::mutex m;

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
namespace compatibility_boost {
	void basic()
	{
		{
			boost::unique_lock<srook::mutex> lk1(m);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
		}
		
		{
			boost::unique_lock<srook::mutex> lk1(m);
			srook::unique_lock<srook::mutex> lk2;
			lk2 = srook::move(lk1);
		}
	}

	void lock_ts()
	{
		{
			boost::unique_lock<srook::mutex> lk1(m, boost::defer_lock);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
			lk2.lock();
		}
		{
			boost::unique_lock<srook::mutex> lk1(m, boost::try_to_lock);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk1));
			if (!lk2) {
				// ...
			}
		}
		{
			m.lock();
			boost::unique_lock<srook::mutex> lk1(m, boost::adopt_lock);
			srook::unique_lock<srook::mutex> lk2(srook::move(lk2));
		}
	}

	void lock_chrono() {}
};
#endif

void unique_lock_construct_test()
{
	{
		srook::unique_lock<srook::mutex> lk1(m);
		srook::unique_lock<srook::mutex> lk2(srook::move(lk1));

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
		lk2.unlock();
		compatibility_boost::basic();
		compatibility_boost::lock_ts();
#endif
	}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
	{
		m.lock();
		srook::unique_lock<srook::mutex> lk1(m, std::adopt_lock);
	}
	{
		srook::unique_lock<srook::mutex> lk1(m, std::try_to_lock);
		if (!lk1) {
		   // ....
		}
	}	
	{
		srook::unique_lock<srook::mutex> lk1(m, std::defer_lock);
		lk1.lock();
	}
#elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
	{
		m.lock();
		srook::unique_lock<srook::mutex> lk1(m, boost::adopt_lock);
	}
	{
		srook::unique_lock<srook::mutex> lk1(m, boost::try_to_lock);
		if (!lk1) {
			// ...
		}
	}
	{
		srook::unique_lock<srook::mutex> lk1(m, boost::defer_lock);
		lk1.lock();
	}
#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
	{
		srook::unique_lock lk1(m);
		srook::unique_lock lk2 = srook::move(lk1);
	}
#endif
}

int main()
{
	unique_lock_construct_test();
}
